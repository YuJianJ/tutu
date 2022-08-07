#include <Arduino.h>

#include "common.h"

void moto_set_info(int16_t pitch, int16_t roll, MOTO_INFO *moto_info)
{
#if 1
    do{
        /* 1. standby or turn dirt */
        if (pitch == 0) 
        {
            if (roll > 0)
            {
                /* turn right */
                moto_info->left_dir = FORWARD;
                moto_info->right_dir = BACKWARD;
                //moto_info->left_duty = roll * 2; // 50 * 2 = 100
                //moto_info->right_duty = roll * 2;
                moto_info->left_duty = roll; // half of MAX
                moto_info->right_duty = roll;
            }
            else if (roll < 0)
            {
                /* turn left */
                moto_info->left_dir = BACKWARD;
                moto_info->right_dir = FORWARD;
                //moto_info->left_duty = abs(roll * 2); // 50 * 2 = 100
                //moto_info->right_duty = abs(roll * 2);
                moto_info->left_duty = abs(roll); // half of MAX
                moto_info->right_duty = abs(roll);

            }
            else
            {
                /* stop */
                break;
            }
            return ;
        }
        else if (pitch >= ANG_MIN && pitch < 0) // forward : (ANG_MIN,0)
        {
            /* forward */
            moto_info->left_dir = FORWARD;
            moto_info->right_dir = FORWARD;
            pitch = -pitch;
            if (roll == 0)
            {
                moto_info->left_duty = pitch * 2;// ANG_MAX = 50
                moto_info->right_duty = moto_info->left_duty;
            }
            else if (roll < 0)
            { // turn left
                roll = -roll;
                moto_info->right_duty = pitch * 2;
                moto_info->left_duty = ((pitch * 2) * (((ANG_MAX - roll) * 100 ) / ANG_MAX) ) / 100 ;
            }
            else
            {
                moto_info->left_duty = pitch * 2;
                moto_info->right_duty = ((pitch * 2) * (((ANG_MAX - roll) * 100 ) / ANG_MAX) ) / 100 ;
            }
            return ;
        }
        else if (pitch > 0 && pitch <= ANG_MAX) // backward : (0,ANG_MAX)
        {
            moto_info->left_dir = BACKWARD;
            moto_info->right_dir = BACKWARD;
            if (roll == 0){
                moto_info->left_duty = pitch * 2;// ANG_MAX = 50
                moto_info->right_duty = moto_info->left_duty;
            }else if ( roll < 0){
                roll = -roll;
                moto_info->right_duty = pitch * 2;
                moto_info->left_duty = ((pitch * 2) * (((ANG_MAX - roll) * 100 ) / ANG_MAX) ) / 100 ;
            }else {
                moto_info->left_duty = pitch * 2;
                moto_info->right_duty = ((pitch * 2) * (((ANG_MAX - roll) * 100 ) / ANG_MAX) ) / 100 ;
            }
            return ;
        }
    } while (0);
    /* defalt */
    moto_info->left_dir  = FORWARD;
    moto_info->right_dir = FORWARD;
    moto_info->left_duty  = 0;
    moto_info->right_duty = 0;
#endif
}

uint16_t is_moto_standby(MOTO_INFO *moto)
{
    if ((moto->left_duty == 0) && (moto->right_duty == 0))
        return 1;
    else
        return 0;
}

void init_moto_gpio(void)
{
    	/* MOTO_LOW : ENA $ ENB */
	pinMode(MOTO_L_EN_GPIO_NUM, OUTPUT);
	digitalWrite(MOTO_L_EN_GPIO_NUM, MOTO_LOW);
	pinMode(MOTO_R_EN_GPIO_NUM, OUTPUT);
	digitalWrite(MOTO_R_EN_GPIO_NUM, MOTO_LOW);
	/* MOTO_LOW : in1 , in2 , in3 , in4 */
	pinMode(MOTO_L_IN4_GPIO_NUM, OUTPUT);
	pinMode(MOTO_L_IN3_GPIO_NUM, OUTPUT);
	pinMode(MOTO_R_IN2_GPIO_NUM, OUTPUT);
	pinMode(MOTO_R_IN1_GPIO_NUM, OUTPUT);
	digitalWrite(MOTO_L_IN4_GPIO_NUM, MOTO_LOW);
	digitalWrite(MOTO_L_IN3_GPIO_NUM, MOTO_LOW);
	digitalWrite(MOTO_R_IN2_GPIO_NUM, MOTO_LOW);
	digitalWrite(MOTO_R_IN1_GPIO_NUM, MOTO_LOW);

}
void init_moto_pwm(void)
{
	ledcSetup(MOTO_L_PWM_CHANNEL,MOTO_L_PWM_FREQ,MOTO_L_PWM_RESOLUTION);
	ledcSetup(MOTO_R_PWM_CHANNEL,MOTO_R_PWM_FREQ,MOTO_R_PWM_RESOLUTION);
	ledcAttachPin(MOTO_L_EN_GPIO_NUM,MOTO_L_PWM_CHANNEL);
	ledcAttachPin(MOTO_R_EN_GPIO_NUM,MOTO_R_PWM_CHANNEL);
}

void moto_set_left(int dir, int duty)
{
    int16_t in3 = -1;
    int16_t in4 = -1;
    int16_t en = -1;
    en = MOTO_L_EN_GPIO_NUM;
    if (dir == FORWARD){
        in3 = MOTO_L_IN3_GPIO_NUM; // LOW
        in4 = MOTO_L_IN4_GPIO_NUM; // HIGH
    }else if(dir == BACKWARD){
        in4 = MOTO_L_IN3_GPIO_NUM; // HIGH
        in3 = MOTO_L_IN4_GPIO_NUM; // LOW
    }else{
        //Serial.println("input error, line:%d", __LINE__);
        printf("input error , line:%d\n", __LINE__);
        return ;
    }

    if (digitalRead(in3) == MOTO_HIGH)
        digitalWrite(in3, MOTO_LOW);
    if (digitalRead(in4) == MOTO_LOW)
        digitalWrite(in4, MOTO_HIGH);
    /* FIXME */
    ledcWrite(MOTO_L_PWM_CHANNEL, duty != 0 ? duty + 156 : 0);
    printf("DEBUG : set left : dir=%d duty=%d\n", dir, duty != 0 ? duty + 156 : 0);
}
void moto_set_right(int dir, int duty)
{
    int16_t en = -1;
    int16_t in1 = -1;
    int16_t in2 = -1;
    en = MOTO_R_EN_GPIO_NUM;
    if (dir == FORWARD)
    {
        in1 = MOTO_R_IN1_GPIO_NUM;
        in2 = MOTO_R_IN2_GPIO_NUM;
    }
    else if (dir == BACKWARD)
    {
        in1 = MOTO_R_IN2_GPIO_NUM;
        in2 = MOTO_R_IN1_GPIO_NUM;
    }
    else
    {
        //Serial.println("input error, line:%d", __LINE__);
        printf("input error , line:%d\n", __LINE__);
        return;
    }

    if (digitalRead(in1) == MOTO_HIGH)
        digitalWrite(in1, MOTO_LOW);
    if (digitalRead(in2) == MOTO_LOW)
        digitalWrite(in2, MOTO_HIGH);
    /* FIXME */
    ledcWrite(MOTO_R_PWM_CHANNEL, duty != 0 ? duty + 156 : 0);
    printf("DEBUG : set right : dir=%d duty=%d\n", dir, duty != 0 ? duty + 156 : 0);
}
