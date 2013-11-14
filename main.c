#include "arm_math.h"

#include "stm32f4xx.h"
#include "cmsis_os.h"

#include "project_init.h"
#include "project_pwm.h"
#include "project_servo.h"
#include "project_filter.h"
#include "project_accelerometer.h"

/*!
 @brief Thread to perform menial tasks such as switching LEDs
 @param argument Unused
 */
void thread(void const * argument);

static struct Servo servo;
static struct Orientation orientation;

//! Thread structure for above thread
osThreadDef(thread, osPriorityNormal, 1, 0);

/*!
 @brief Program entry point
 */
int main (void) {
	
	init_TIM4(1 / SERVO_DUTY_CYCLE_STEP, SERVO_FREQUENCY);
	//init_TIM4(ACCELEROMETER_PWM_STEPS, ACCELEROMETER_PWM_FREQUENCY);
	init_LEDS_PWM();
	init_servo(&servo, 3);
	init_orientation(&orientation);
	init_accelerometer();
	
	osThreadId tid_thread;

	// Start thread
	tid_thread = osThreadCreate(osThread(thread), NULL);

	// The below doesn't really need to be in a loop
	while(1){
		osDelay(osWaitForever);
	}
}

void thread (void const *argument) {
	/*uint32_t position;
	uint32_t direction;
	while(1) {
		if (position == 160) {
			direction = 0;
		} else if (position == 0) {
			direction = 1;
		}
		if (direction) {
			position++;
		} else {
			position--;
		}
		update_position(&servo, position);
		osDelay(20);
	}*/
	while(1) {
		update_orientation(&orientation);
		update_position(&servo, orientation.moving_average_roll.average / 2 + 50);
		//display_orientation(&orientation);
		osDelay(20);
	}
}
