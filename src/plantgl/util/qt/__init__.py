from openalea.plantgl.config import PGL_QT_VERSION
import os

QT_VERSION = PGL_QT_VERSION

QT_API = 'QT_API' 
PYQT5_API = 'pyqt5'
PYQT4_API = 'pyqt'
PYSIDE_API = 'pyside'

os.environ[QT_API] = PYQT4_API if QT_VERSION == 4 else PYQT5_API


if QT_VERSION == 4:
    os.environ.setdefault('QT_API_VERSION', '2')
    import PyQt4
else:
    import PyQt5


if QT_VERSION == 4:
    import sip
    assert sip.getapi('QString') == 2

