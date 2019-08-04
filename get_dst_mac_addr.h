#pragma once
#include "initheader.h"
#include <pcap.h>
#include <stdio.h>
#include <stdint.h>

/* resolution IP to MAC  */
void get_dst_mac_addr(u_char* send_mac,u_char* send_ip, u_char* dst_MAC_store,u_char* target_ip, pcap_t* handle);

void get_dst_mac_addr(u_char* send_mac,u_char* send_ip, u_char* dst_MAC_store,u_char* target_ip, pcap_t* handle){

    u_char broad_cast_mac[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    u_int16_t request = 0x0100;

    u_char* buf = arp_packet_maker(send_mac, send_ip, broad_cast_mac, target_ip, request);

    int res = pcap_sendpacket(handle,buf,42);
    if(res==-1){
        printf("Send Packet Error\n");
    }

    struct pcap_pkthdr* header;
    const u_char* packet;
    pcap_next_ex(handle, &header, &packet);

    memcpy(dst_MAC_store,(packet+6),sizeof(uint8_t)*6);

}
