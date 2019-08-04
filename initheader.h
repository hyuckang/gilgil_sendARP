#pragma once

#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <pcap.h>
#include <arpa/inet.h>
#include <stdlib.h>

#include "get_my_mac_addr.h"
#include "arp_packet_format.h"
#include "arp_packet_maker.h"
#include "get_dst_mac_addr.h"
#include "ethernet_header.h"
