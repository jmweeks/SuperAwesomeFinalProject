#include "stm32f4xx.h"

#include "project_servo.h"

void init_servo(struct Servo *servo, uint32_t CCR) {
	servo->CCR = CCR;
	servo->position = 0;
}

void update_position(struct Servo *servo, uint32_t position) {
	uint32_t CCR_value = ((position * (SERVO_MAX_DUTY_CYCLE - SERVO_MIN_DUTY_CYCLE) / SERVO_STEPS) + SERVO_MIN_DUTY_CYCLE) / SERVO_DUTY_CYCLE_STEP;
	switch (servo->CCR) {
		case 1:
			TIM4->CCR1 = CCR_value;
			break;
		case 2:
			TIM4->CCR2 = CCR_value;
			break;
		case 3:
			TIM4->CCR3 = CCR_value;
			break;
		default:
			TIM4->CCR4 = CCR_value;
	}
	servo->position = position;
}
