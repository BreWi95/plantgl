import os


EXTRA_CXXFLAGS="-DCGAL_CFG_NO_CPP0X_VARIADIC_TEMPLATES"

library_inc = os.environ.get('LIBRARY_INC',os.path.join(os.environ['PREFIX'],'include'))

try:
    qversionconfig = file(os.path.join(library_inc,'qt','QtCore','qconfig.h'),'r').read()
    pattern = '#define QT_VERSION_MAJOR '
    try:
        i = qversionconfig.index(pattern)+len(pattern)
        qversionconfig = qversionconfig[i:].splitlines()[0]
        QT_VERSION = eval(qversionconfig)
    except ValueError, ie:
        qversionconfig = file(os.path.join(library_inc,'qt','QtCore','qglobal.h'),'r').read()
        pattern = '#define QT_VERSION '
        i = qversionconfig.index(pattern)+len(pattern)
        qversionconfig = qversionconfig[i:].splitlines()[0] >> 16
        QT_VERSION = eval(qversionconfig)
except Exception, ie:
    print 'Autodetect qt error:', ie
    QT_VERSION = 4

if 'CPU_COUNT' in os.environ:
    num_jobs = os.environ['CPU_COUNT']


EXTRA_LIBS = "boost_system png" 
