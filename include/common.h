#ifndef __COMMON_H__
#define __COMMON_H__

#include "master_version.h"
#include "master_mpu6050.h"
#include "moto_info.h"
#include "connect_func.h"

#define PITCH  ACCEL_YOUT // F / B
#define ROLL   ACCEL_XOUT // L / R

#if 1
#define TUTU_STA  // for master
#else
#define TUTU_AP   // for car
#endif

#endif
