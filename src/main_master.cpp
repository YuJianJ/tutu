#include <Arduino.h>
#include <WiFi.h>
#include <WiFiAP.h>

#include "common.h"
#ifdef TUTU_STA

WiFiUDP Udp;

// Set these to your desired credentials.
const char *SSID = "TUTUCAR";
const char *PASSWORD = "sdc.2200";

uint8_t x=1;

/* UDP param */
#define HOST_IP "192.168.168.1"
const int udp_port = 1122;
char rbuf[128];

MOTO_INFO moto_info;

void setup() {
  /* serial init */
  Serial.begin(115200);
  /* print soft version */
  Serial.printf("master ver : %s\n", __MASTER_VERSION);

  mpu_init();

  /* enanble key */
  enable_key(EN_KEY_GPIO_NUM);
  Serial.printf("DEGBG : get en_key = %d\n", digitalRead(EN_KEY_GPIO_NUM));

  /* connect AP */
  WiFi.begin(SSID, PASSWORD);
  Serial.println("connecting ...");

  Serial.printf("SSID : %s\n", SSID);
  Serial.printf("IP   : %s\n", PASSWORD);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }

  Serial.println("wifi connected!");

  /* UDP */
  Udp.begin(udp_port);
  Serial.println("UDP start!");

}

void loop() {

  if (WiFi.isConnected())
  {
    if (is_key_press(EN_KEY_GPIO_NUM) == true)
    {
      delay(100);
      int16_t pitch, roll;
      static int16_t standby = 0;
      mpu_get_ang(&pitch, &roll);
      Serial.printf("pitch , roll = %d\t%d\n", pitch, roll);
      moto_set_info(pitch, roll, &moto_info);
      Serial.printf("Left  : (dir, duty) = (%d\t%d)\n", moto_info.left_dir, moto_info.left_duty);
      Serial.printf("Right : (dir, duty) = (%d\t%d)\n", moto_info.right_dir, moto_info.right_duty);
      // udp_tx(HOST_IP, udp_port, &Udp, &moto_info);
      if (is_moto_standby(&moto_info))
      {
        if (standby == 0)
        {
          udp_tx(HOST_IP, udp_port, &Udp, &moto_info);
          standby = 1;
          Serial.println("send pkt standby...");
        }
        Serial.println("standby...");
      }
      else
      {
        udp_tx(HOST_IP, udp_port, &Udp, &moto_info);
        standby = 0;
        Serial.println("running...");
      }
    }
  }else{
    Serial.println("reconnecting ...");
    WiFi.reconnect();
    delay(1000);
  }
}
#endif