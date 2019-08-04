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
    get_dst_mac_addr.h \
    get_my_mac_addr.h


PRECOMPILED_HEADER = initheader.h
