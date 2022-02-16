#ifndef __TUTU_API_H__
#define __TUTU_API_H__

#include "tutu_types.h"
#include <stdint.h>
/********************** common *********************/

/********************** moto *********************/
/* callback funcs for moto */
//void dataRead(const String & data);
void joy_moto_callback(uint8_t x , uint8_t y);
void ran_speed_max_callback(int32_t val);

/* config moto funcs */
void init_car_info(CAR *car , LINK_TIME *time , CMD_MOTO *cmd , DEV_MOTO *moto , CAR_STA *sta);
void set_car_info(CAR *car , int type);
void get_car_info(CAR *car , int type);
void reset_cmd_info(CAR *car , uint8_t x , uint8_t y);
void reset_moto_info(CAR *car);
void reset_sta_info(CAR *car);
void sync_cmd_moto_info(CAR *car);
/* dri moto funcs */
void init_moto_gpio(void);
void init_moto_pwm(void);
void change_moto(CAR *car);
void change_moto_by_dir(int which_moto , int dir);
void change_moto_by_duty(int which_moto , int duty);

/* New Task for cmd inpur timeout */
void stop_moto_if_dev_offline(CAR *car );
void reset_link_time(CAR *car , unsigned long time);
int is_time_to_checklink(CAR *car);
int is_dev_online(unsigned long timeout);

/********************** cam *********************/

#endif
