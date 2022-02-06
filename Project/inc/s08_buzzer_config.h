#ifndef __s08_buzzer_conf
#define __s08_buzzer_conf

/* Base register address header file */
#include "stm32l1xx.h"
/* Base LL driver included */
#include "stm32l1xx_ll_system.h"
#include "stm32l1xx_ll_rcc.h"
#include "stm32l1xx_ll_gpio.h"
#include "stm32l1xx_ll_pwr.h"
#include "stm32l1xx_ll_utils.h"
#include "stm32l1xx_ll_bus.h"
/* DAC driver included */
#include "stm32l1xx_ll_dac.h"

void S08_STM_BUZZER_CONFIG(void)
{
    /* Declare struct for GPIO config */
    LL_GPIO_InitTypeDef GPIO_InitStruct;
    
    /* Enable GPIOB clock */
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
    
    /* Enable DAC clock */
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_DAC1);
    
    /* Config DAC GPIOA PA5 as analog */
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pin = LL_GPIO_PIN_5;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
    LL_GPIO_Init(GPIOA, &GPIO_InitStruct);                  // Write configure value to registers 
    
    //LL_DAC_Enable(DAC1, LL_DAC_CHANNEL_2);
    LL_DAC_ConvertData12RightAligned(DAC1, LL_DAC_CHANNEL_2, 0xFFF);
}
#endif
