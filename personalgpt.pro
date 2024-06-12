QT       += core gui
QT +=network
QT += websockets
QT +=sql
QT +=charts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
RC_ICONS = openai-black.ico
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    abstractsqlmodel.cpp \
    chatbox.cpp \
    chatlabelsshow.cpp \
    chatlabeltag.cpp \
    chatloginmodel.cpp \
    chatmain.cpp \
    chatshowwidget.cpp \
    connecttoserve.cpp \
    loginsqlmodel.cpp \
    main.cpp \
    mainwindow.cpp \
    statusshow.cpp \
    udpsocketmodel.cpp \
    userinfo.cpp

HEADERS += \
    abstractsqlmodel.h \
    chatbox.h \
    chatlabelsshow.h \
    chatlabeltag.h \
    chatloginmodel.h \
    chatmain.h \
    chatshowwidget.h \
    connecttoserve.h \
    loginsqlmodel.h \
    mainwindow.h \
    statusshow.h \
    udpsocketmodel.h \
    userinfo.h

FORMS += \
    chatbox.ui \
    chatlabelsshow.ui \
    chatmain.ui \
    chatshowwidget.ui \
    mainwindow.ui \
    statusshow.ui \
    userinfo.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
