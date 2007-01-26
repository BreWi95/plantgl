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

/*! \file view_event.h
    \brief Definition of the viewer class events.
*/

#ifndef __view_event_h__
#define __view_event_h__

/* ----------------------------------------------------------------------- */

#include <qevent.h>
#include <qcolor.h>
#include <qstringlist.h>
#include <vector>
#include "Tools/config.h"
#include "Tools/util_vector.h"

#ifdef QT_THREAD_SUPPORT
#include <qthread.h>
#endif

TOOLS_USING(Vector3)

/* ----------------------------------------------------------------------- */

class GEOM_API ViewEvent : public QCustomEvent {
public:

  ViewEvent(int type):
	QCustomEvent(type),
	sent_event(false){}

  virtual ~ViewEvent(){}

  bool sent_event;

};
/**
   \class ViewSceneChangeEvent
   \brief An event to pass to glframe for changing scene.

*/

/* ----------------------------------------------------------------------- */

class GEOM_API ViewSceneChangeEvent : public ViewEvent {

  public :

  /// Constructor.
  ViewSceneChangeEvent(int type = 0);

  /// Destructor.
  ~ViewSceneChangeEvent();

  /// copy object.
  virtual ViewSceneChangeEvent * copy();

  const int& getSceneType() const;

protected:
  void setSceneType(const int& i);

private:

  int scene_type;
};

/* ----------------------------------------------------------------------- */

class GEOM_API ViewFileChangeEvent : public ViewEvent {

  public :

  /// Constructor.
  ViewFileChangeEvent(const QString& file);

  /// Destructor.
  ~ViewFileChangeEvent();

  /// new file to parse.
  QString filename;

};

/* ----------------------------------------------------------------------- */

class GEOM_API ViewImageSaveEvent : public ViewEvent {

  public :

  /// Constructor.
  ViewImageSaveEvent(const QString& file,const QString& format, bool withAlpha);

  /// Destructor.
  ~ViewImageSaveEvent();

  QString filename;
  QString format;
  bool withAlpha;
};

/* ----------------------------------------------------------------------- */

class GEOM_API ViewRefreshEvent : public ViewEvent {

  public :

  /// Constructor.
  ViewRefreshEvent();

  /// Destructor.
  ~ViewRefreshEvent();

};

/* ----------------------------------------------------------------------- */



/**
   \class ViewSelectRecoverEvent
   \brief An event to get selection from the viewer. Usefull for inter thread communication.
*/
class ViewSelectRecoverEvent : public ViewEvent {

public :

  /// Constructor.
  ViewSelectRecoverEvent();

  /// Constructor.
  ViewSelectRecoverEvent(std::vector<uint32_t> * e);

/// Destructor.
  ~ViewSelectRecoverEvent();

  /// set the selection (for the viewer).
  void setSelection(const std::vector<uint32_t>& a);

//private :

  /// Data Selection exchange beetwen the 2 process.
  std::vector<uint32_t> * __exchange;

};

class ViewSelectionSet : public ViewEvent {

public :

  /// Constructor.
  ViewSelectionSet(const std::vector<uint32_t>&);

  /// Destructor.
  ~ViewSelectionSet();

  /// set the selection (for the viewer).
  const std::vector<uint32_t>& getSelection() const;

protected :

  /// Data Selection exchange beetwen the 2 process.
  const std::vector<uint32_t> __data;

};

/* ----------------------------------------------------------------------- */

/**
   \class ViewEndEvent
   \brief An event to end the viewer. Usefull for inter thread communication.

*/
class ViewEndEvent : public ViewEvent {

    public :

  /// Constructor.
  ViewEndEvent();

  /// Destructor.
  ~ViewEndEvent();

};

/* ----------------------------------------------------------------------- */

/**
   \class ViewFullScreenEvent
   \brief An event to set the viewer full screen. Usefull for inter thread communication.

*/
class ViewFullScreenEvent : public ViewEvent {

    public :

  /// Constructor.
  ViewFullScreenEvent(bool b = true);

  /// Destructor.
  ~ViewFullScreenEvent();

  bool value;
};

/* ----------------------------------------------------------------------- */

/**
   \class ViewGLFrameOnlyEvent
   \brief An event to display GL Frame Only. Usefull for inter thread communication.

*/
class ViewGLFrameOnlyEvent : public ViewEvent {

    public :

  /// Constructor.
  ViewGLFrameOnlyEvent(bool b = true);

  /// Destructor.
  ~ViewGLFrameOnlyEvent();

  bool value;
};

/* ----------------------------------------------------------------------- */


/**
   \class ViewQuestionEvent
   \brief An event to end the viewer. Usefull for inter thread communication.

*/
class ViewQuestionEvent : public ViewEvent {

public :

  /// Constructor.
  ViewQuestionEvent();
  ViewQuestionEvent(const QString& _caption,
				 const QString& _text,
				 const QString& _but0txt = QString::null,
				 const QString& _but1txt = QString::null,
				 const QString& _but2txt = QString::null,
				 int * result = NULL);

  /// Destructor.
  ~ViewQuestionEvent();

  int * result;

  QString caption;
  QString text;
  QString but0txt;
  QString but1txt;
  QString but2txt;

};

/* ----------------------------------------------------------------------- */


/**
   \class ViewQuestionEvent
   \brief An event to end the viewer. Usefull for inter thread communication.

*/
class ViewItemSelectionEvent : public ViewEvent {

public :

  /// Constructor.
  ViewItemSelectionEvent(const QString& _caption,
				 const QString& _text,
				 const QStringList& _values,
				 bool _editable = false,
				 QString * res = NULL,
				 bool * ok = NULL);

  /// Destructor.
  ~ViewItemSelectionEvent();

  QString * result;
  bool * ok;

  QString caption;
  QString text;
  QStringList values;
  bool editable;

};

/* ----------------------------------------------------------------------- */

class ViewAnimationEvent : public ViewEvent {

public :

  /// Constructor.
  ViewAnimationEvent(bool a);

  /// Destructor.
  ~ViewAnimationEvent();

  bool mode;
};

/* ----------------------------------------------------------------------- */

class ViewBgColorEvent : public ViewEvent {

public :

  /// Constructor.
  ViewBgColorEvent(const QColor& c);

  /// Destructor.
  ~ViewBgColorEvent();

  QColor color;
};

/* ----------------------------------------------------------------------- */

class ViewGridEvent : public ViewEvent {

public :

  /// Constructor.
  ViewGridEvent(bool _xy, bool _yz, bool _xz, 
				bool _axis, int _size, int _unit, int _def);

  /// Destructor.
  ~ViewGridEvent();

  bool xy;
  bool yz;
  bool xz;
  bool axis;
  int size;
  int unit;
  int def;
};

/* ----------------------------------------------------------------------- */

class ViewCameraEvent : public ViewEvent {

public :

  /// Constructor.
  ViewCameraEvent(const Vector3& pos, const Vector3& target,
			      float azimuth, float elevation, int def);

  /// Destructor.
  ~ViewCameraEvent();

  Vector3 pos;
  Vector3 target;
  float azimuth;
  float elevation;
  int def;
};

/* ----------------------------------------------------------------------- */

class ViewPosEvent : public ViewEvent {

public :

  /// Constructor.
  ViewPosEvent(int _x, int _y, int _w, int _h, int _def);

  /// Destructor.
  ~ViewPosEvent();

  int x;
  int y;
  int w;
  int h;
  int def;
};

/* ----------------------------------------------------------------------- */

class ViewFileSelEvent : public ViewEvent {

public :

  /// Constructor.
  ViewFileSelEvent(const QString& caption,
				   const QString& startPath,
				   const QString& filter = QString::null,
				   bool existing = true, 
				   bool dir = true,
				   QString * res = NULL);

  /// Destructor.
  ~ViewFileSelEvent();

  QString *  result;
  QString caption;
  QString startPath;
  QString filter;
  bool existing;
  bool dir;
};

/* ----------------------------------------------------------------------- */
class ViewRayBuffer;

class ViewRayBuffEvent : public ViewEvent {

public :

  /// Constructor.
	ViewRayBuffEvent(const TOOLS(Vector3)& pos,
				   const TOOLS(Vector3)& dir,
		           const TOOLS(Vector3)& dx, 
		           const TOOLS(Vector3)& dy,
		           int sx, int sy,
				   ViewRayBuffer ** res = NULL);
	
	/// Destructor.
	~ViewRayBuffEvent();
	
	ViewRayBuffer **  result;
	const TOOLS(Vector3) pos;
	const TOOLS(Vector3) dir;
	const TOOLS(Vector3) dx; 
	const TOOLS(Vector3) dy;
    int sx;
	int sy;
};

/* ----------------------------------------------------------------------- */
class ViewZBuffer;

class ViewZBuffEvent : public ViewEvent {

public :

  /// Constructor.
	ViewZBuffEvent(ViewZBuffer ** res = NULL);
	
	/// Destructor.
	~ViewZBuffEvent();
	
	ViewZBuffer **  result;
};

/* ----------------------------------------------------------------------- */

class ViewProjSizeEvent : public ViewEvent {

public :

  /// Constructor.
	ViewProjSizeEvent (double * _size = NULL, int * _nbpix = NULL, double * _pixwidth = NULL);
	
	/// Destructor.
	~ViewProjSizeEvent();
	
    int * nbpixel;
	double * pixelwidth;
	double * size;
};

/* ----------------------------------------------------------------------- */

class ViewCameraProjEvent : public ViewEvent {

public :

  /// Constructor.
  ViewCameraProjEvent(bool _mode);

  /// Destructor.
  ~ViewCameraProjEvent();

  bool mode;
};

/* ----------------------------------------------------------------------- */

#endif
