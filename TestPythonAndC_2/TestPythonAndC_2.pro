QT = core

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
 \    # testPython.py
    temp.py


win32: LIBS += -L$$PWD/../../../Tools/Ana/libs/ -lpython310

INCLUDEPATH += $$PWD/../../../Tools/Ana/include
DEPENDPATH += $$PWD/../../../Tools/Ana/include

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../../Tools/Ana/libs/python310.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/../../../Tools/Ana/libs/libpython310.a
