#ifndef __CONNECT_FUNC_H__
#define __CONNECT_FUNC_H__

#include <WiFi.h>
#include <WiFiUdp.h>

void udp_tx(const char * host, const int udp_port, WiFiUDP *udp, MOTO_INFO *moto);


#endif