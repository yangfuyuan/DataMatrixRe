#-------------------------------------------------
#
# Project created by QtCreator 2016-07-29T09:03:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DataMatrixRe
TEMPLATE = app

contains(TEMPLATE, "lib"){
    DESTDIR =./lib
    DLLDESTDIR = ./bin
}else{
    DESTDIR = ./bin
}


UI_DIR = ./ui
OBJECTS_DIR = ./obj
MOC_DIR = ./moc

QMAKE_CFLAGS += -std=c99


SOURCES += main.cpp\
        mainwindow.cpp \
    libdmtx/detector.c \
    libdmtx/dmtx.c \
    libdmtx/dmtxbytelist.c \
    libdmtx/dmtxdecode.c \
    libdmtx/dmtxdecodescheme.c \
    libdmtx/dmtximage.c \
    libdmtx/dmtxmatrix3.c \
    libdmtx/dmtxmessage.c \
    libdmtx/dmtxplacemod.c \
    libdmtx/dmtxreedsol.c \
    libdmtx/dmtxregion.c \
    libdmtx/dmtxscangrid.c \
    libdmtx/dmtxsymbol.c \
    libdmtx/dmtxtime.c \
    libdmtx/dmtxvector2.c

HEADERS  += mainwindow.h \
    libdmtx/detector.h \
    libdmtx/dmtx.h \
    libdmtx/dmtxstatic.h

FORMS    += mainwindow.ui




INCLUDEPATH += /usr/local/include
LIBS += /usr/local/lib/libraspicam.so

INCLUDEPATH += /usr/include
LIBS += /usr/lib/libwiringPi.so


RC_FILE = myapp.rc

DISTFILES +=

RESOURCES += \
    images.qrc

