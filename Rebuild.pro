QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Source/Class_Time.cpp \
    Source/clock.cpp \
    Source/date.cpp \
    Source/fileexception.cpp \
    Source/mycontainer.cpp \
    Source/myexception.cpp \
    Source/nullptrexception.cpp \
    Source/rangeexception.cpp \
    Source/train.cpp \
    main.cpp \
    mwindow.cpp \
    newelement.cpp \
    search.cpp

HEADERS += \
    Source/Class_Time.h \
    Source/clock.h \
    Source/date.h \
    Source/fileexception.h \
    Source/mycontainer.h \
    Source/myexception.h \
    Source/myiterator.h \
    Source/nullptrexception.h \
    Source/rangeexception.h \
    Source/train.h \
    mwindow.h \
    newelement.h \
    search.h

FORMS += \
    mwindow.ui \
    newelement.ui \
    search.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES +=
