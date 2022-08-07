#include <Arduino.h>
#include "common.h"
#include <Wire.h>

void mpu_init(void)
{
#if 1
    /* init mpu6050 i2c */
    Wire.begin(I2C_SDA_GPIO, I2C_SCL_GPIO); // sda , scl
    Wire.beginTransmission(I2C_SLAVE_ADDR);
    /* reset dev */
    Wire.write(REG_PM);
    //Wire.write(80);     // bit 7 reset if set 1
    Wire.write(0);     // bit 7 reset if set 1
    //delay(100);         // delay 100sms for reset
    //Wire.write(REG_PM);
    //Wire.write(0x01);   // set clk : 0x01
    /* walk up always */
    //Wire.write(REG_PM_2);
    //Wire.write(0x00);
    /* disable global intr */
    //Wire.write(REG_INT);
    //Wire.write(0x00);
    byte i2c_error = Wire.endTransmission();
    if (i2c_error == 0)
    {
        Serial.printf("i2c device found at %#x\n");
    }
#endif
}

void mpu_get_ang(int16_t *pitch , int16_t *roll)
{
    //int16_t x, y, z;
    int16_t x, y;
    int16_t val;
    Wire.beginTransmission(I2C_SLAVE_ADDR);
    Wire.write(REG_ACCEL);
    Wire.endTransmission(false);
    Wire.requestFrom(I2C_SLAVE_ADDR, 14, true);

    x = Wire.read() << 8 | Wire.read();
    y = Wire.read() << 8 | Wire.read();
    //z = Wire.read() << 8 | Wire.read();

    val = y >> 8;   // PITCH
    if (val > ANG_MAX)
        val = ANG_MAX;
    else if (val < ANG_MIN)
        val = ANG_MIN;
    else if (val > ANG_DEAD_MIN && val < ANG_DEAD_MAX)
        val = 0;
    else
    {
        /* do nothing */
    }
    *pitch = val;

    val = x >> 8;   // ROLL
    if (val > ANG_MAX)
        val = ANG_MAX;
    else if (val < ANG_MIN)
        val = ANG_MIN;
    else if (val > ANG_DEAD_MIN && val < ANG_DEAD_MAX)
        val = 0;
    else
    {
        /* do nothing */
    }
    *roll = val;

}

void test(void){
#if 0
    int16_t x, y, z;
    Wire.beginTransmission(I2C_SLAVE_ADDR);
    Wire.write(REG_ACCEL);
    Wire.endTransmission(false);
    Wire.requestFrom(I2C_SLAVE_ADDR, 14, true);

    x = Wire.read() << 8 | Wire.read();
    y = Wire.read() << 8 | Wire.read();
    z = Wire.read() << 8 | Wire.read();

    Serial.printf("x,y,z = %d\t%d\t%d\n", x/100, y/100, z/100);
    Serial.printf("-x,y,z = %d\t%d\t%d\n", x>>8, y>>8, z>>8);

    delay(500);
#endif
}

void enable_key(int gpio)
{
    pinMode(gpio, INPUT);
}
bool is_key_press(int gpio)
{
    return digitalRead(gpio) == MOTO_HIGH ? false : true;
}