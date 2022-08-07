#ifndef __MSATER_MPU6050_H__
#define __MSATER_MPU6050_H__

/* i2c slave addr */
#define I2C_SLAVE_ADDR 0x68

/* i2c gpio */
#define I2C_SDA_GPIO (21)  
#define I2C_SCL_GPIO (22)

/* registers */
#define REG_PM      0x6b
#define REG_PM_2    0x6c
#define REG_INT     0x38
#define REG_ACCEL   0x3b /* 0x3b 0x3c : X_H X_L ; 0x3d 0x3e : Y_H Y_L ; 0x3f 0x40 : Z_H Z_L */

/* ACCEL type */
#define ACCEL_XOUT 0x01
#define ACCEL_YOUT 0x02
#define ACCEL_ZOUT 0x03

/* gpio for master */
#define EN_KEY_GPIO_NUM  (26)

void mpu_init(void);
void mpu_get_ang(int16_t *pitch , int16_t *roll);
void enable_key(int gpio);
bool is_key_press(int gpio);
void test(void);


#endif
