#ifndef __TUTU_TYPES_H__
#define __TUTU_TYPES_H__

#define TUTU_NG -1
#define TUTU_OK 1
#define INIT 999

typedef struct time_connect_t
{
	unsigned long timeout;
	unsigned long time_old;
	unsigned long time_now;
}LINK_TIME;

enum cmd_status_info 
{
	CMD_GET_ONLINE=1,
	CMD_GET_OFFLINE
};
typedef struct cmd_moto_info_t
{
	/* get point(x,y)*/
	int x_in;
	int y_in; 
	/* set */
	/*length of l & r */
	int x_old;
	int y_old; 
	int l_len;
	int r_len;
	int dir_l;
	int dir_r;
	int dir_l_old;
	int dir_r_old;
}CMD_MOTO;

#define MOTO_JOY_LENGTH_HALF 128
enum moto_types {MOTO_LEFT=1 , MOTO_RIGHT};
enum moto_status {MOTO_FREE=1,MOTO_STOP,MOTO_FORWARD,MOTO_BACKWARD,MOTO_BUSY,MOTO_STAY};
typedef struct dev_moto_info_t
{
	int dir_l;//e.g:MOTO_BUSY
	int dir_r;
	int dir_l_old;
	int dir_r_old;
	/* set */
	int duty_l;
	int duty_r;
	int duty_l_old;
	int duty_r_old;
	/* get */
	double vel_l;
	double vel_r;
}DEV_MOTO;

enum car_status {CAR_FREE=1,CAR_STOP,CAR_FORWARD,CAR_BACKWARD,CAR_BUSY};
typedef struct car_status_t
{
	int dir;
	double angle_base;	// ori
	double angle_old;	// lsat
	double angle;		// now
	//int moto_speed;
}CAR_STA;

typedef struct car_info_all_t
{
	LINK_TIME *time;
	CMD_MOTO *cmd;
	DEV_MOTO *moto;
	CAR_STA *sta;
}CAR; 

enum all_cmd_define_here
{
	GET_SART=1,
	/* CMD_INFO */
	GET_CMD_X_LEN,
	GET_CMD_Y_LEN,
	/* DEV_INFO */
	GET_MOTO_LEFT_DIR,
	GET_MOTO_LEFT_DUTY,
	/* CAR_STA */
	GET_CAR_STA,
	GET_CAR_STA_DIR,
	GET_DONE,

	SET_START,
	/* CMD_INFO */
	//SET_CMD_X_IN,
	//SET_CMD_Y_IN,
	SET_CMD_X_LEN,
	SET_CMD_Y_LEN,
	SET_CMD_X_OLD,
	SET_CMD_Y_OLD,
	SET_CMD_DIR,
	SET_CMD_DIR_OLD,
	/* DEV_INFO */
	SET_MOTO_LEFT_DIR,
	SET_MOTO_LEFT_DUTY,
	SET_MOTO_RIGHT_DIR,
	SET_MOTO_RIGHT_DUTY,
	/* CAR_STA */
	SET_CAR_STA,
	SET_CAR_STA_DIR,
	SET_DOEN,

	CHECK_START,
	/* CMD_INFO */
	/* DEV_INFO */
	/* CAR_STA */
	CHECK_CMD_MOTO,
	CHECK_DONE
};

#endif
