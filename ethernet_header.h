#pragma once
#include "initheader.h"

#define ETH_P_ARP 0x0608    /* Address Resolution packet */
#define ETHER_ADDR_LEN  6   /* MAC Address Size */

/* Ethernet frame header */
typedef struct {
    uint8_t dst_addr[ETHER_ADDR_LEN]; /* Destination hardware address */
    uint8_t src_addr[ETHER_ADDR_LEN];  /* Source hardware address */
    uint16_t frame_type = ETH_P_ARP;   /* ARP */
}ether_hdr;
