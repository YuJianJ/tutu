#include "tutu_common.h"

void init_car_info(CAR *car , LINK_TIME * time , CMD_MOTO * cmd , DEV_MOTO * moto , CAR_STA * sta)
{
    memset(time , 0, sizeof(LINK_TIME));
    memset(cmd , 0, sizeof(CMD_MOTO));
    memset(moto , 0, sizeof(DEV_MOTO));
    memset(sta , 0, sizeof(CAR_STA));
	/* init time */
	time->time_old = time->time_now = 0;
	time->timeout = LINK_TIMEOUT_DEF ;
	/* init cmd */
	cmd->x_in = cmd->y_in = INIT ;
	cmd->x_old = cmd->y_old = INIT ;
	cmd->l_len = cmd->r_len = INIT ;
	cmd->dir_l = cmd->dir_r = INIT ;
	cmd->dir_l_old = cmd->dir_r_old = INIT ;
	/* init dev */
	moto->dir_l = moto->dir_r = INIT ;
	moto->dir_l_old = moto->dir_r_old = INIT ;
	moto->duty_l = moto->duty_r = INIT ;
	moto->duty_l_old = moto->duty_r_old = INIT ;
	/* init sta */
	sta->dir = INIT ;
	sta->angle_base = INIT ;
	sta->angle_old = INIT ;
	sta->angle = INIT ;
	/* link all struct */
	car->time = time;
    car->cmd = cmd;
    car->moto = moto;
    car->sta = sta;
}
void set_car_info(CAR *car , int type)
{
	switch(type)
	{
		case SET_MOTO_LEFT_DIR:
			break;
		case SET_MOTO_LEFT_DUTY:
			break;
		default:
			break;
	}
}
void get_car_info(CAR *car , int type)
{
}

void reset_cmd_info(CAR *car , uint8_t x , uint8_t y)
{
	car->cmd->x_in = x ;
	car->cmd->y_in = y ;
	//double d = 0;
	int line_1 = x-y ;
	int line_2 = x+y-255 ;
	/* forward */
	if( (0 <= line_1) && ( 0 >= line_2) )	// y range [0,128]
	{
		car->cmd->dir_l = MOTO_FORWARD;
		car->cmd->dir_r = MOTO_FORWARD;
		//d = (x-y) * M_SQRT1_2;// M_SQRT1_2 = 1/sqrt(2)
		//d = (x-y) * 0.7;// M_SQRT1_2 = 1/sqrt(2) ≈ 0.707
		car->cmd->l_len = ( ((line_1)*70)/100 );
		car->cmd->r_len = ( ((~line_2)*70)/100 );
	}
	/* turn left */
	else if ( (0 > line_1) && ( 0 > line_2) )
	{
		car->cmd->dir_l = MOTO_BACKWARD;
		car->cmd->dir_r = MOTO_FORWARD;
		car->cmd->l_len = ( ((~line_1)*70)/100 );
		car->cmd->r_len = ( ((~line_2)*70)/100 );
	}
	/* turn right */
	else if ( (0 < line_1) && ( 0 < line_2) )
	{
		car->cmd->dir_l = MOTO_FORWARD;
		car->cmd->dir_r = MOTO_BACKWARD;
		car->cmd->l_len = ( ((line_1)*70)/100 );
		car->cmd->r_len = ( ((line_2)*70)/100 );
	}
	/* backward */
	else if (  (0 >= line_1) && ( 0 <= line_2) )
	{
		car->cmd->dir_l = MOTO_BACKWARD;
		car->cmd->dir_r = MOTO_BACKWARD;
		car->cmd->l_len = ( ((line_2)*70)/100 );
		car->cmd->r_len = ( ((~line_1)*70)/100 );
	}
}
void reset_moto_info(CAR *car)
{
	/* renew */
	car->moto->dir_l = car->cmd->dir_l ;
	car->moto->dir_r = car->cmd->dir_r ;
	//car->moto->duty_l = (car->cmd->l_len * 100) / MOTO_JOY_LENGTH_HALF ; // int
	//car->moto->duty_r = (car->cmd->r_len * 100) / MOTO_JOY_LENGTH_HALF ; // int
	//car->moto->duty_l = (car->cmd->l_len * 100) / MOTO_JOY_LENGTH_HALF ; // int
	//car->moto->duty_r = (car->cmd->r_len * 100) / MOTO_JOY_LENGTH_HALF ; // int
	car->moto->duty_l = car->cmd->l_len; // int
	car->moto->duty_r = car->cmd->r_len; // int
	car->moto->vel_l = 0; //reserved
	car->moto->vel_r = 0; //reserved
}
void reset_sta_info(CAR *car)
{
	car->sta->angle_old = 0 ;	// reserved
	car->sta->angle_base = 0 ;	// reserved
	car->sta->angle = 0 ;		// reserved
}
void sync_cmd_moto_info(CAR *car)
{
	car->cmd->x_old = car->cmd->x_in;
	car->cmd->y_old = car->cmd->y_in;
	car->cmd->dir_l_old = car->cmd->dir_l;
	car->cmd->dir_r_old = car->cmd->dir_r;
	car->moto->dir_l_old = car->moto->dir_l;
	car->moto->dir_r_old = car->moto->dir_r;
}
void init_moto_gpio(void)
{
	/* LOW : ENA $ ENB */
	pinMode(MOTO_L_EN_GPIO_NUM, OUTPUT);
	digitalWrite(MOTO_L_EN_GPIO_NUM, LOW);
	pinMode(MOTO_R_EN_GPIO_NUM, OUTPUT);
	digitalWrite(MOTO_R_EN_GPIO_NUM, LOW);
	/* LOW : in1 , in2 , in3 , in4 */
	pinMode(MOTO_L_IN1_GPIO_NUM, OUTPUT);
	pinMode(MOTO_L_IN2_GPIO_NUM, OUTPUT);
	pinMode(MOTO_R_IN3_GPIO_NUM, OUTPUT);
	pinMode(MOTO_R_IN4_GPIO_NUM, OUTPUT);
	digitalWrite(MOTO_L_IN1_GPIO_NUM, LOW);
	digitalWrite(MOTO_L_IN2_GPIO_NUM, LOW);
	digitalWrite(MOTO_R_IN3_GPIO_NUM, LOW);
	digitalWrite(MOTO_R_IN4_GPIO_NUM, LOW);
}
void init_moto_pwm(void)
{
	ledcSetup(MOTO_L_PWM_CHANNEL,MOTO_L_PWM_FREQ,MOTO_L_PWM_RESOLUTION);
	ledcSetup(MOTO_R_PWM_CHANNEL,MOTO_R_PWM_FREQ,MOTO_R_PWM_RESOLUTION);
	ledcAttachPin(MOTO_L_EN_GPIO_NUM,MOTO_L_PWM_CHANNEL);
	ledcAttachPin(MOTO_R_EN_GPIO_NUM,MOTO_R_PWM_CHANNEL);
}
void change_moto(CAR *car)
{
	if (car->moto->dir_l != car->moto->dir_l_old)
	{
		change_moto_by_dir(MOTO_LEFT, car->moto->dir_l);
	}
	if (car->moto->dir_r != car->moto->dir_r_old)
	{
		change_moto_by_dir(MOTO_RIGHT, car->moto->dir_r);
	}
	if (car->moto->duty_l != car->moto->duty_l_old)
	{
		change_moto_by_duty(MOTO_LEFT, car->moto->duty_l);
	}
	if (car->moto->duty_r != car->moto->duty_r_old)
	{
		change_moto_by_duty(MOTO_RIGHT, car->moto->duty_r);
	}
}
void change_moto_by_dir(int which , int dir)
{
	//int en = INIT ;// reserved 
	int in1 = INIT ;
	int in2 = INIT ;
	switch(which){
		case MOTO_LEFT:
			//en = MOTO_L_EN_GPIO_NUM ;
			in1 = MOTO_L_IN1_GPIO_NUM ;
			in2 = MOTO_L_IN2_GPIO_NUM ;
			break;
		case MOTO_RIGHT:
			//en = MOTO_R_EN_GPIO_NUM ;
			in1 = MOTO_R_IN3_GPIO_NUM ;
			in2 = MOTO_R_IN4_GPIO_NUM ;
			break;
		default:
			break;//do nothing 
	}
	switch(dir){
		default:
		case MOTO_STAY:
		case MOTO_FREE:
			break;
		case MOTO_STOP://0,0 / 1,1
			//digitalWrite(en, LOW);
			digitalWrite(in2, digitalRead(in1));
			break;
		case MOTO_FORWARD://1,0
			if(digitalRead(in1) == LOW )
				digitalWrite(in1, HIGH);
			if(digitalRead(in2) == HIGH )
				digitalWrite(in2, LOW);
			break;
		case MOTO_BACKWARD://0,1
			if(digitalRead(in1) == HIGH )
				digitalWrite(in1, LOW);
			if(digitalRead(in2) == LOW )
				digitalWrite(in2, HIGH);
			break;
	}
}
void change_moto_by_duty(int which , int duty)
{
	/* set suty range : [min , max] */
	double duty_fix = duty;
	if(duty != 0){
		duty_fix = duty + 127; // reserved Min speed/duty
	}
	/* use PWM as default? */
	/* Tips : 12v * 0.66 = 8v => 12v * 170/256 = 8v => duty >= 170 */
	if(which == MOTO_LEFT)
		ledcWrite(MOTO_L_PWM_CHANNEL, duty_fix); 
	else
		ledcWrite(MOTO_R_PWM_CHANNEL, duty_fix);
}

/* New Task for cmd inpur timeout */
void stop_moto_if_dev_offline(CAR *car )
{
	if (is_time_to_checklink(car) == TUTU_OK)
	{
		if (is_dev_online(0) == TUTU_NG)
		{
			//car->moto->dir_l = MOTO_STOP;
			//car->moto->dir_r = MOTO_STOP;
			//set_car_info(car , SET_MOTO_LEFT_DIR);
			//set_car_info(car , SET_MOTO_RIGHT_DIR);
		}
	}
}
void reset_link_time(CAR *car , unsigned long time)
{
	car->time->time_old = car->time->time_now ;
	car->time->time_now = time;
}
int is_time_to_checklink(CAR *car)
{
	if(car->time->time_now - car->time->time_old >= car->time->timeout)
		return TUTU_OK;
	else
		return TUTU_NG;
}
int is_dev_online(unsigned long timeout)
{
    /* FIXME */
	//return Blinker.connected();
    return TUTU_OK;
}

