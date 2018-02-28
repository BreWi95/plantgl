""" import qt.py from IPython to set QString and QVariant

The goal is to have the same version of QString and QVariant in all OpenAlea
"""

try:
    from openalea.plantgl.util.qt import QtCore
except ImportError:
    pass

try:
    from openalea.plantgl.util.qt import QtGui
except ImportError:
    pass

try:
    from openalea.plantgl.util.qt import QtWidgets
except ImportError:
    pass

try:
    from openalea.plantgl.util.qt import QtPrintSupport
except ImportError:
    pass

try:
    from openalea.plantgl.util.qt import QtOpenGL
except ImportError:
    pass

try:
    from openalea.plantgl.util.qt import QtTest
except ImportError:
    pass

try:
    from openalea.plantgl.util.qt import QtSql
except ImportError:
    pass

try:
    from openalea.plantgl.util.qt import QtWebKit
except ImportError:
    pass

try:
    from openalea.plantgl.util.qt import QtSvg
except ImportError:
    pass

try:
    from openalea.plantgl.util.qt import phonon
except ImportError:
    pass

