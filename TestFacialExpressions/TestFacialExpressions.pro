QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_facialexpressions.cpp

# configure opencv
INCLUDEPATH += $$PWD/../../libs/opencv450/include
LIBS += -L$$PWD/../../libs/opencv450/lib/Release \
    -lopencv_calib3d450 \
    -lopencv_core450 \
    -lopencv_dnn450 \
    -lopencv_features2d450 \
    -lopencv_flann450 \
    -lopencv_gapi450 \
    -lopencv_highgui450 \
    -lopencv_imgcodecs450 \
    -lopencv_imgproc450 \
    -lopencv_ml450 \
    -lopencv_objdetect450 \
    -lopencv_photo450 \
    -lopencv_stitching450 \
    -lopencv_video450 \
    -lopencv_videoio450 \

# configure openpose
INCLUDEPATH += $$PWD/../../libs/openpose/include
LIBS += $$PWD/../../libs/openpose/lib/openpose.lib

# configure gflags
INCLUDEPATH += $$PWD/../../libs
LIBS += $$PWD/../../libs/gflags/lib/gflags.lib

INCLUDEPATH += $$PWD/../sources
#
SOURCES += $$PWD/../sources/BehaviorProcessor.cpp
SOURCES += $$PWD/../sources/EyeDetector.cpp
SOURCES += $$PWD/../sources/Point3f3i.cpp
SOURCES += $$PWD/../sources/PoseProcessor.cpp
SOURCES += $$PWD/../sources/Skeleton.cpp
SOURCES += $$PWD/../sources/SkeletonExtractor.cpp
SOURCES += $$PWD/../sources/SpeedReg.cpp
SOURCES += $$PWD/../sources/Stopwatch.cpp
SOURCES += $$PWD/../sources/YoloDetector.cpp
SOURCES += $$PWD/../sources/facekeypoint.cpp
SOURCES += $$PWD/../sources/faceprocessor.cpp
SOURCES += $$PWD/../sources/platform.cpp
#
HEADERS += $$PWD/../sources/BehaviorProcessor.h
HEADERS += $$PWD/../sources/EyeDetector.h
HEADERS += $$PWD/../sources/Point3f3i.h
HEADERS += $$PWD/../sources/PoseProcessor.h
HEADERS += $$PWD/../sources/Skeleton.h
HEADERS += $$PWD/../sources/SkeletonExtractor.h
HEADERS += $$PWD/../sources/SpeedReg.h
HEADERS += $$PWD/../sources/Stopwatch.h
HEADERS += $$PWD/../sources/YoloDetector.h
HEADERS += $$PWD/../sources/facekeypoint.h
HEADERS += $$PWD/../sources/faceprocessor.h
HEADERS += $$PWD/../sources/mini.h
HEADERS += $$PWD/../sources/platform.h
