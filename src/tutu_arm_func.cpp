#include "tutu_common.h"

void init_arm_pwm(void)
{
	//pinMode(ARM_B_GPIO_NUM, OUTPUT);
    ledcSetup(ARM_H_PWM_CHANNEL,ARM_PWM_FREQ,ARM_PWM_RESOLUTION);
    //ledcSetup(ARM_2_PWM_CHANNEL,ARM_PWM_FREQ,ARM_PWM_RESOLUTION);
    //ledcSetup(ARM_1_PWM_CHANNEL,ARM_PWM_FREQ,ARM_PWM_RESOLUTION);
    //ledcSetup(ARM_B_PWM_CHANNEL,ARM_PWM_FREQ,ARM_PWM_RESOLUTION);
	ledcAttachPin(ARM_H_GPIO_NUM,ARM_H_PWM_CHANNEL);
	//ledcAttachPin(ARM_2_GPIO_NUM,ARM_2_PWM_CHANNEL);
	//ledcAttachPin(ARM_1_GPIO_NUM,ARM_1_PWM_CHANNEL);
	//ledcAttachPin(ARM_B_GPIO_NUM,ARM_B_PWM_CHANNEL);
}

void arm_pwm_test(int angle)
{
    ledcWrite(ARM_H_PWM_CHANNEL, angle);
}
