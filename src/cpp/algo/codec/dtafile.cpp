/* -*-c++-*-
 *  ----------------------------------------------------------------------------
 *
 *       AMAPmod: Exploring and Modeling Plant Architecture
 *
 *       Copyright 1995-2000 UMR Cirad/Inra Modelisation des Plantes
 *
 *       File author(s): C. Nouguier & F. Boudon (frederic.boudon@cirad.fr) nouguier
 *
 *       $Source$
 *       $Id$
 *
 *       Forum for AMAPmod developers    : amldevlp@cirad.fr
 *
 *  ----------------------------------------------------------------------------
 *
 *                      GNU General Public Licence
 *
 *       This program is free software; you can redistribute it and/or
 *       modify it under the terms of the GNU General Public License as
 *       published by the Free Software Foundation; either version 2 of
 *       the License, or (at your option) any later version.
 *
 *       This program is distributed in the hope that it will be useful,
 *       but WITHOUT ANY WARRANTY; without even the implied warranty of
 *       MERCHANTABILITY or FITNESS For A PARTICULAR PURPOSE. See the
 *       GNU General Public License for more details.
 *
 *       You should have received a copy of the GNU General Public
 *       License along with this program; see the file COPYING. If not,
 *       write to the Free Software Foundation, Inc., 59
 *       Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 *  ----------------------------------------------------------------------------
 */





#include "dtafile.h"
#include "scne_scene.h"
#include "scne_shape.h"
#include "appe_material.h"
#include "geom_amapsymbol.h"
#include "util_messages.h"
#include "Tools/util_math.h"
#include <fstream>

GEOM_USING_NAMESPACE

using namespace std;

// #define COLMULT(a,b,f) a = Color3((a.getRed()*f+b.getRed()*(100-f))/100,(a.getRed()*f+b.getBlue()*(100-f))/100,(a.getBlue()*f+b.getBlue()*(100-f))/100)
#define COLMULT(a,b,f);

/* ----------------------------------------------------------------------- */

ScenePtr readDtaFile(const string& fileName,  const string& symbol_path){
    ScenePtr result(new Scene());
    ifstream stream(fileName.c_str());
    if(stream){
	char c = ' ';
	//while(c ==' ' || c == '\t' || c == '\n')stream >> c;
	int num = 0;
	stream >> num;
	char buf[101];
	stream.getline(buf,100);
	// while(c !='\n')stream >> c;
//	(*SceneObject::commentStream) << "Must Find " << num << " symbol(s)" << endl;
	for(int a1=0;a1<num;a1++){
	    string name;
	    stream >> name;
	    int id;
	    stream >> id;
	    string file;
	    stream >> file;
		stream.getline(buf,100);
		size_t pos = file.find("_T_");
		if (pos != string::npos)
			file = string(file.begin(),file.begin()+pos);
		if(*(symbol_path.end()-1) == '/' || *(symbol_path.end()-1) == '\\')
			file = symbol_path+file+".smb";
	    else file = symbol_path+'/'+file+".smb";
	    AmapSymbol::Builder b;
	    b.FileName = &file;
	    if (b.isValid()){
			GeometryPtr s(new AmapSymbol(file));
			result->add(GeomShape(s,AppearancePtr(0),id));
	    }
		else { 		
		  (*SceneObject::warningStream) << "*** Warning : Cannot find symbol " << name << " in " << file << endl;
		  (*SceneObject::warningStream) << "*** Warning : Default Geometry will be used."<< endl;
			result->add(GeomShape(GeometryPtr(0),AppearancePtr(0),id));
		}

	}
	for(uint32_t a=0;a < (uint32_t) num;a++){
	    string name;
	    stream >> name;
		while(name != "Symbole") {(*SceneObject::errorStream) << "Error with Token '" << name.c_str()  << "' when parsing " << fileName << endl;stream >> name;}
	    int id;
	    stream >> id;
	    Color3 emission;
	    Color3 ambient;
	    Color3 specular;
	    real_t diffuse;
	    real_t shininess;
		int interpol = -1;

	    for(int m=0 ; m<5 ; m++){
		string field;
		stream >> field;
		if(field == "INTERPOLATION"){
		    stream >> interpol;
			m--;
		}
		else if(field == "EMISSION"){
		    real_t a,b,c;
		    stream >> a >> b >> c;
		    emission = Color3(uchar_t(a*255),uchar_t(b*255),uchar_t(c*255));
		}
		else if(field == "AMBIENT"){
		    real_t a,b,c;
		    stream >> a >> b >> c;
		    ambient = Color3(uchar_t(a*255),uchar_t(b*255),uchar_t(c*255));
		}
		else if(field == "SPECULAR"){
		    real_t a,b,c;
		    stream >> a >> b >> c;
		    specular = Color3(uchar_t(a*255),uchar_t(b*255),uchar_t(c*255));
		}
		else if(field == "DIFFUSE"){
		    real_t a,b,c;
		    stream >> a >> b >> c;
		    if(ambient.getRed() !=0 && 
			   ambient.getGreen() !=0 && 
			   ambient.getBlue() !=0)
		       diffuse = ((uchar_t(a*255)/ambient.getRed())+(uchar_t(b*255)/ambient.getGreen())+(uchar_t(c*255)/ambient.getBlue()))/3;
			else {
				real_t r1 = 0, r2 = 0, r3 = 0;
				int d = 0;
				if(ambient.getRed() !=0) {
					r1 = (uchar_t(a*255)/ambient.getRed());d++;
				}
				if(ambient.getGreen() !=0) {
					r2 = (uchar_t(b*255)/ambient.getGreen());d++;
				}
				if(ambient.getBlue() !=0) {
					r3 = (uchar_t(c*255)/ambient.getBlue());d++;
				}
				if(d == 0) diffuse = 1;
				else diffuse = (r1+r2+r3)/d;
			}
		}
		else if(field == "SHININESS"){
		    real_t a;
		    stream >> a;
		    shininess = a / 20;
		}
		else (*SceneObject::errorStream) << "Error with Token field '" << field.c_str()  << "' when parsing " << fileName << endl;
	    }
		if(interpol != -1){
		    Color3 emission2;
		    Color3 ambient2;
			Color3 specular2;
			real_t diffuse2;
			real_t shininess2;

		    for(int m=0 ; m<5 ; m++){
			string field;
			stream >> field;
			if(field == "EMISSION"){
				real_t a,b,c;
				stream >> a >> b >> c;
				emission2 = Color3(uchar_t(a*255),uchar_t(b*255),uchar_t(c*255));
				COLMULT(emission,emission2,interpol);
			}
			else if(field == "AMBIENT"){
				real_t a,b,c;
				stream >> a >> b >> c;
				ambient2 = Color3(uchar_t(a*255),uchar_t(b*255),uchar_t(c*255));
				COLMULT(ambient,ambient2,interpol);
			}
			else if(field == "SPECULAR"){
				real_t a,b,c;
				stream >> a >> b >> c;
				specular2 = Color3(uchar_t(a*255),uchar_t(b*255),uchar_t(c*255));
				COLMULT(specular,specular2,interpol);
			}
			else if(field == "DIFFUSE"){
				real_t a,b,c;
				stream >> a >> b >> c;
				if(ambient2.getRed() !=0 && ambient2.getGreen() !=0 && ambient2.getBlue() !=0)
					diffuse2 = ((uchar_t(a*255)/ambient2.getRed())+(uchar_t(b*255)/ambient2.getGreen())+(uchar_t(c*255)/ambient2.getBlue()))/3;
				else diffuse2 = 0;
				diffuse = (diffuse * interpol + diffuse2 * (100-interpol))/100;
			}
			else if(field == "SHININESS"){
				real_t a;
				stream >> a;
				shininess2 = a / 20;
				shininess = (shininess * interpol + shininess2 * (100-interpol))/100;
			}
			else (*SceneObject::errorStream) << "Error with Token field '" << field.c_str()  << "' when parsing " << fileName << endl;
			}
		}

	    AppearancePtr app(new Material(ambient,diffuse,specular,emission,shininess));
	    if(app->isValid()){
		Scene::iterator _it=result->getBegin();
		bool ok = false;
		GeomShapePtr * pt;
		while(_it!=result->getEnd() && !ok){
		    pt = (GeomShapePtr *)&(*(_it));
		    if((*pt)->getId() == (uint32_t)id){
			(*pt)->appearance = app;
			ok = true;
		    }
		    _it++;
		}
		if(!ok) (*SceneObject::errorStream) << "*** Error : The Appearance " << a  << " cannot be attributed." << endl;
	    }
	    else (*SceneObject::errorStream) << "*** Error : An appearance is not valid (with GEOM)." << endl;
	}
	return result;
    }
    else return ScenePtr(0);
}


/* ----------------------------------------------------------------------- */


bool Dtafile::isValid( ) const {
  if (_fileName.empty()) {
    genMessage(WARNINGMSG(UNINITIALIZED_FIELD_ss),"Dtafile","FileName");
    return 0;
  };
  ifstream _file(_fileName.c_str());
  if (_file) return true;
  string _mess = "Cannot open " + _fileName + '.';
  genMessage(WARNINGMSG(INVALID_FIELD_VALUE_sss),"Dtafile","FileName",_mess.c_str());
  return false;
}


/* ----------------------------------------------------------------------- */


Dtafile::Dtafile( const string& fileName,  const string& __symbol_path ) :
    _fileName(fileName),
    _symbol_path(__symbol_path),
    _scene(0),
    linear(false),
    symbolTable(0){

    if(isValid()){
/*      setSymbolPath(_symbol_path);
        ifstream _file(_fileName.c_str());
        SceneObjectSymbolTable * table = new SceneObjectSymbolTable;
        GenericParser<SceneObjectPtr> _parser(dta2geom_yyparse,table);
        SceneObjectRecursiveLexer _dta2geomLexer(&_file,&cerr,_fileName.c_str());
        _parser.parse(&_dta2geomLexer,cerr);
        for( SceneObjectSymbolTable::iterator _it = table->begin();
             _it!=table->end();_it++){
            GeomShapePtr s = GeomShapePtr(_it->second);
            if(s){
                _scene->add(*s);
            }
        } */
        _scene = readDtaFile(fileName,__symbol_path);
    }
}

Dtafile::~Dtafile( ) {
  if(symbolTable)delete symbolTable;
}

const string&
Dtafile::getFileName( ) const {
  return _fileName;
}

const ScenePtr&
Dtafile::getScene() const {
  return _scene;
}


/* ----------------------------------------------------------------------- */

const unsigned int  Dtafile::getSize() const {
    return _scene->getSize();
}

AmapSymbolPtr Dtafile::getSymbol( const uint32_t id) const {
    int Id = getSymbolNumber(id);
    if(Id == -1) Id =id;
    GeomShapePtr shape;
    for(Scene::iterator _it = _scene->getBegin();
        _it != _scene->getEnd();
        _it++){
      if(shape.cast(*_it).isValid() && (int)shape->getId() == Id)
        return AmapSymbolPtr::Cast(shape->geometry);
    }
    return AmapSymbolPtr(0);
}

MaterialPtr Dtafile::getMaterial( const uint32_t id) const {
    int Id = getSymbolNumber(id);
    if(Id == -1) Id =id;
    GeomShapePtr shape;
    for(Scene::iterator _it = _scene->getBegin();
        _it != _scene->getEnd();
        _it++){
        if(shape.cast(*_it).isValid() && (int)shape->getId() == Id)
          return MaterialPtr::Cast(shape->appearance);
    }
    return MaterialPtr(0);
};

const GeomShapePtr Dtafile::getdtainfo( const uint32_t id) const {
    int Id = getSymbolNumber(id);
    if(Id == -1) Id =id;
    GeomShapePtr shape;
    for(Scene::iterator _it = _scene->getBegin();
        _it != _scene->getEnd();
        _it++){
      if(shape.cast(*_it).isValid() && (int)shape->getId() == Id)
        return shape;
    }
    return GeomShapePtr(0);
};


bool Dtafile::readSymbolTable(const string & mtg_filename){
    ifstream _file(mtg_filename.c_str());
    if (!_file)return false;
    else {
        size_t lineSize = 1024;
        char * lineBuf = new char[lineSize];
        vector< pair<int,int> > *  symbol_table = new vector< pair<int,int> >;
        while (_file.getline(lineBuf,lineSize) && string(lineBuf) != "#table des symboles");
        if( string(lineBuf) == "#table des symboles"){
            char c;
            _file >> c;
            if (c == '#'){
                int nb;
                char option[15];
                _file >> nb;
                _file >> option;
                if(string(option) == "lineaire")
                    linear = true;
                else linear = false;
                for(int i=0;i<nb;i++){
                    int a,b;
                    c = ' ';
                    while(c!='#')_file >> c;
                    _file >> a;
                    _file >> b;
                    if(finite(a) && finite(a)){
                        symbol_table->push_back(pair<int,int>(a,b));
                    }
                }
            }
                delete lineBuf;
            if(symbol_table->size()!=0){
                if(symbolTable) delete symbolTable;
                symbolTable = symbol_table;
/*              cerr << "Symbol Table Found :" << endl;
                for(vector< pair<int,int> >::iterator _it=symbolTable->begin();
                    _it!=symbolTable->end();_it++)
                    cerr << _it->first << " -> " << _it->second << endl;*/
                return true;
            }
            else return false;
        }
        else return false;
    }
}

int Dtafile::getSymbolNumber(const int id) const {
    if(!symbolTable) return -1;
    else {
        if(symbolTable->begin()->first >= id) return symbolTable->begin()->second;
        if((symbolTable->end()-1)->first <= id) return (symbolTable->end()-1)->second;
        else{
            vector< pair<int,int> >::iterator _it = symbolTable->begin();
            vector< pair<int,int> >::iterator _it2 = symbolTable->begin();
            _it2++;
            while(!(_it->first >= id && (_it2)->first <= id )){_it++;_it2++;}
            if(!linear)return _it->second;
            else return ((_it->second)+ ((_it2->second - _it->second)*(id-_it->first))/((_it2)->first - _it->first));
        }
    }
}

ostream& Dtafile::writeAMLCode(ostream& stream){
    if(symbolTable){
        stream << "#  Search Symbol Name in the MTG written by AMAPsim." << endl;
        stream << "step(_e) = Feature(_e,\"STEP\")" << endl << endl;
        stream << "#  Function that return the name of the symbol " << endl;
        stream << "#  associate to the entity _e." << endl;
        stream << "symbolName(_e) = If(step(_e) < "<< symbolTable->begin()->first << ") Then ";
        AmapSymbolPtr _smb =  getSymbol(symbolTable->begin()->first);
        if(_smb)
            stream << _smb->getName().c_str() << " \\" << endl;
        else stream << "\"\" \\" << endl;

        if(!linear){
            vector< pair <int,int> >::iterator _it = symbolTable->begin();
            while ((_it+1)!=symbolTable->end()){
                stream << "Else If(step(_e) >= " << _it->first << " And " << "step(_e) < " << (_it+1)->first << " ) Then ";
                _smb =  getSymbol(_it->first);
                if(_smb)
                    stream << _smb->getName().c_str() << " \\" << endl;
                else stream << "\"\" \\" << endl;
                _it++;
            }
        }
        else{
            vector< pair <int,int> >::iterator _it = symbolTable->begin();
            while ((_it+1)!=symbolTable->end()){
                int a = _it->first, b = (_it+1)->first;
                int c = _it->second, d = (_it+1)->second, e = d-c ;
                int j = a,k = a;
                for(int i = 0 ; i <= e ; i ++){
                    k = i*(b-a)/(d-c) + a;
                    stream << "Else If(step(_e) >= " << j << " And " << "step(_e) < " << k << " ) Then ";
                    _smb =  getSymbol(j);
                    if(_smb)
                        stream << _smb->getName().c_str() << " \\" << endl;
                    else stream << "\"\" \\" << endl;
                    j = k;
                }
                _it++;
            }
        }
        stream << "Else ";
        _smb =  getSymbol((symbolTable->end()-1)->first+1);
        if(_smb)
            stream << _smb->getName().c_str() << endl << endl;
        else stream << "\"\" " << endl  << endl;


        stream << "#  Function that return the name of the appearance" << endl;
        stream << "#  associate to the entity _e." << endl;
        stream << "appName(_e) = If(step(_e) < "<< symbolTable->begin()->first << ") Then ";
        AppearancePtr _app;
        if(_app.cast(getMaterial(symbolTable->begin()->first)))
            stream << _app->getName().c_str() << " \\" << endl;
        else stream << "\"\" \\" << endl;

        if(!linear){
            vector< pair <int,int> >::iterator _it = symbolTable->begin();
            while ((_it+1)!=symbolTable->end()){
                stream << "Else If(step(_e) >= " << _it->first << " And " << "step(_e) < " << (_it+1)->first << " ) Then ";
                _app =  getMaterial(_it->first);
                if(_app)
                    stream << _app->getName().c_str() << " \\" << endl;
                else stream << "\"\" \\" << endl;
                _it++;
            }
        }
        else{
            vector< pair <int,int> >::iterator _it = symbolTable->begin();
            while ((_it+1)!=symbolTable->end()){
                int a = _it->first, b = (_it+1)->first;
                int c = _it->second, d = (_it+1)->second, e = d-c ;
                int j = a,k = a;
                for(int i = 0 ; i <= e ; i ++){
                    k = i*(b-a)/(d-c) + a;
                    stream << "Else If(step(_e) >= " << j << " And " << "step(_e) < " << k << " ) Then ";
                    _app =  getMaterial(j);
                    if(_app)
                        stream << _app->getName().c_str() << " \\" << endl;
                    else stream << "\"\" \\" << endl;
                    j = k;
                }
                _it++;
            }
        }
        stream << "Else ";
        _app =  getMaterial((symbolTable->end()-1)->first + 1);
        if(_app)
            stream << _app->getName().c_str() << endl << endl;
        else stream << "\"\" " << endl << endl;
        stream << "#  Array of [step, symbol num]." << endl;
        stream << "#  Function " << (linear ? "Linear" : "Constant") << endl;
        stream << "step_symb = [ \\" << endl;
        for(vector< pair <int,int> >::iterator _it = symbolTable->begin();
            _it != symbolTable->end();_it++){
            stream << "[" << _it->first << "," << _it->second << "]";
            if(_it!=symbolTable->end()-1)stream << ",";
            stream << " \\" << endl;
        }
        stream << "]" << endl << endl;
    }

    stream << "#  Array of symbol num." << endl;
    stream << " num_symb_array = [ \\" << endl;
    int nb = 0,itf = _scene->getSize();
    GeomShapePtr shape;
    for(Scene::iterator _it = _scene->getBegin();
        _it != _scene->getEnd();
        _it++){
        nb++;
        if(shape.cast(*_it)){
          stream << shape->getId();
          if(nb!=itf)stream << ",";
          stream << " \\" << endl;
        }
    }
    stream  << "]" << endl << endl;

    stream << "#  Array of [symbol name ,appearance name]." << endl;
    stream << " symb_array = [ \\" << endl;
    nb = 0;
    for(Scene::iterator _it2 = _scene->getBegin();
        _it2 != _scene->getEnd();
        _it2++){
      if(shape.cast(*_it2)){
        nb++;
        stream << "[";
        if(shape->getGeometry())stream <<shape->getGeometry()->getName().c_str() << ",";
        else stream << " \"\" ,";
        if(shape->getAppearance())stream <<shape->getAppearance()->getName().c_str() << "]";
        else stream << " \"\" ]";
        if(nb!=itf)stream << ",";
        stream << " \\" << endl;
      }
    }
    stream  << "]" << endl << endl;

    return stream;
}

/*
bofstream& Dtafile::write( bofstream& stream ) const {
}
*/

/* ----------------------------------------------------------------------- */
