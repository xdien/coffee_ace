#-------------------------------------------------
#
# Project created by QtCreator 2015-01-23T20:15:57
#
#-------------------------------------------------
include(../common.pri)
QT       += core gui sql xml printsupport qml quick


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport
TARGET = coffee_ace
TEMPLATE = app
INCLUDEPATH += $$PWD/../include
DEPENDPATH  += $$PWD/../include
QTPLUGIN += qwindows
EXTRA_DIR     += $$PWD/reports
DEST_DIR       = $${DEST_BINS}
REPORTS_DIR    = $${DEST_DIR}

unix:{
    LIBS += -L$${DEST_LIBS} -llimereport
    contains(CONFIG,zint){
        LIBS += -L$${DEST_LIBS} -lQtZint
    }
    contains(CONFIG,qaivlib){
        LIBS += -L$${DEST_LIBS} -lqaivlib
    }
    DESTDIR = $$DEST_DIR
    QMAKE_POST_LINK += $$QMAKE_COPY_DIR $$quote($$EXTRA_DIR) $$quote($$REPORTS_DIR) $$escape_expand(\n\t)
linux{
    #Link share lib to ../lib rpath
    QMAKE_LFLAGS += -Wl,--rpath=\\\$\$ORIGIN
    QMAKE_LFLAGS += -Wl,--rpath=\\\$\$ORIGIN/lib
    QMAKE_LFLAGS += -Wl,--rpath=\\\$\$ORIGIN/../lib
    QMAKE_LFLAGS_RPATH += #. .. ./libs
    QT += xlsx
    DESTDIR = $${DEST_LIBS}
    DEST_DIR = $$DESTDIR/include
    LIBS += -L$${DEST_LIBS} -llimereport -lqaivlib

}
    target.path = $${DEST_DIR}
    INSTALLS = target
}


CONFIG (debug, debug|release) {
 mac: TARGET = $$join(TARGET,,,_debug)
 win32: TARGET = $$join(TARGET,,,d)
}
win32 {
    EXTRA_FILES ~= s,/,\\,g
    BUILD_DIR ~= s,/,\\,g
    DESTDIR = $${DEST_LIBS}
    DEST_DIR = $$DESTDIR/include

    #DEST_DIR ~= s,/,\\,g
    DEST_INCLUDE_DIR ~= s,/,\\,g
QT += xlsx
LIBS += -L$${DEST_LIBS} -llimereport -lqaivlib
    #for(FILE,EXTRA_FILES){
    #    QMAKE_POST_LINK += $$QMAKE_COPY \"$$FILE\" \"$${DEST_INCLUDE_DIR}\" $$escape_expand(\\n\\t)
    #}
    #QMAKE_POST_LINK += $$QMAKE_COPY_DIR \"$${DEST_INCLUDE_DIR}\" \"$${DEST_DIR}\"
}
static { # everything below takes effect with CONFIG = static
 CONFIG+= static
 CONFIG += staticlib # this is needed if you create a static library, not a static executable
 DEFINES+= STATIC
 message("~~~ static build ~~~") # this is for information, that the static build is done
 mac: TARGET = $$join(TARGET,,,_static) #this adds an _static in the end, so you can seperate static build
#from non static build
 win32:
{
TARGET = $$join(TARGET,,,s)
INCLUDEPATH += -$(QTDIR)\plugins\platforms\
}
#non static build
}

SOURCES += main.cpp\
        mainwindow.cpp \
    dialog_setting.cpp \
    config/config_sqlconnect.cpp \
    login.cpp \
    about.cpp \
    utils/manageindex.cpp \
    config/common.cpp \
    chucnang/formphanquyen.cpp \
    chucnang/formquyen.cpp \
    chucnang/formtaikhoan.cpp \
    chucnang/chitiet/dialogdoimatkhau.cpp \
    utils/taikhoan.cpp \
    utils/quyen.cpp

HEADERS  += mainwindow.h \
    dialog_setting.h \
    config/config_sqlconnect.h \
    login.h \
    about.h \
    utils/manageindex.h \
    config/common.h \
    chucnang/formphanquyen.h \
    chucnang/formquyen.h \
    chucnang/formtaikhoan.h \
    chucnang/chitiet/dialogdoimatkhau.h \
    utils/taikhoan.h \
    utils/quyen.h

FORMS    += mainwindow.ui \
    dialog_setting.ui \
    login.ui \
    about.ui \
    chucnang/formquyen.ui \
    chucnang/formtaikhoan.ui \
    chucnang/formphanquyen.ui \
    chucnang/chitiet/dialogdoimatkhau.ui


DISTFILES += \
    img/checked.png \
    banhang.qml

RESOURCES += \
    img/img.qrc \
    app.qrc

