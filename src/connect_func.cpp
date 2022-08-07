#include <Arduino.h>
#include "common.h"
#include <WiFi.h>
#include <WiFiAP.h>

void udp_tx(const char * host, const int udp_port, WiFiUDP *udp, MOTO_INFO *moto)
{
    if (moto == NULL){
        return ;
    }
    char wbuf[4];
    memset(wbuf, '\0', sizeof(wbuf));
    #if 1
    wbuf[0] = moto->left_dir;
    wbuf[1] = moto->left_duty;
    wbuf[2] = moto->right_dir;
    wbuf[3] = moto->right_duty;
    #endif
    udp->beginPacket(host, udp_port);
    for (int i = 0; i < 4; i++)
    {
        udp->print(wbuf[i]);
    }
    //udp->print((char *)moto);
    udp->endPacket();
}