#include "stm32f4xx.h"

#include "project_robot.h"

static void updateRobotPosition(struct Robot *robot) {
	robot->boomPosition = robot->positionY;
	robot->crowdPosition = robot->positionZ;
	robot->swingPosition = robot->angle;
}

void waitUntilRobotStopped(struct Robot *robot) {
	waitUntilServoStopped(robot->boomServo);
	waitUntilServoStopped(robot->crowdServo);
	waitUntilServoStopped(robot->swingServo);
}

void init_robot(struct Robot *robot, struct Servo *boomServo, struct Servo *crowdServo, struct Servo *swingServo) {
	robot->boomServo = boomServo;
	robot->crowdServo = crowdServo;
	robot->swingServo = swingServo;
	
	robot->boomPosition = robot->boomServo->minPosition;
	robot->crowdPosition = robot->crowdServo->minPosition;
	robot->swingPosition = robot->swingServo->minPosition;
	
	robot->positionY = 0;
	robot->positionZ = 0;
	robot->angle = 0;
}

void moveRobot(struct Robot *robot, uint32_t positionY, uint32_t positionZ, uint32_t angle) {
	robot->positionY = positionY;
	robot->positionZ = positionZ;
	robot->angle = angle;
	
	updateRobotPosition(robot);
	
	moveServo(robot->boomServo, robot->boomServo->maxPosition);
	waitUntilServoStopped(robot->boomServo);
	
	moveServo(robot->crowdServo, robot->crowdPosition);
	moveServo(robot->swingServo, robot->swingPosition);
	waitUntilRobotStopped(robot);
	
	moveServo(robot->boomServo, robot->boomPosition);
	waitUntilServoStopped(robot->boomServo);
}

void floatRobot(struct Robot *robot) {
	floatServo(robot->boomServo);
	floatServo(robot->crowdServo);
	floatServo(robot->swingServo);
}
