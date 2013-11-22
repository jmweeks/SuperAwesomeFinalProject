#include "arm_math.h"

#include "stm32f4xx.h"
#include "cmsis_os.h"

#include "project_init.h"
#include "project_pwm.h"
#include "project_servo.h"
#include "project_filter.h"
#include "project_accelerometer.h"
#include "CC2500.h"


/*!
 @brief Thread to perform menial tasks such as switching LEDs
 @param argument Unused
 */
void thread(void const *argument);

static struct Servo servo;
static struct Orientation orientation;

//! Thread structure for above thread
osThreadDef(thread, osPriorityNormal, 1, 0);

uint8_t  dummyData[2] ={0,0};
uint8_t dummyAddr;
uint8_t dummyWrite;

/*!
 @brief Program entry point
 */
int main (void) {
	osThreadId tid_thread;
	CC2500_Init();
	
	//dummyData = 4;
	//dummyAddr = CC2500_REG_MDMCFG3;
	//dummyWrite = CC2500_CFG_MDMCFG3;
	//CC2500_Read(&dummyData, 0x30, 1);//send reset strobe
	//CC2500_Read(&dummyData, 0x30, 6); //set burst byte to read status reg expected: 0x03 for addr 0x31 and (0x80 for 0x30)
	//CC2500_Write(&dummyWrite, dummyAddr,1);
	//dummyAddr = CC2500_REG_MDMCFG3;
	//CC2500_Read(&dummyData, dummyAddr, 1);
	
	dummyData[0] =2;

	CC2500_Read(dummyData, 0x31, 6);//send SRES reset strobe

	
	dummyData[0] = 0x0A;
	dummyAddr = 0x00;
	
	//CC2500_Write(dummyData, dummyAddr, 1); //write to register 0
	//CC2500_Read(dummyData, dummyAddr, 1); 

	CC2500_config_transmitter();
	
	//CC2500_CFG_FSCTRL1 is 0x0C
 	CC2500_Read(dummyData, CC2500_REG_FSCTRL1, 1); 
	osDelay(1000);
	
	//CC2500_CFG_MDMCFG1 should be 0x42
	CC2500_Read(dummyData, CC2500_REG_MDMCFG1, 1); 

	

	// The below doesn't really need to be in a loop
	while(1){
		CC2500_Read(dummyData, dummyAddr, 1); 
		osDelay(1000);
		//osDelay(osWaitForever);
	}
}

void thread (void const *argument) {
	while(1) {
		osMutexWait(servo.mutexID, osWaitForever);
		servo.position = 180;
		osMutexRelease(servo.mutexID);
		osDelay(10000);
		osMutexWait(servo.mutexID, osWaitForever);
		servo.position = 0;
		osMutexRelease(servo.mutexID);
		osDelay(10000);
	}
}
