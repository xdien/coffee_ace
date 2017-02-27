TEMPLATE = subdirs
include(common.pri)
#contains(CONFIG, zint){
#    SUBDIRS += 3rdparty
#}

SUBDIRS += \
        limereport \
        qaivlib \
        app
CONFIG   += ordered c++11
