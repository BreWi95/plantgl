"""
Provides QtDesigner classes and functions.
"""
import os
from openalea.plantgl.util.qt import QT_API, PYQT5_API, PYQT4_API


if os.environ[QT_API] in PYQT5_API:
    from PyQt5.QtDesigner import *
elif os.environ[QT_API] in PYQT4_API:
    from PyQt4.QtDesigner import *
