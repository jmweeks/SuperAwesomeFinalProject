/*!
	@file project_receiver.c
	Source file for receiver initialization.
*/
#include "stm32f4xx.h"
#include "cmsis_os.h"

#include "project_receiver.h"	

/**  
  * @brief  Function that initializes receiver. 
  * @param  *receiver: pointer to Receiver structure.
  * @retval None  
  */
void init_receiver(struct Receiver *receiver) {
	receiver->state = 0;
	receiver->buffer_space = 0;
	
	CC2500_Init();
	CC2500_config_transmitter();
	goToTX(&(receiver->state), &(receiver->buffer_space));
	
	osMutexDef(receiverMutex);
	receiver->mutexID=osMutexCreate(osMutex(receiverMutex));
}
