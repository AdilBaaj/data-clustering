QT += core gui
QT += widgets

TARGET = dataVizualization
TEMPLATE = app

SOURCES += main.cpp \
    pcaclass.cpp \
    clusteringclass.cpp \
    data.cpp \
    dataset.cpp \
    visualization.cpp \
    datavisualizationprogram.cpp\
    WindowData.cpp \
    WindowPara.cpp

HEADERS += \
    pcaclass.h \
    clusteringclass.h \
    data.h \
    dataset.h \
    visualization.h \
    datavisualizationprogram.h\
    WindowData.h \
    WindowPara.h


#Add X11 library
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../opt/X11/lib/release/ -lX11
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../opt/X11/lib/debug/ -lX11
else:unix: LIBS += -L$$PWD/../../../../../opt/X11/lib/ -lX11

INCLUDEPATH += $$PWD/../../../../../opt/X11/include
DEPENDPATH += $$PWD/../../../../../opt/X11/include

#Add Eigen Library
INCLUDEPATH += /Users/Adil/Documents/Libraries_cpp/Eigen
DEPENDPATH += /Users/Adil/Documents/Libraries_cpp/Eigen

#Add dlib library
INCLUDEPATH += /Users/Adil/Documents/Libraries_cpp/dlib-18.17
DEPENDPATH += /Users/Adil/Documents/Libraries_cpp/dlib-18.17


#Add vtk library

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/release/ -lLSDyna.5.10.0
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/debug/ -lLSDyna.5.10.0
else:unix: LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/ -lLSDyna.5.10.0

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/release/ -lMapReduceMPI.5.10.0
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/debug/ -lMapReduceMPI.5.10.0
else:unix: LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/ -lMapReduceMPI.5.10.0

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/release/ -lmpistubs.5.10.0
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/debug/ -lmpistubs.5.10.0
else:unix: LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/ -lmpistubs.5.10.0

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/release/ -lQVTK.5.10.0
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/debug/ -lQVTK.5.10.0
else:unix: LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/ -lQVTK.5.10.0

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/release/ -lvtkalglib.5.10.0
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/debug/ -lvtkalglib.5.10.0
else:unix: LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/ -lvtkalglib.5.10.0

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/release/ -lvtkCharts.5.10.0
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/debug/ -lvtkCharts.5.10.0
else:unix: LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/ -lvtkCharts.5.10.0

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/release/ -lvtkCommon.5.10.0
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/debug/ -lvtkCommon.5.10.0
else:unix: LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/ -lvtkCommon.5.10.0

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/release/ -lvtkDICOMParser.5.10.0
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/debug/ -lvtkDICOMParser.5.10.0
else:unix: LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/ -lvtkDICOMParser.5.10.0

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/release/ -lvtkexoIIc.5.10.0
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/debug/ -lvtkexoIIc.5.10.0
else:unix: LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/ -lvtkexoIIc.5.10.0

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/release/ -lvtkexpat.5.10.0
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/debug/ -lvtkexpat.5.10.0
else:unix: LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/ -lvtkexpat.5.10.0

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/release/ -lvtkFiltering.5.10.0
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/debug/ -lvtkFiltering.5.10.0
else:unix: LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/ -lvtkFiltering.5.10.0

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/release/ -lvtkfreetype.5.10.0
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/debug/ -lvtkfreetype.5.10.0
else:unix: LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/ -lvtkfreetype.5.10.0

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/release/ -lvtkftgl.5.10.0
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/debug/ -lvtkftgl.5.10.0
else:unix: LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/ -lvtkftgl.5.10.0

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/release/ -lvtkGenericFiltering
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/debug/ -lvtkGenericFiltering
else:unix: LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/ -lvtkGenericFiltering

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/release/ -lvtkGeovis
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/debug/ -lvtkGeovis
else:unix: LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/ -lvtkGeovis

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/release/ -lvtkGraphics
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/debug/ -lvtkGraphics
else:unix: LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/ -lvtkGraphics

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/release/ -lvtkhdf5_hl
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/debug/ -lvtkhdf5_hl
else:unix: LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/ -lvtkhdf5_hl

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/release/ -lvtkhdf5
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/debug/ -lvtkhdf5
else:unix: LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/ -lvtkhdf5

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/release/ -lvtkHybrid
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/debug/ -lvtkHybrid
else:unix: LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/ -lvtkHybrid

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/release/ -lvtkImaging
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/debug/ -lvtkImaging
else:unix: LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/ -lvtkImaging

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/release/ -lvtkInfovis
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/debug/ -lvtkInfovis
else:unix: LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/ -lvtkInfovis

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/release/ -lvtkIO
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/debug/ -lvtkIO
else:unix: LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/ -lvtkIO

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/release/ -lvtkjpeg
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/debug/ -lvtkjpeg
else:unix: LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/ -lvtkjpeg

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/release/ -lvtklibxml2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/debug/ -lvtklibxml2
else:unix: LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/ -lvtklibxml2

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/release/ -lvtkmetaio
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/debug/ -lvtkmetaio
else:unix: LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/ -lvtkmetaio

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/release/ -lvtkNetCDF_cxx
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/debug/ -lvtkNetCDF_cxx
else:unix: LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/ -lvtkNetCDF_cxx

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/release/ -lvtkNetCDF
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/debug/ -lvtkNetCDF
else:unix: LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/ -lvtkNetCDF

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/release/ -lvtkpng
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/debug/ -lvtkpng
else:unix: LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/ -lvtkpng

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/release/ -lvtkproj4
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/debug/ -lvtkproj4
else:unix: LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/ -lvtkproj4

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/release/ -lvtkRendering
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/debug/ -lvtkRendering
else:unix: LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/ -lvtkRendering

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/release/ -lvtksqlite
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/debug/ -lvtksqlite
else:unix: LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/ -lvtksqlite

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/release/ -lvtksys
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/debug/ -lvtksys
else:unix: LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/ -lvtksys

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/release/ -lvtktiff
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/debug/ -lvtktiff
else:unix: LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/ -lvtktiff

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/release/ -lvtkViews
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/debug/ -lvtkViews
else:unix: LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/ -lvtkViews

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/release/ -lvtkVolumeRendering
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/debug/ -lvtkVolumeRendering
else:unix: LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/ -lvtkVolumeRendering

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/release/ -lvtkWidgets
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/debug/ -lvtkWidgets
else:unix: LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/ -lvtkWidgets

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/release/ -lvtkzlib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/debug/ -lvtkzlib
else:unix: LIBS += -L$$PWD/../../Libraries_cpp/vtk/lib/ -lvtkzlib

INCLUDEPATH += $$PWD/../../Libraries_cpp/vtk/include
DEPENDPATH += $$PWD/../../Libraries_cpp/vtk/include
