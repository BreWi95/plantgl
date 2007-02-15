/* -*-c++-*-
 *  ----------------------------------------------------------------------------
 *
 *       AMAPmod: Exploring and Modeling Plant Architecture
 *
 *       Copyright 1995-2000 UMR Cirad/Inra Modelisation des Plantes
 *                           UMR PIAF INRA-UBP Clermont-Ferrand
 *
 *       File author(s): F. Boudon
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

/*! \file view_geomscenegl.h
    \brief Definition of the viewer class ViewGeomSceneGL and ViewMultiGeomSceneGL.
*/

#ifndef __view_geomscenegl_h__
#define __view_geomscenegl_h__

/* ----------------------------------------------------------------------- */

#include "../base/modalscenegl.h"
#include <scenegraph/scene/scene.h>
#include <scenegraph/geometry/polyline.h>
#include <algo/base/discretizer.h>
#include <algo/base/skelcomputer.h>
#include <algo/base/bboxcomputer.h>
#include <algo/opengl/glbboxrenderer.h>
#include <algo/opengl/glrenderer.h>
#include <algo/opengl/gltransitionrenderer.h>
#include <algo/opengl/glskelrenderer.h>
#include <algo/opengl/glctrlptrenderer.h>
#include <tool/util_hashmap.h>
#include <vector>

/* ----------------------------------------------------------------------- */

class QSlider;
class QDialod;
class QToolBar;

/* ----------------------------------------------------------------------- */

class ViewGeomReader;
class ViewRayPointHitBuffer;
#include "../base/util_qwidget.h"

/* ----------------------------------------------------------------------- */

/**
   \class ViewGeomSceneGL
   \brief A GL Display Manager for Geom Scene.

*/

/* ----------------------------------------------------------------------- */

class VIEW_API ViewGeomSceneGL  : public ViewModalRendererGL
{
  Q_OBJECT

    public :

  /// Constructor.
  ViewGeomSceneGL(ViewCameraGL * camera=0,
                  ViewLightGL * light=0,
                  QGLWidget * parent=0,
                  const char * name=0);

  /// Destructor.
  virtual ~ViewGeomSceneGL();

  virtual void selectGL();

  /// Scene change Event.
  virtual bool sceneChangeEvent(ViewSceneChangeEvent *);

  virtual void paintGL();

  virtual void initializeGL();

  virtual bool addOpenEntries(QPopupMenu * menu);

  virtual bool addSaveEntries(QPopupMenu * menu);

  virtual bool addImportEntries(QPopupMenu * menu);

  virtual bool addExportEntries(QPopupMenu * menu);  
  
  /// Add Edit Entries
  virtual bool addEditEntries(QPopupMenu * menu);

  virtual bool addProperties(QTabWidget * tab);

  virtual bool browse(QListView *,bool);

  /// Create a Popup menu that reflect the functionality of this.
  virtual QPopupMenu * createToolsMenu(QWidget * parent);

  virtual void clear();

  virtual void clearCache();

  /// Set the scene \b _scene to the frame and display.
  int addScene( const PGL(ScenePtr)& scene );

  /// Set the scene \b _scene to the frame and display.
  int setScene( const PGL(ScenePtr)& scene );

  /// Get the scene.
  PGL(ScenePtr) getScene( ) const;

  /// Get the scene. 
  PGL(ScenePtr) getSelection( ) const;

  /// Get the scene. 
  PGL(ScenePtr) getNotSelection( ) const;

  virtual std::vector<uint32_t> getSelectionIds() const;
  virtual uint32_t translateId(uint32_t) const;

  /// Get the global Bounding Box.
  const PGL(BoundingBoxPtr) getGlobalBoundingBox() const;

  const PGL(BoundingBoxPtr) getSelectionBoundingBox() ;

  std::vector<std::pair<uint32_t,double> > getProjectionSizes(const PGL(ScenePtr)&);
  ViewRayPointHitBuffer * castRays(const PGL(ScenePtr)& sc, bool back_test);

  /// Get the surface of the scene.
  real_t getSceneSurface();

  /// Get the volume of the scene.
  real_t getSceneVolume();
 
  /// Get the surface of the selected element.
  real_t getSelectionSurface();
  
  /// Get the volume of the selected element.
  real_t getSelectionVolume();
 
  bool getDisplayListUse() const;

  static bool useThread();

  /// Save current scene in GEOM format in the file \b filename.
  bool saveAsGeom(const QString& filename);
  bool saveAsGeom(const QString& shape,
				  const QString& geom,
				  const QString& mat);

  /// Print the current Scene in the povray format in the file \b filename.
  bool saveAsPovRay(const QString& filename);

  /// Print the current Scene in the povray format in the file \b filename.
  bool saveAsVegeStar(const QString& filename);

  /// Print the current Scene in the Amap format in the file \b filename.
  bool saveAsAmapSymbol(const QString& filename);

  /// Print the current Scene in the Amap format in the file \b filename.
  bool saveAsLinetree(const QString& filename);

  /// Print the current Scene in the Amap format in the file \b filename.
  bool saveAsLinetree(const QString& lig,
                      const QString& dta,
                      const QString& smb,
                      const QString& key,
					  bool bigendian = true);

  /// Try to open file. Return true if ok.
  virtual bool open(const QString& filename);

  /// Try to open stream. Return true if ok.
  // virtual bool openStream(std::istream& stream);

  /// Load the symbol of the file \b _filename.
  bool openAmapSymbol(const QString& filename,bool add=false);

  /// Load the geom objects of the file \b _filename.
  bool openGeomFile(const QString& filename);

  /// Load the geom objects of the file \b _filename.
  bool addGeomFile(const QString& filename);

  /// Load the geom objects of the file \b _filename.
  bool openGeomViewFile(const QString& filename,bool add=false);

  /// Load the geom objects.
  bool openLinetree(const QString& filename,bool add=false);

   /// Import VegeStar geometry from filename.
  bool openVegeStar(const QString& filename,bool add=false);
  bool openVegeStarSymbol1(const QString& filename,bool add=false);

  bool exportFred(const QString& filename);
  bool hasSameMaterial() const;

  bool getGeomFilenames(QString& shape,
						QString& geom,
						QString& mat);

  /// Save the scene \bscene in GEOM format in the file \b filename.
  bool saveScene(const QString& shape,
				 const QString& geom,
				 const QString& mat,
				 PGL(ScenePtr) scene);

  /// Connect this to a GL Widget.
  virtual void connectTo(QGLWidget *);

public slots:

  virtual void refreshDisplay();

  virtual void addFile(const QString& filename);
  /// Save current scene in GEOM format.
  virtual void save();

  /// Save current scene in GEOM format.
  virtual void saveAs();
  void saveAsGeom();

  void saveSelection();
  void saveNotSelection();

  /// Print the current Scene in the povray format.
  void saveAsPovRay();

  /// Print the current Scene in the povray format.
  void saveAsVegeStar();

  /// Print the current Scene in the AMAP format.
  void saveAsAmapSymbol();

  /// Print the current Scene in the vrml format.
  void saveAsVrml();

  /// Print the current Scene in the AMAP format.
  void saveAsLinetree();

  /// Print the current Scene in the ply format.
  void saveAsPly();

  /// Load a symbol.
  void openAmapSymbol();

  /// Load geom objects.
  void openGeomFile();

  /// Load geom objects.
  void addGeomFile();

  /// Load geom objects.
  void openGeomViewFile();

  /// Load the geom objects.
  void openLinetree();

  /// Load the geom objects.
  void openVegeStar();
  void openVegeStarSymbol1();
  void openVegeStarSymbol2();
  void openVegeStarSymbol3();
  void showVegeStarSymbol1();
  void showVegeStarSymbol2();
  void showVegeStarSymbol3();
  void setSelectionVegeStarSymbol1();
  void setSelectionVegeStarSymbol2();
  void setSelectionVegeStarSymbol3();

  void exportFred();

  void changeDisplayListUse();
  virtual void useDisplayList(bool);

  /// Clear Selection Event.
  virtual void clearSelectionEvent();
  virtual void clearDisplayList();

  /// Selection Event.
  virtual void selectionEvent(uint32_t);
  virtual void selectionEvent(const std::vector<uint32_t>&);
  virtual void selectionIdEvent(const std::vector<uint32_t>&);
  virtual void selectionEvent(QListViewItem *);

  void removeSelection();
  void keepSelectionOnly();
  void wireSelection();
  void discretizeSelection();
  void triangulateSelection();

  void clipboard();

  virtual void computeCamera();

signals:
  
  void displayList(bool);

protected :

  virtual void customEvent(QCustomEvent *); 

  /// The scene object (which contains all the geometric shape and appereance to display).
  PGL(ScenePtr) __scene;

  /// The Discretizer.
  PGL(Discretizer) __discretizer;

  /// The Selection Renderer.
  PGL(GLRenderer) __renderer;

  /// The Skeleton Computer.
  PGL(SkelComputer) __skelComputer;

  /// The Bounding Box Computer.
  PGL(BBoxComputer) __bboxComputer;

  /// The Skeleton Renderer.
  PGL(GLSkelRenderer) __skelRenderer;

  /// The Bounding Box Renderer.
  PGL(GLBBoxRenderer) __bboxRenderer;

  /// The Control Points Renderer.
  PGL(GLCtrlPointRenderer) __ctrlPtRenderer;

  /// The global Bounding Box.
  PGL(BoundingBoxPtr) __bbox;

  /// Selected shapes.
 STDEXT::hash_map<uint32_t,PGL(Shape3DPtr)> __selectedShapes;

#ifdef QT_THREAD_SUPPORT
  /// Reader.
  ViewGeomReader * __reader;

#endif

};



/* ----------------------------------------------------------------------- */

/**
   \class ViewMultiGeomSceneGL
   \brief A GL Display Manager for Multiple Geom Scene.

*/
class VIEW_API ViewMultiGeomSceneGL  : public ViewGeomSceneGL
{
  Q_OBJECT

    public :


  /// Constructor.
  ViewMultiGeomSceneGL(ViewCameraGL * camera=0,
                       ViewLightGL * light=0,
                       QGLWidget * parent=0,
                       const char * name=0);

  /// Destructor.
  virtual ~ViewMultiGeomSceneGL();

  virtual void paintGL();

  virtual bool addOpenEntries(QPopupMenu * menu);

  virtual void clear();

  /// Set the scene \b _scene to the frame and display.
  int setScene( const PGL(ScenePtr)& scene1,
                const PGL(ScenePtr)& scene2 );

  /// Load the geom objects of the file \b _filename.
  bool openGeomFiles(const QString& filename1,
                     const QString& filename2);

  /// Scene change Event.
  virtual bool sceneChangeEvent(ViewSceneChangeEvent *);

  virtual void fillToolBar(QToolBar * toolBar);

  /// Add other toolbar.
  virtual bool addOtherToolBar(QMainWindow * menu);

  virtual QPopupMenu * createToolsMenu(QWidget * parent);

public slots:

  /// Load the geom objects.
  void openGeomFiles();

  /// Set the Rendering Step
  void setRenderingStep(int);

  /// Change the visibility of the Transition Slider
  void changeSliderVisibility();

  signals:

  void renderingStepChanged(int);

  void sliderVisibilityChanged(bool);

protected :

  /// The Transition Renderer.
  PGL(GLTransitionRenderer) __transitionRenderer;

  /// Rendering a simple scene.
  bool __simpleScene;

  /// The rendering step.
  int __renderingStep;

  /// Transition dialog slider
  QSlider * __transSlider;
  ViewToolBar * __transitionBar;
};

/* ----------------------------------------------------------------------- */
#endif

