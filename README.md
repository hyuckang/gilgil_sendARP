# gilgil_sendARP
APR Spoofing의 전 단계인 send ARP이다.
ARP Spoofing이 되기 위해서는 패킷을 릴레이까지 해주어야하기 때문에 send ARP는 ARP Spoofing이 아니다.
 
send_ARP eth0 192.168.10.2 192.168.10.1 으로 실행하게 되면

eth0에서 192.168.10.2 로 공격자의 mac address(eth0)과 192.168.10.2로 이루어진 ARP Reply 패킷이 1초 간격으로 전송된다.
 
결과적으로 192.168.10.2 의 arp table이 감염되어 192.168.10.1 으로 가는 패킷이 공격자에게 오게된다.

