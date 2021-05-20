QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addflightform.cpp \
    flightform.cpp \
    main.cpp \
    mainwindow.cpp \
    passform.cpp \
    useraddform.cpp

HEADERS += \
    AVL.h \
    HashTable.h \
    List.h \
    MyStructs.h \
    addflightform.h \
    flightform.h \
    mainwindow.h \
    passform.h \
    useraddform.h

FORMS += \
    addflightform.ui \
    flightform.ui \
    mainwindow.ui \
    passform.ui \
    useraddform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES +=

win32:RC_ICONS += "ico.ico"
