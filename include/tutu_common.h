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
//#define __SOFT_VER__ "v0.1.3"		// 2021.12.29 : update duty.
//#define __SOFT_VER__ "v1.0.0"		// 2022.06.19 : A BLE conn
//#define __SOFT_VER__ "v1.1.0"		// 2022.06.25 : M MOTO PWN chan; M MOTO GPIO num
#define __SOFT_VER__ "v2.1.0"		// 2022.07.02 : M MOTO GPIO num; A conn BLE; FIX Blinker crash; A func BLE_timeout

#if 0 //ori
#define MOTO_L_EN_GPIO_NUM	18
#define MOTO_L_IN4_GPIO_NUM 14
#define MOTO_L_IN3_GPIO_NUM 15
#define MOTO_R_EN_GPIO_NUM 19
#define MOTO_R_IN2_GPIO_NUM 16
#define MOTO_R_IN1_GPIO_NUM 17
#else
#define MOTO_R_EN_GPIO_NUM  16
#define MOTO_R_IN1_GPIO_NUM 17
#define MOTO_R_IN2_GPIO_NUM 5
#define MOTO_L_IN3_GPIO_NUM 18
#define MOTO_L_IN4_GPIO_NUM 19 //4,5,18,19,21,22,23 //13,12,14,27,26,25,33,32,35,34
#define MOTO_L_EN_GPIO_NUM	21
#endif
#define MOTO_L_PWM_CHANNEL		7//5//4//3 //2//0
#define MOTO_L_PWM_FREQ			4500
#define MOTO_L_PWM_RESOLUTION	8
#define MOTO_R_PWM_CHANNEL		6
#define MOTO_R_PWM_FREQ			4500
#define MOTO_R_PWM_RESOLUTION	8

#define ARM_H_GPIO_NUM	26//26//25//34x//35x//32//33
#define ARM_2_GPIO_NUM	25
#define ARM_1_GPIO_NUM	33
#define ARM_B_GPIO_NUM	32
#define ARM_H_PWM_CHANNEL		2
#define ARM_2_PWM_CHANNEL		0
#define ARM_1_PWM_CHANNEL		0
#define ARM_B_PWM_CHANNEL		0
#define ARM_PWM_FREQ			50
#define ARM_PWM_RESOLUTION	    10 //1024

/* 1000 ms */
#define LINK_TIMEOUT_DEF	1000
#define LINK_SLEEP_TIME_DEF	1000

#endif
