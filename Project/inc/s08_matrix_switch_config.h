#ifndef __matrix_switch_conf
#define __matrix_switch_conf

/* Base register address header file */
#include "stm32l1xx.h"
/* Base LL driver included */
#include "stm32l1xx_ll_system.h"
#include "stm32l1xx_ll_rcc.h"
#include "stm32l1xx_ll_gpio.h"
#include "stm32l1xx_ll_pwr.h"
#include "stm32l1xx_ll_utils.h"
#include "stm32l1xx_ll_bus.h"
/* EXTI driver included */
#include "stm32l1xx_ll_exti.h"
/* Configuration */
#include "s08_irqhandler_config.h"

void S08_STM_MATRIX_SWITCH_CONFIG(void)
{
    /* Declare struct for GPIO config */
    LL_GPIO_InitTypeDef GPIO_InitStruct;
    
    /* Enable GPIOA, GPIOC clock */
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
    
    /* Enable System configuration controller clock */
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);

    /* Config User-Botton GPIOA PA0 as input */
    GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
    GPIO_InitStruct.Pin = LL_GPIO_PIN_0;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
    LL_GPIO_Init(GPIOA, &GPIO_InitStruct);                  // Write configure value to registers
    
    /* Config Matrix-switch1 GPIOA PA11 as input */
    GPIO_InitStruct.Pin = LL_GPIO_PIN_11;
    LL_GPIO_Init(GPIOA, &GPIO_InitStruct);                  // Write configure value to registers
    
    /* Config Matrix-switch2 GPIOA PC12 as input */
    GPIO_InitStruct.Pin = LL_GPIO_PIN_12;
    LL_GPIO_Init(GPIOC, &GPIO_InitStruct);                  // Write configure value to registers
    
    /* EXTI Line 0 (EXTI0) for PA0 */
    LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTA, LL_SYSCFG_EXTI_LINE0);
    LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_0);
    LL_EXTI_EnableRisingTrig_0_31(LL_EXTI_LINE_0);
    
    /* EXTI Line 11 (EXTI11) for PA11 */
    LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTA, LL_SYSCFG_EXTI_LINE11);
    LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_11);
    LL_EXTI_EnableFallingTrig_0_31(LL_EXTI_LINE_11);
    
    /* EXTI Line 12 (EXTI12) for PC12 */
    LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTC, LL_SYSCFG_EXTI_LINE12);
    LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_12);
    LL_EXTI_EnableFallingTrig_0_31(LL_EXTI_LINE_12);
    
    /* NVIC */
    NVIC_EnableIRQ((IRQn_Type) 6);
    NVIC_SetPriority((IRQn_Type) 6, 0);
    NVIC_EnableIRQ((IRQn_Type) 40);
    NVIC_SetPriority((IRQn_Type) 40, 1);
}
#endif
