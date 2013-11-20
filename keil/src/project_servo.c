#include "stm32f4xx.h"
#include "cmsis_os.h"

#include "project_servo.h"

void init_servo(struct Servo *servo, uint32_t CCR) {
	servo->CCR = CCR;
	servo->position = 0;
	servo->realPosition = 0;
	osThreadDef(servoThread, osPriorityNormal, 1, 0);
	servo->threadID = osThreadCreate(osThread(servoThread), servo);
	osMutexDef(servoMutex);
	servo->mutexID=osMutexCreate(osMutex(servoMutex));
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
	servo->realPosition = position;
}

void servoThread (void const *argument) {
	struct Servo *servo;
	servo = (struct Servo *)argument;
	while(1) {
		osMutexWait(servo->mutexID, osWaitForever);
		if (servo->position != servo->realPosition) {
			if (servo->position > servo->realPosition) {
				servo->realPosition++;
			} else {
				servo->realPosition--;
			}
			update_position(servo, servo->realPosition);
		}
		osMutexRelease(servo->mutexID);
		osDelay(1000 / SERVO_DEG_PER_SECOND);
	}
}
