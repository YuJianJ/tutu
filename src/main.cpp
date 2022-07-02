//#define WIFI_CONN
//#define APCFG_CONN
#define BLE_CONN

#if defined(BLE_CONN)
	#define BLINKER_BLE
	#define CONFIG_FREERTOS_UNICORE 1
#elif defined(WIFI_CONN)
	#define BLINKER_WIFI
#elif defined(APCFG_CONN)
	#define BLINKER_PRO_ESP
#endif

#define BLINKER_ESP_TASK

#include "tutu_common.h"
#include <Blinker.h> 


static LINK_TIME link_time;
static CMD_MOTO cmd;
static DEV_MOTO moto;
static CAR_STA tutu_sta;
static CAR car;

static double moto_duty_max = 100.00;

/************************** wifi config **********************/
/* wifi configuration */

#if defined(WIFI_CONN)
char auth[] = "eb0b6e62edeb";
#if 1//iphone
char ssid[] = "j iPhone";
char pswd[] = "33336666hot";
#else// AP
char ssid[] = "lshfkxjd";
char pswd[] = "88889999900..";
#endif
#endif

/************************** define para & funcs **********************/
/* define wights : moto */
BlinkerJoystick joy_moto("joy_moto");               // joy_moto
BlinkerSlider ran_speed_max("ran_speed_max");       // ran_speed_max
/* define wights : cam */
/* define wights : arm */
BlinkerJoystick joy_arm_b_h("joy_arm_b_h");               // joy_moto

void dataRead(const String & data);

/************************* funcs : callback for moto ***********************/
// callback for the wights with NO attach funcs */
void dataRead(const String & data)
{
    BLINKER_LOG("Blinker readString: ", data);
}
// callback func of joy_moto 
void joy_moto_callback(uint8_t x , uint8_t y)
{
    BLINKER_LOG("joy get x=", x);
	BLINKER_LOG("joy get y=", y);
	reset_link_time(&car, millis()); // reset input parm
	reset_cmd_info(&car , x ,y); // reset input parm
	reset_moto_info(&car);          // reset moto parm
	change_moto(&car);
	sync_cmd_moto_info(&car);
	reset_sta_info(&car);
}
// callback func of ran_speed
void ran_speed_max_callback(int32_t val)
{
    BLINKER_LOG("ran get max_speed val=", val);
}
/************************* funcs : callback for cam ***********************/

/************************* funcs : callback for arm ***********************/
void joy_arm_b_h_callback(uint8_t x , uint8_t y)
{
    BLINKER_LOG("joy get x=", x);
	BLINKER_LOG("joy get y=", y);
	//reset_link_time(&car, millis()); // reset input parm
	//reset_cmd_info(&car , x ,y); // reset input parm
	//reset_moto_info(&car);          // reset moto parm
	//change_moto(&car);
	//sync_cmd_moto_info(&car);
	//reset_sta_info(&car);
}

/************************* funcs : common API for moto ***********************/

/************************* funcs : common API for cam ***********************/

/************************* funcs : common API for arm ***********************/

/*************************** init weights and attach funcs ***************************/
void setup()
{

    /* init serial */
	Serial.begin(115200);
	BLINKER_DEBUG.stream(Serial);
	BLINKER_DEBUG.debugAll();

	/* init gpio builin LED */
	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, HIGH);

#if defined(BLE_CONN)
	Blinker.begin();
#elif defined(WIFI_CONN)
	/* wifi link request */
	Blinker.begin(auth, ssid, pswd);
#endif

	/* init moto gpio & pwm */
	init_moto_gpio();
	init_moto_pwm();
	/* init struct CAR info */
	init_car_info(&car , &link_time , &cmd , &moto, &tutu_sta);

	/* init arm gpio & pwm */
	//init_arm_pwm();

	/* bind func with weights : moto */
	Blinker.attachData(dataRead);
	joy_moto.attach(joy_moto_callback);
	ran_speed_max.attach(ran_speed_max_callback);

	/* bind func with weights : cam */

	/* bind func with weights : arm */
	joy_arm_b_h.attach(joy_arm_b_h_callback);

	init_arm_pwm();


#ifdef LINK_CHECK
	/* SMP for TxRx */
	xTaskCreatePinnedToCore(stop_moto_if_dev_offline,"stop_moto_if_dev_offline",8192,NULL,1,NULL,1);
#endif
	BLINKER_TAST_INIT();
}

/*************************** loop : main *********************/
void loop()
{
	if (millis() - car.time->time_now > car.time->timeout)
	{
		change_moto_by_duty(MOTO_LEFT, 0);
		change_moto_by_duty(MOTO_RIGHT, 0);
		delay(10);
	}
	else
	{
		delay(100);
	}
#if 0
		delay(500);
		Serial.printf("GPIO = %d\n", ARM_H_GPIO_NUM);

		int i = 26;// -90
		arm_pwm_test(i);//0.5ms/20ms * 2**10 = 1/40 * 1024 = 25.6 ≈ 26
		Serial.printf("i = %d\n", i);
		delay(2000);

		i = 52;// -45
		arm_pwm_test(i);//1ms/20ms * 2**10 = 1/20 * 1024 = 51.2 ≈ 52
		Serial.printf("i = %d\n", i);
		delay(2000);

		i = 77;// -0
		arm_pwm_test(i);//1.5ms/20ms * 2**10 = 3/40 * 1024 = 76.8 ≈ 77
		Serial.printf("i = %d\n", i);
		delay(2000);

		i = 103;// 45
		arm_pwm_test(i);//2ms/20ms * 2**10 = 1/10 * 1024 = 102.4 ≈ 103
		Serial.printf("i = %d\n", i);
		delay(2000);

		i = 128;// 90
		arm_pwm_test(i);//2.5ms/20ms * 2**10 = 5/40 * 1024 = 128
		Serial.printf("i = %d\n", i);
		delay(2000);

#endif
}