#include <Arduino.h>
#include <WiFi.h>
#include <WiFiAP.h>

#include "common.h"
#ifdef TUTU_AP

WiFiAPClass WiFiAP;
WiFiUDP Udp;
MOTO_INFO moto;

// Set these to your desired credentials.
const char *SSID = "TUTUCAR";
const char *PASSWORD = "sdc.2200";
const char *HOSTNAME = "tutu_ap";

uint8_t x=1;
IPAddress local_IP(192, 168, 168, 1);  
IPAddress gateway(192, 168, 168, 1);
IPAddress subnet(255, 255, 255, 0);

/* UDP param */
const int udp_port = 1122;
char rbuf[128];

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");

  /* init wifi AP */
  WiFiAP.softAPConfig(local_IP, gateway, subnet);
  WiFiAP.softAPsetHostname(HOSTNAME);
  WiFiAP.softAP(SSID, PASSWORD);

  Serial.println("\n SSID : ");
  Serial.println(SSID);
  Serial.println("\n IP   : ");
  Serial.println(WiFiAP.softAPIP());

  delay(2000);
  Serial.print("AP IP address: ");
  Serial.println(WiFiAP.softAPIP());
  Serial.print("softAP Broadcast IP: ");
  Serial.println(WiFiAP.softAPBroadcastIP());
  Serial.print("softAP NetworkID: ");
  Serial.println(WiFiAP.softAPNetworkID());
  Serial.print("softAP SubnetCIDR: ");
  Serial.println(WiFiAP.softAPSubnetCIDR());
  Serial.print("softAP Hostname: ");
  Serial.println(WiFiAP.softAPgetHostname());
  Serial.print("softAP macAddress: ");
  Serial.println(WiFiAP.softAPmacAddress());
  Serial.print("softAP StationNum: ");
  Serial.println(WiFiAP.softAPgetStationNum());

  Serial.println("AP started");

  /* init MOTO */
  init_moto_gpio();
  init_moto_pwm();
  Serial.println("init moto ...");

  /* init UDP */
  Udp.begin(udp_port);
  Serial.println("UDP linsting ...");

}


void loop() {
  int data_len = Udp.parsePacket();
  static uint16_t standby = 0;
  if (data_len){
    int len = Udp.read(rbuf, sizeof(rbuf));
    if (len > 0)
    {
      rbuf[len] = 0;
    }
    Serial.println("");
    for (int i = 0; i < len; i++){
      Serial.printf("%d(%#x) ", rbuf[i], rbuf[i]);
    }
    Serial.println("");
    if (len == 4)
    {
      moto.left_dir = rbuf[0];
      moto.left_duty = rbuf[1];
      moto.right_dir = rbuf[2];
      moto.right_duty = rbuf[3];
      /* FIXME */
      if (moto.left_duty == 0 && moto.right_duty == 0)
      {
        printf("ship pkt ...\n");
        standby = 1;
      }
      else
      {
        Serial.printf("moto : left  (dir, duty) = (%d, %d)\n", moto.left_dir, moto.left_duty);
        Serial.printf("moto : right (dir, duty) = (%d, %d)\n", moto.right_dir, moto.right_duty);
        Serial.println("");
        /* moto setting */
        moto_set_left(moto.left_dir, moto.left_duty);
        moto_set_right(moto.right_dir, moto.right_duty);
        delay(100);
        moto_set_left(moto.left_dir, 0);
        moto_set_right(moto.right_dir, 0);
        standby = 0;
      }
    }
  }
  /* FIXME */
#if 0
  else
  {
    if (standby == 0)
    {
      delay(100);
      moto_set_left(FORWARD, 0);
      moto_set_right(FORWARD, 0);
      standby = 1;
    }
  }
#endif
}
#endif