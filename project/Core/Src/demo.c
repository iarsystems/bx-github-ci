#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_crc.h"
#include "Fast_CRC32.h"


#pragma language=save
#pragma language=extended

__root const uint32_t __checksum       @ ".checksum";
__root const uint32_t __Checksum_Begin @ ".marker_crc_start" = 0x5A5A5A5A;
__root const uint32_t __Checksum_End   @ ".marker_crc_end"   = 0xA5A5A5A5;

/**
  * @brief Checksum Error Handler
  * @retval None
  */
static void Checksum_ErrorHandler(void)
{
  __disable_irq();
  while (1) { }
}

/**
  * @brief Calculates checksum using STM32F407 HW-CRC
  * @retval CRC result
  */
static bool Self_Checksum(void)
{
  CRC_HandleTypeDef crcHandle = { .Instance = CRC };
  
  uint32_t const * pChecksum_Begin = &__Checksum_Begin;
  uint32_t const * pChecksum_End = &__Checksum_End;
    
  if (HAL_OK != HAL_CRC_Init(&crcHandle))
  {
    /* CRC Peripheral initialization error */
    Checksum_ErrorHandler();
  }
  
  uint32_t appCRC32 = Fast_CRC32(0xFFFFFFFF, pChecksum_Begin, (pChecksum_End - pChecksum_Begin) + 1);

#if !defined(NDEBUG)  
  printf("Checksum starts   @: 0x0%p\n", pChecksum_Begin );
  printf("Checksum ends     @: 0x0%p\n", pChecksum_End );
  printf("Checksum appCRC32  : 0x%08x\n", appCRC32);
#endif  
  
  if (appCRC32 == __checksum)
  {
    return true;
  }
  return false;
}

void demo(void)
{
  bool Pass = Self_Checksum();
#if !defined(NDEBUG)
  printf("App checksum       : 0x%08x\n",__checksum);
#endif    
  if (Pass)
  {
    printf("PASS");
  }
  else
  {
    printf("FAIL");
  }
  
}

#pragma language=restore