#define BLINKER_WIFI 
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
char auth[] = "eb0b6e62edeb";
#if 0//iphone
char ssid[] = "j iPhone";
char pswd[] = "33336666hot";
#else// AP
//char ssid[] = "lshfkxjd";
//char pswd[] = "88889999900..";
char ssid[] = "AX3000";
char pswd[] = "88889999..";
#endif

/************************** define para & funcs **********************/
/* define wights : moto */
BlinkerJoystick joy_moto("joy_moto");               // joy_moto
BlinkerSlider ran_speed_max("ran_speed_max");       // ran_speed_max
/* define wights : cam */
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
/************************* funcs : callback for moto ***********************/



/************************* funcs : common API for moto ***********************/

/************************* funcs : common API for cam ***********************/

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

	/* wifi link request */
	Blinker.begin(auth, ssid, pswd);
	Blinker.attachData(dataRead);

	/* init moto gpio & pwm */
	init_moto_gpio();
	init_moto_pwm();
	/* init struct CAR info */
	init_car_info(&car , &link_time , &cmd , &moto, &tutu_sta);

	/* bind func with weights : moto */
	joy_moto.attach(joy_moto_callback);
	ran_speed_max.attach(ran_speed_max_callback);

	/* bind func with weights : cam */

	
#ifdef LINK_CHECK
	/* SMP for TxRx */
	xTaskCreatePinnedToCore(stop_moto_if_dev_offline,"stop_moto_if_dev_offline",8192,NULL,1,NULL,1);
#endif

	BLINKER_TAST_INIT();
}

/*************************** loop : main *********************/
void loop() {
    //Blinker.run();
}