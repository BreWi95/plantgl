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


/*! \file geom_patch.h
    \brief Definition of the geometry class Patch.
*/


#ifndef __geom_patch_h__
#define __geom_patch_h__

/* ----------------------------------------------------------------------- */

#include "geom_parametricmodel.h"

/* ----------------------------------------------------------------------- */

GEOM_BEGIN_NAMESPACE

/* ----------------------------------------------------------------------- */

class Point4Matrix;
typedef RCPtr<Point4Matrix> Point4MatrixPtr;

/* ----------------------------------------------------------------------- */

/** 
    \class Patch
    \brief Abstract base class for objects of type of 3D parametric patch.
*/

/* ----------------------------------------------------------------------- */

class GEOM_API Patch : public ParametricModel
{

public:

  static const bool DEFAULT_CCW;

  /// A structure which helps to build an object of type of Patch.
  struct Builder : public ParametricModel::Builder {

    /// A pointer to the \b CCW field.
    bool * CCW;

    /// Constructor.
    Builder( );

    /// Destructor.
    ~Builder( );

  };


  /// Constructor.
  Patch(bool ccw = DEFAULT_CCW);

  /// Destructor
  virtual ~Patch( ) ;

  /// Returns \e Control Points value.
  virtual Point4MatrixPtr getCtrlPoints( ) const = 0 ;


  virtual bool isACurve( ) const;

  virtual bool isASurface( ) const;

  virtual bool isAVolume( ) const;

  /// Returns \e CCW value.
  const bool getCCW( ) const;

  /// Returns \e CCW field.
  bool& getCCW( );

  /// Returns whether \e CCW is set to its default value.
  bool isCCWToDefault( ) const;

protected:

  /// the ccw field
  bool __ccw;

};

/// Patch Pointer
typedef RCPtr<Patch> PatchPtr;
 

/* ----------------------------------------------------------------------- */

// __geom_patch_h__
/* ----------------------------------------------------------------------- */

GEOM_END_NAMESPACE

/* ----------------------------------------------------------------------- */
#endif
