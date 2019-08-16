#pragma once

#include <stdlib.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <pcap.h>

#include "ethernet_header.h"
#include "get_my_mac_addr.h"
#include "arp_packet_format.h"
#include "arp_request_maker.h"
#include "arp_reply_maker.h"
#include "send_arp.h"

void usage();
void usage(){
    printf("syntax error!\n");
    printf("syntax : send_arp <interface> <sender ip> <target ip>\n");
    printf("example : send_arp eth0 192.168.10.5 192.168.10.1\n");
}

