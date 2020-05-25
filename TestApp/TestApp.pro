QT += core gui widgets

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += qt
CONFIG += thread

DEFINES += "_GNU_SOURCE"
DEFINES += "__USE_UNIX98"
DEFINES += "NWKMGR_SRVR"
DEFINES += "ZG_SECURE_ENABLED"
DEFINES += "MAX_BINDING_CLUSTER_IDS"
DEFINES += "ZCL_ON_OFF"
DEFINES += "ZCL_STANDALONE"
DEFINES += "SERVER_NAME=NWK_MGR"
DEFINES += "__APP_UI__"
DEFINES += "HAVE_SYS_POLL_H"
DEFINES += "HAVE_SYS_UIO_H"
DEFINES += "HAVE_MALLOC_H"
#DEFINES += "USER_INTERFACE_H"

SOURCES += \
        ./google/protobuf-c/protobuf-c-data-buffer.c \
        ./google/protobuf-c/protobuf-c-dispatch.c \
        ./google/protobuf-c/protobuf-c-rpc.c \
        ./google/protobuf-c/protobuf-c.c \
        ../engines/actions_engine.c \
        ../engines/attribute_engine.c \
        ../engines/commissioning_engine.c \
        ../engines/device_list_engine.c \
        ../engines/group_scene_engine.c \
        ../engines/network_info_engine.c \
        ../engines/ota_engine.c \
        ../engines/sensor_engine.c \
        ../engines/state_reflector.c \
        ../engines/system_engine.c \
        ../framework/data_structures.c \
        ../framework/macros.c \
        ../framework/polling.c \
        ../framework/socket_interface.c \
        ../framework/tcp_client.c \
        ../framework/timer_utils.c \
        ../framework/user_interface.c \
        ../gateway.pb-c.c \
        ../nwkmgr.pb-c.c \
        ../otasrvr.pb-c.c \
        cpp_connect_c.cpp \
        main.cpp \
        mainwindow.cpp \
        #zigbee.c\
        zigbee.cpp \
        uiconnection.cpp

HEADERS += \
    ../engines/actions_engine.h \
    ../engines/attribute_engine.h \
    ../engines/commissioning_engine.h \
    ../engines/device_list_engine.h \
    ../engines/group_scene_engine.h \
    ../engines/network_info_engine.h \
    ../engines/ota_engine.h \
    ../engines/sensor_engine.h \
    ../engines/state_reflector.h \
    ../engines/system_engine.h \
    ../framework/data_structures.h \
    ../framework/macros.h \
    ../framework/polling.h \
    ../framework/socket_interface.h \
    ../framework/tcp_client.h \
    ../framework/timer_utils.h \
    ../framework/types.h \
    ../framework/user_interface.h \
    ../gateway.pb-c.h \
    ../hal_types.h \
    ../nwkmgr.pb-c.h \
    ../otasrvr.pb-c.h \
    cpp_connect_c.h \
    extern.h \
    mainwindow.h \
    uiconnection.h \
    zigbee.h

INCLUDEPATH += \
 ../ \
 ../framework \
 ../engines \
 ./google/protobuf-c/ \

#unix|win32: LIBS += -lprotobuf-c

FORMS += \
    mainwindow.ui \
    uiconnection.ui

DISTFILES += \
    images/logo-no-text.png

