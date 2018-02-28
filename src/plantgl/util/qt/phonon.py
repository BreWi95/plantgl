# -*- coding: utf-8 -*-

import os
from openalea.plantgl.util.qt import QT_API, PYQT5_API, PYQT4_API, PYSIDE_API

if os.environ[QT_API] == PYQT4_API:
    from PyQt4.phonon import *
elif os.environ[QT_API] == PYQT5_API:
    from PyQt5.phonon import *
else:
    from PySide.phonon import *
