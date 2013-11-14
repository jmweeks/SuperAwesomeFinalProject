#include "stm32f4xx.h"

#include "project_pwm.h"

#define SERVO_STEPS 160
#define SERVO_FREQUENCY 50
#define SERVO_MIN_DUTY_CYCLE 0.025f
#define SERVO_MAX_DUTY_CYCLE 0.125f
#define SERVO_DUTY_CYCLE_STEP ((SERVO_MAX_DUTY_CYCLE-SERVO_MIN_DUTY_CYCLE)/SERVO_STEPS)

struct Servo {
	uint32_t CCR;
	uint32_t position;
};

void init_servo(struct Servo *servo, uint32_t CCR);
void update_position(struct Servo *servo, uint32_t position);
