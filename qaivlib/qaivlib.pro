#/******************************************************************************
#** This file is part of qadvanceditemviews.
#**
#** Copyright (c) 2011-2013 Martin Hoppe martin@2x2hoppe.de
#**
#** qadvanceditemviews is free software: you can redistribute it
#** and/or modify it under the terms of the GNU Lesser General
#** Public License as published by the Free Software Foundation,
#** either version 3 of the License, or (at your option) any
#** later version.
#**
#** qadvanceditemviews is distributed in the hope that it will be
#** useful, but WITHOUT ANY WARRANTY; without even the implied
#** warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#** See the GNU General Public License for more details.
#**
#** You should have received a copy of the GNU Lesser General Public
#** License along with qadvanceditemviews.
#** If not, see <http://www.gnu.org/licenses/>.
#******************************************************************************/

TEMPLATE = lib
TARGET = qaivlib

equals(QT_MAJOR_VERSION, 4){
    QT += core gui
}
equals(QT_MAJOR_VERSION, 5){
    QT += core widgets
}

CONFIG += debug_and_release
CONFIG += lib
CONFIG += dll
CONFIG += create_prl
CONFIG += link_prl
include(../common.pri)
unix {
    DEFINES += QAIVLIB_LIBRARY
}
else {
    DEFINES += QT_LARGEFILE_SUPPORT QT_DLL QAIVLIB_LIBRARY
}

EXTRA_FILES += \
    $$PWD/qadvancedheaderview.h \
$$PWD/qconditionaldecorationdialog.h \
$$PWD/qconditionaldecorationproxymodel.h \
$$PWD/qfiltermodel.h \
$$PWD/qfiltermodelproxy.h \
$$PWD/qfilterviewconnector.h \
$$PWD/qgroupingproxymodel.h \
$$PWD/qconditionaldecoration.h \
$$PWD/qfixedrowstableview.h \
$$PWD/qmimedatautil.h \
$$PWD/qrangefilter.h \
$$PWD/quniquevaluesproxymodel.h \
$$PWD/qselectionlistfilter.h \
$$PWD/qtablemodelwriter.h \
$$PWD/qtextfilter.h \
$$PWD/qvaluefilter.h \
$$PWD/qaivlib_global.h \
$$PWD/qadvancedtableview.h \
$$PWD/qabstractfilter.h \
$$PWD/qabstractfiltermodel.h \
$$PWD/qabstractfilterproxymodel.h \
$$PWD/qabstractmodelitemdecoration.h

win32 {
    EXTRA_FILES ~= s,/,\\,g
    BUILD_DIR ~= s,/,\\,g
    DESTDIR = $${DEST_LIBS}
    DEST_DIR = $$DESTDIR/include
    DEST_DIR ~= s,/,\\,g
    DEST_INCLUDE_DIR ~= s,/,\\,g

    for(FILE,EXTRA_FILES){
        QMAKE_POST_LINK += $$QMAKE_COPY \"$$FILE\" \"$${DEST_INCLUDE_DIR}\" $$escape_expand(\\n\\t)
    }
    QMAKE_POST_LINK += $$QMAKE_COPY_DIR \"$${DEST_INCLUDE_DIR}\" \"$${DEST_DIR}\"
}


PRECOMPILED_HEADER = stdafx.h
HEADERS += $$PWD/qabstractfilter.h \
    $$PWD/qabstractfiltermodel.h \
    $$PWD/qabstractfilterproxymodel.h \
    $$PWD/qabstractmodelitemdecoration.h \
    $$PWD/qadvancedheaderview.h \
    $$PWD/qadvancedheaderview_p.h \
    $$PWD/qadvancedtableview.h \
    $$PWD/qadvancedtableview_p.h \
    $$PWD/qaiv.h \
    $$PWD/qaivlib_global.h \
    $$PWD/qautofilter.h \
    $$PWD/qautofilter_p.h \
    $$PWD/qcheckstateproxymodel.h \
    $$PWD/qclickablelabel.h \
    $$PWD/qconditionaldecoration.h \
    $$PWD/qconditionaldecorationdialog.h \
    $$PWD/qconditionaldecorationdialog_p.h \
    $$PWD/qconditionaldecorationproxymodel.h \
    $$PWD/qfiltereditorpopupwidget.h \
    $$PWD/qfiltereditorwidget.h \
    $$PWD/qfiltergroup.h \
    $$PWD/qfiltermodel.h \
    $$PWD/qfiltermodelproxy.h \
    $$PWD/qfilterview.h \
    $$PWD/qfilterviewconnector.h \
    $$PWD/qfilterviewitemdelegate.h \
    $$PWD/qfixedrowsheaderview.h \
    $$PWD/qfixedrowstableview.h \
    $$PWD/qgroupingproxymodel.h \
    $$PWD/qgroupingproxymodel_p.h \
    $$PWD/qheaderviewconnector.h \
    $$PWD/qmimedatautil.h \
    $$PWD/qrangefilter.h \
    $$PWD/qrangefilter_p.h \
    $$PWD/qregexpfilter.h \
    $$PWD/qregexpfilter_p.h \
    $$PWD/qsearchbar.h \
    $$PWD/qsearchbar_p.h \
    $$PWD/qselectionlistfilter.h \
    $$PWD/qselectionlistfilter_p.h \
    $$PWD/qshareditemselectionmodel.h \
    $$PWD/qsinglecolumnproxymodel.h \
    $$PWD/qtablemodelcsvwriter_p.h \
    $$PWD/qtablemodelexcelmlwriter_p.h \
    $$PWD/qtablemodelexportpushbutton.h \
    $$PWD/qtablemodelhtmlwriter_p.h \
    $$PWD/qtablemodelwordmlwriter_p.h \
    $$PWD/qtablemodelwriter.h \
    $$PWD/qtextfilter.h \
    $$PWD/qtextfilter_p.h \
    $$PWD/quniquevaluesproxymodel.h \
    $$PWD/qvaluefilter.h \
    $$PWD/qvaluefilter_p.h \
    $$PWD/stdafx.h
SOURCES += $$PWD/qabstractfilter.cpp \
    $$PWD/qabstractfiltermodel.cpp \
    $$PWD/qabstractfilterproxymodel.cpp \
    $$PWD/qabstractmodelitemdecoration.cpp \
    $$PWD/qadvancedheaderview.cpp \
    $$PWD/qadvancedtableview.cpp \
    $$PWD/qaiv.cpp \
    $$PWD/qautofilter.cpp \
    $$PWD/qcheckstateproxymodel.cpp \
    $$PWD/qclickablelabel.cpp \
    $$PWD/qconditionaldecoration.cpp \
    $$PWD/qconditionaldecorationdialog.cpp \
    $$PWD/qconditionaldecorationproxymodel.cpp \
    $$PWD/qfiltereditorpopupwidget.cpp \
    $$PWD/qfiltereditorwidget.cpp \
    $$PWD/qfiltergroup.cpp \
    $$PWD/qfiltermodel.cpp \
    $$PWD/qfiltermodelproxy.cpp \
    $$PWD/qfilterview.cpp \
    $$PWD/qfilterviewconnector.cpp \
    $$PWD/qfilterviewitemdelegate.cpp \
    $$PWD/qfixedrowsheaderview.cpp \
    $$PWD/qfixedrowstableview.cpp \
    $$PWD/qgroupingproxymodel.cpp \
    $$PWD/qheaderviewconnector.cpp \
    $$PWD/qmimedatautil.cpp \
    $$PWD/qrangefilter.cpp \
    $$PWD/qregexpfilter.cpp \
    $$PWD/qsearchbar.cpp \
    $$PWD/qselectionlistfilter.cpp \
    $$PWD/qshareditemselectionmodel.cpp \
    $$PWD/qsinglecolumnproxymodel.cpp \
    $$PWD/qtablemodelcsvwriter.cpp \
    $$PWD/qtablemodelexcelmlwriter.cpp \
    $$PWD/qtablemodelexportpushbutton.cpp \
    $$PWD/qtablemodeltmlwriter.cpp \
    $$PWD/qtablemodelwordmlwriter.cpp \
    $$PWD/qtablemodelwriter.cpp \
    $$PWD/qtextfilter.cpp \
    $$PWD/quniquevaluesproxymodel.cpp \
    $$PWD/qvaluefilter.cpp \
    $$PWD/stdafx.cpp
FORMS += $$PWD/qadvancedtableview.ui \
    $$PWD/qconditionaldecorationdialog.ui \
    $$PWD/qsearchbar.ui
TRANSLATIONS += $$PWD/qaivlib_de.ts
RESOURCES += $$PWD/qaiv.qrc

