######################################################################
# Automatically generated by qmake (2.00a) Sun Jun 26 21:12:22 2005
######################################################################

TEMPLATE = app
CONFIG += qt warn_on debug console
QT -= gui
DEPENDPATH += .
INCLUDEPATH += . ../..
unix:LIBS += -L../../quazip -lquazip
win32:LIBS += -L../../quazip/release -lquazip

# Input
SOURCES += main.cpp

unix {
  OBJECTS_DIR=.obj
}
