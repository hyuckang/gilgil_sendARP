TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lpcap
SOURCES += \
    main.cpp

HEADERS += \
    arp_packet_format.h \
    arp_packet_maker.h \
    ethernet_header.h \ \
    get_my_mac_addr.h \
    init.h \
    arp_request_maker.h \
    arp_reply_maker.h \
    send_arp.h


PRECOMPILED_HEADER = init.h
