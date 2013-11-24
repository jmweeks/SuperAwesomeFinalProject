#include "stm32f4xx.h"

#include "project_servo.h"

struct Robot {
	struct Servo *boomServo;
	struct Servo *crowdServo;
	struct Servo *swingServo;
	uint32_t positionY;
	uint32_t positionZ;
	uint32_t angle;
	uint32_t boomPosition;
	uint32_t crowdPosition;
	uint32_t swingPosition;
};

void init_robot(struct Robot *robot, struct Servo *boomServo, struct Servo *crowdServo, struct Servo *swingServo);
void moveRobot(struct Robot *robot, uint32_t positionY, uint32_t positionZ, uint32_t angle);
void waitUntilRobotStopped(struct Robot *robot);
void floatRobot(struct Robot *robot);
