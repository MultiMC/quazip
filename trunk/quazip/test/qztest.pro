TEMPLATE = app
QT -= gui
CONFIG += qtestlib
CONFIG += console
CONFIG -= app_bundle
TARGET = 
DEPENDPATH += .
INCLUDEPATH += . ..
LIBS += -L../quazip
LIBS += -lquazip
!win32: LIBS += -lz

# Input
HEADERS += qztest.h \
testjlcompress.h \
testquachecksum32.h \
testquagzipfile.h \
testquaziodevice.h \
testquazipdir.h \
testquazipfile.h \
testquazip.h

SOURCES += qztest.cpp \
testjlcompress.cpp \
testquachecksum32.cpp \
testquagzipfile.cpp \
testquaziodevice.cpp \
testquazip.cpp \
testquazipdir.cpp \
testquazipfile.cpp

OBJECTS_DIR = .obj
MOC_DIR = .moc
