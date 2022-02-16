#ifndef __TUTU_COMMON_H__
#define __TUTU_COMMON_H__

//#include "tutu_types.h"
#include "tutu_api.h"
#include <string.h>
#include <esp32-hal-gpio.h>
//#include <math.h>

//#define __SOFT_VER__ "v0.1.1-rc1"
//#define __SOFT_VER__ "v0.1.1-rc2"		// 2021.12.27 : Changed the steering logic.
//#define __SOFT_VER__ "v0.1.2"		// 2021.12.29 : Modify the control mode.Fix errors in cmd .
#define __SOFT_VER__ "v0.1.3"		// 2021.12.29 : update duty.
// callback:reset_moto_info_by_vel
// reset_moto_info_by_vel:read vel from MPU605
// run_moto:check flag continue/FIX 
// loop from joy_callback

#define MOTO_L_EN_GPIO_NUM	18
#define MOTO_L_IN1_GPIO_NUM 14
#define MOTO_L_IN2_GPIO_NUM 15
#define MOTO_R_EN_GPIO_NUM 19
#define MOTO_R_IN3_GPIO_NUM 16
#define MOTO_R_IN4_GPIO_NUM 17

#define MOTO_L_PWM_CHANNEL		0
#define MOTO_L_PWM_FREQ			4500
#define MOTO_L_PWM_RESOLUTION	8
#define MOTO_R_PWM_CHANNEL		1
#define MOTO_R_PWM_FREQ			4500
#define MOTO_R_PWM_RESOLUTION	8

/* 1000 ms */
#define LINK_TIMEOUT_DEF	1000
#define LINK_SLEEP_TIME_DEF	1000

#endif
