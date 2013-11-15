#include "CC2500.h"

/** @defgroup STM32F4_DISCOVERY_CC2500_Private_Defines
  * @{
  */
	
__IO uint32_t  CC2500Timeout = CC2500_FLAG_TIMEOUT;

/* Read/Write command */
#define READWRITE_CMD              ((uint8_t)0x80) 
/* Multiple byte read/write command */ 
#define MULTIPLEBYTE_CMD           ((uint8_t)0x40)
/* Dummy Byte Send by the SPI Master device in order to generate the Clock to the Slave device */
#define DUMMY_BYTE                 ((uint8_t)0x00)
