#ifndef __MOTO_INFO_H__
#define __MOTO_INFO_H__

/* keep ang range [ANG_MIN,ANG_OPTIMIZE_MIN],[ANG_OPTIMIZE_MAX,ANG_MAX] */
#define ANG_MAX         (50)
#define ANG_DEAD_MAX    (10)
#define ANG_DEAD_MIN    (-10)
#define ANG_MIN         (-50)

/* driver moto */
typedef struct cmd_moto_info_t{
    int16_t left_dir;
    int16_t left_duty;
    int16_t right_dir;
    int16_t right_duty;
}MOTO_INFO;

#define FORWARD     0x01
#define BACKWARD    0x02
#define MOTO_LOW     (0)
#define MOTO_HIGH    (1)

#define MOTO_R_EN_GPIO_NUM  16
#define MOTO_R_IN1_GPIO_NUM 17
#define MOTO_R_IN2_GPIO_NUM 5
#define MOTO_L_IN3_GPIO_NUM 18
#define MOTO_L_IN4_GPIO_NUM 19 //4,5,18,19,21,22,23 //13,12,14,27,26,25,33,32,35,34
#define MOTO_L_EN_GPIO_NUM	21

#define MOTO_L_PWM_CHANNEL		7//5//4//3 //2//0
#define MOTO_L_PWM_FREQ			4500
#define MOTO_L_PWM_RESOLUTION	8 // 1024
#define MOTO_R_PWM_CHANNEL		6
#define MOTO_R_PWM_FREQ			4500
#define MOTO_R_PWM_RESOLUTION	8 // 1024

void moto_set_info(int16_t pitch, int16_t roll, MOTO_INFO *moto_info);
uint16_t is_moto_standby(MOTO_INFO *moto);

void init_moto_gpio(void);
void init_moto_pwm(void);
void moto_set_left(int dir, int duty);
void moto_set_right(int dir, int duty);

#endif