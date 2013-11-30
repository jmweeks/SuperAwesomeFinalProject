#include "arm_math.h"

#include "stm32f4xx.h"
#include "cmsis_os.h"

#include "project_init.h"
#include "project_servo.h"
#include "project_magnet.h"
#include "project_robot.h"
#include "CC2500.h"

#include <stdlib.h>


/*!
 @brief Thread to perform menial tasks such as switching LEDs
 @param argument Unused
 */
void thread(void const *argument);

static struct Servo boomServo, crowdServo, swingServo;
static struct Robot robot;
static struct Magnet magnet;

//! Thread structure for above thread
osThreadDef(thread, osPriorityNormal, 1, 0);

uint8_t state, buffer_space;
uint8_t data[4];

/*!
 @brief Program entry point
 */
int main (void) {
	osThreadId tid_thread;
	CC2500_Init();
	init_TIM4(1 / SERVO_DUTY_CYCLE_STEP, SERVO_FREQUENCY);
	init_LEDS_PWM();
	init_servo(&boomServo, 1, BOOM_ANGLE_MAX, BOOM_ANGLE_MIN);
	init_servo(&crowdServo, 2, CROWD_ANGLE_MAX, CROWD_ANGLE_MIN);
	init_servo(&swingServo, 3, SWING_ANGLE_MAX, SWING_ANGLE_MIN);
	init_robot(&robot, &boomServo, &crowdServo, &swingServo);
	init_magnet(&magnet, RCC_AHB1Periph_GPIOD, GPIOD, GPIO_Pin_15);
	
	CC2500_config_transmitter();
	
	goToRX(&state, &buffer_space);
	
	tid_thread = osThreadCreate(osThread(thread), NULL);
	
	osDelay(osWaitForever);
}

void thread (void const *argument) {
	parkRobot(&robot);
	osDelay(1000);

//	uint32_t prevY1=0, prevAngle1=0, nextY1=rand()%7, nextAngle1=rand()%14;
//	uint32_t prevY2=0, prevAngle2=0, nextY2=rand()%7, nextAngle2=rand()%14;
	while(1) {
		wireless_RX(data, 4, &state, &buffer_space);
		moveRobot(&robot, data[0], data[1], data[2]);
		if (data[3]) {
			turnMagnetOn(&magnet);
		} else {
			turnMagnetOff(&magnet);
		}
		
//		moveRobot(&robot, prevY1, 0, prevAngle1);
//		turnMagnetOn(&magnet);
//		osDelay(500);
//		moveRobot(&robot, nextY1, 0, nextAngle1);
//		turnMagnetOff(&magnet);
//		osDelay(500);
//		
//		moveRobot(&robot, prevY2, 0, prevAngle2);
//		turnMagnetOn(&magnet);
//		osDelay(500);
//		moveRobot(&robot, nextY2, 0, nextAngle2);
//		turnMagnetOff(&magnet);
//		osDelay(500);
//		
//		prevY1=nextY1;
//		prevAngle1=nextAngle1;
//		prevY2=nextY2;
//		prevAngle2=nextAngle2;
//		
//		nextY1=rand()%7;
//		nextAngle1=rand()%14;
//		nextY2=rand()%7;
//		nextAngle2=rand()%14;
		osDelay(100);
	}
}
