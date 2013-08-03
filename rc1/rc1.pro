#-------------------------------------------------
#
# Project created by QtCreator 2013-07-19T17:04:33
#
#-------------------------------------------------

QT       += core gui opengl network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = rc1
TEMPLATE = app

INCLUDEPATH += comm/libofqf

SOURCES += main.cpp\
    view.cpp \
    storage.cpp \
    conf/layoutmodel.cpp \
    event/eventhandlerrect.cpp \
    comm/senderdebug.cpp \
    test/unittest.cpp \
    point.cpp \
    paint/paintbgshapes.cpp \
    paint/paintshapes.cpp \
    paint/paintstat.cpp \
    paint/pointpaintshape.cpp \
    comm/libofqf/qosctypes.cpp \
    comm/libofqf/qosctcpserverthread.cpp \
    comm/libofqf/qosctcpserver.cpp \
    comm/libofqf/qosctcpclient.cpp \
    comm/libofqf/qoscserver.cpp \
    comm/libofqf/qoscproxyinterface.cpp \
    comm/libofqf/qoscproxy.cpp \
    comm/libofqf/qoscmsgparser.cpp \
    comm/libofqf/qoscclient.cpp \
    comm/senderoscpuredata.cpp

HEADERS  += \
    view.h \
    storage.h \
    conf/layoutmodel.h \
    event/eventhandlerrect.h \
    comm/isender.h \
    event/ieventhandler.h \
    comm/senderdebug.h \
    test/unittest.h \
    iview.h \
    point.h \
    paint/ipaint.h \
    paint/ipointpaint.h \
    paint/paintbgshapes.h \
    paint/paintshapes.h \
    paint/paintstat.h \
    paint/pointpaintshape.h \
    comm/libofqf/qosctypes.h \
    comm/libofqf/qosctcpserverthread.h \
    comm/libofqf/qosctcpserver.h \
    comm/libofqf/qosctcpclient.h \
    comm/libofqf/qoscserverinterface.h \
    comm/libofqf/qoscserver.h \
    comm/libofqf/qoscproxyinterface.h \
    comm/libofqf/qoscproxy.h \
    comm/libofqf/qoscmsgparser.h \
    comm/libofqf/qoscclientinterface.h \
    comm/libofqf/qoscclient.h \
    comm/senderoscpuredata.h

OTHER_FILES += \
    android/res/values-ru/strings.xml \
    android/res/values-nb/strings.xml \
    android/res/layout/splash.xml \
    android/res/values-zh-rTW/strings.xml \
    android/res/values-pl/strings.xml \
    android/res/values-it/strings.xml \
    android/res/values-de/strings.xml \
    android/res/values-rs/strings.xml \
    android/res/values/libs.xml \
    android/res/values/strings.xml \
    android/res/values-fr/strings.xml \
    android/res/values-fa/strings.xml \
    android/res/values-id/strings.xml \
    android/res/values-ms/strings.xml \
    android/res/values-ro/strings.xml \
    android/res/values-el/strings.xml \
    android/res/values-et/strings.xml \
    android/res/values-zh-rCN/strings.xml \
    android/res/values-ja/strings.xml \
    android/res/values-es/strings.xml \
    android/res/values-nl/strings.xml \
    android/res/values-pt-rBR/strings.xml \
    android/AndroidManifest.xml \
    android/version.xml \
    android/src/org/qtproject/qt5/android/bindings/QtApplication.java \
    android/src/org/qtproject/qt5/android/bindings/QtActivity.java \
    android/src/org/kde/necessitas/ministro/IMinistro.aidl \
    android/src/org/kde/necessitas/ministro/IMinistroCallback.aidl
