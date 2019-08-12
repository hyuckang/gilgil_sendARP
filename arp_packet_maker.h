#pragma once
#include "initheader.h"

u_char* arp_packet_maker(u_char* send_mac, u_char* send_ip, u_char* target_mac, u_char* target_ip, u_int16_t op_code);

u_char* arp_packet_maker(u_char* send_mac, u_char* send_ip, u_char* target_mac, u_char* target_ip, u_int16_t op_code){

    ether_hdr eth_hdr;
    arp_ether_ipv4 arp_hdr;
    u_char* packet = (u_char*) malloc(sizeof(eth_hdr) + sizeof(arp_hdr));

    memcpy(eth_hdr.src_addr, send_mac, sizeof(eth_hdr.src_addr));
    memcpy(eth_hdr.dst_addr, target_mac, sizeof(eth_hdr.dst_addr));

    arp_hdr.op_code = op_code;
    memcpy(arp_hdr.send_hw_addr, send_mac, sizeof(arp_hdr.send_hw_addr));

    if(op_code==0x0100){// ARP Request Packet
        for(int i=0;i<6;i++) arp_hdr.target_hw_addr[i] = 0x00;
        for(int i=0;i<4;i++) arp_hdr.send_ip_addr[i] =0x00;
        memcpy(arp_hdr.target_ip_addr, send_ip, sizeof(arp_hdr.target_ip_addr));
    }

    if(op_code==0x0200){// ARP Reply Packet
        memcpy(arp_hdr.target_hw_addr, target_mac, sizeof(arp_hdr.target_hw_addr));
        memcpy(arp_hdr.send_ip_addr, target_ip, sizeof(arp_hdr.send_ip_addr));
        memcpy(arp_hdr.target_ip_addr,send_ip,sizeof(arp_hdr.target_ip_addr));
    }

    memcpy(packet, &eth_hdr, sizeof(eth_hdr));
    memcpy(packet+sizeof(eth_hdr), &arp_hdr, sizeof(arp_hdr));

    /* test code
    if(op_code==0x0100) printf("ARP Request packet\n");
    if(op_code==0x0200) printf("ARP Reply packet\n");
    printf("eth src addr : %2x:%2x:%2x:%2x:%2x:%2x\n",eth_hdr.src_addr[0],eth_hdr.src_addr[1],eth_hdr.src_addr[2],eth_hdr.src_addr[3],eth_hdr.src_addr[4],eth_hdr.src_addr[5]);
    printf("eth dst_addr : %2x:%2x:%2x:%2x:%2x:%2x\n",eth_hdr.dst_addr[0],eth_hdr.dst_addr[1],eth_hdr.dst_addr[2],eth_hdr.dst_addr[3],eth_hdr.dst_addr[4],eth_hdr.dst_addr[5]);
    printf("send_hw_addr : %2x:%2x:%2x:%2x:%2x:%2x\n",arp_hdr.send_hw_addr[0],arp_hdr.send_hw_addr[1],arp_hdr.send_hw_addr[2],arp_hdr.send_hw_addr[3],arp_hdr.send_hw_addr[4],arp_hdr.send_hw_addr[5]);
    printf("send_ip_addr : %2d:%2d:%2d:%2d\n",arp_hdr.send_ip_addr[0],arp_hdr.send_ip_addr[1],arp_hdr.send_ip_addr[2],arp_hdr.send_ip_addr[3]);
    printf("target_hw_addr : %2x:%2x:%2x:%2x:%2x:%2x\n",arp_hdr.target_hw_addr[0],arp_hdr.target_hw_addr[1],arp_hdr.target_hw_addr[2],arp_hdr.target_hw_addr[3],arp_hdr.target_hw_addr[4],arp_hdr.target_hw_addr[5]);
    printf("target_ip_addr : %2d:%2d:%2d:%2d\n",arp_hdr.target_ip_addr[0],arp_hdr.target_ip_addr[1],arp_hdr.target_ip_addr[2],arp_hdr.target_ip_addr[3]);
    printf("\n");
    */
    return packet;
}
