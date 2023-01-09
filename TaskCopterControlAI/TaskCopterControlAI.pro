QT -= gui
QT += serialport

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

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
SOURCES += $$PWD/../sources/MachineControlAI.cpp
SOURCES += $$PWD/../sources/interactionsppr.cpp

SOURCES += \
    main.cpp

INCLUDEPATH += $$PWD/../sources

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

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

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
HEADERS += $$PWD/../sources/MachineControlAI.h
HEADERS += $$PWD/../sources/interactionsppr.h
