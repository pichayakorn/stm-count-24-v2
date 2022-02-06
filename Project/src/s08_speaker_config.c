/* Base registers address header file */
#include "stm32l1xx.h"
/* Library related header files */
#include "stm32l1xx_ll_system.h"
#include "stm32l1xx_ll_bus.h"
#include "stm32l1xx_ll_gpio.h"
#include "stm32l1xx_ll_pwr.h"
#include "stm32l1xx_ll_rcc.h"
#include "stm32l1xx_ll_utils.h"
/* Timer peripheral driver included */
#include "stm32l1xx_ll_tim.h"
/* EXTI driver included */
#include "stm32l1xx_ll_exti.h"
/* STM Music note included */
#include "s08_speaker_config.h"

/* For 3s update event */
#define TIM2_PSC            32000
#define TIM2_ARR            80

/* Fix PSC for key note */
#define TIM4_PSC            2

/* Macro function for ARR calculation */
#define ARR_CALCULATE(N)    ( (32E6) / ((TIM4_PSC) * (N)) )

uint16_t sheetNote[] = {C_6,SP,C_6,SP,C_6,SP,
                        C_6,C_6,C_6,C_6,C_6,C_6,
                        Ab_5,Ab_5,Ab_5,Ab_5,Ab_5,Ab_5,
                        Bb_5,Bb_5,Bb_5,Bb_5,Bb_5,Bb_5,
                        C_6,C_6,SP,SP,Bb_5,Bb_5,
                        C_6,C_6,C_6,C_6,C_6,C_6,
                        C_6,C_6,C_6,C_6,C_6,C_6,
                        C_6,C_6,C_6,SP,SP,SP};

uint16_t cur = 0;
                        
void STM_SOUNDTRACK_CONFIG(void) {
    TIM_OC_Config(ARR_CALCULATE(sheetNote[cur]));
}

void RESET_SOUNDTRACK(void) {
    cur = 0;
	uint16_t ARR = ARR_CALCULATE(sheetNote[cur]);
    LL_TIM_SetAutoReload(TIM4, ARR - 1);
}

void TIM_BASE_Config(uint16_t ARR) {
    LL_TIM_InitTypeDef TIM_InitStruct;
    
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM4);
    
    /* Time-base 4 configure */
    TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
    TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
    TIM_InitStruct.Autoreload = ARR - 1;
    TIM_InitStruct.Prescaler = TIM4_PSC - 1;
    LL_TIM_Init(TIM4, &TIM_InitStruct);
    
    /* Time-base 2 configure */
    TIM_InitStruct.Autoreload = TIM2_ARR - 1;
    TIM_InitStruct.Prescaler = TIM2_PSC - 1;
    LL_TIM_Init(TIM2, &TIM_InitStruct);
}

void TIM_OC_GPIO_Config(void) {
    /* Declare struct for GPIO config */
    LL_GPIO_InitTypeDef GPIO_InitStruct;
    
    /* Enable GPIOB clock */
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
    
    /* Config PB6 as alternate function (TIM4_CH1) */
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Alternate = LL_GPIO_AF_2;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pin = LL_GPIO_PIN_6;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
    
    LL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void TIM_OC_Config(uint16_t note) {
    LL_TIM_OC_InitTypeDef TIM_OC_InitStruct;
    
    TIM_BASE_Config(note);
    TIM_OC_GPIO_Config();
    
    TIM_OC_InitStruct.OCState = LL_TIM_OCSTATE_DISABLE;
    TIM_OC_InitStruct.OCMode = LL_TIM_OCMODE_PWM1;
    TIM_OC_InitStruct.OCPolarity = LL_TIM_OCPOLARITY_HIGH;
    TIM_OC_InitStruct.CompareValue = LL_TIM_GetAutoReload(TIM4) / 2;    //  50% duty
    LL_TIM_OC_Init(TIM4, LL_TIM_CHANNEL_CH1, &TIM_OC_InitStruct);
      
    LL_TIM_ClearFlag_UPDATE(TIM2);
    LL_TIM_EnableIT_UPDATE(TIM2);
    
    /* Interrupt Configure */
    NVIC_SetPriority(TIM2_IRQn, 3);
    NVIC_EnableIRQ(TIM2_IRQn);
    
    NVIC_SetPriority(TIM4_IRQn, 4);
    NVIC_EnableIRQ(TIM4_IRQn);
    LL_TIM_EnableIT_CC1(TIM4);
    
    /* Start Output Compare in PWM Mode */
    //LL_TIM_CC_EnableChannel(TIM4, LL_TIM_CHANNEL_CH1);
    //LL_TIM_EnableCounter(TIM4);
    
    //LL_TIM_EnableCounter(TIM2);
}

void UPDATE_Keynote(uint16_t note) {
    if (note != SP) {
        uint16_t ARR = ARR_CALCULATE(note);
        LL_TIM_SetAutoReload(TIM4, ARR - 1);
        LL_TIM_OC_SetCompareCH1(TIM4, LL_TIM_GetAutoReload(TIM4) / 2);    //  50% duty
    } else {
        LL_TIM_SetAutoReload(TIM4, 1);
        LL_TIM_OC_SetCompareCH1(TIM4, 0);    //  0% duty
    }
}

void TIM2_IRQHandler(void) {
    if (LL_TIM_IsActiveFlag_CC1(TIM2) == SET) {
        LL_TIM_ClearFlag_CC1(TIM2);
        if (cur != sizeof(sheetNote)/sizeof(sheetNote[0]) - 1) {
            UPDATE_Keynote(sheetNote[++cur]);           
        } else {
            LL_TIM_OC_SetCompareCH1(TIM4, 0);    //  0% duty
            RESET_SOUNDTRACK();  
            LL_TIM_DisableCounter(TIM2);
            LL_TIM_DisableCounter(TIM4);
            LL_TIM_DisableIT_UPDATE(TIM2);
            LL_TIM_CC_DisableChannel(TIM4, LL_TIM_CHANNEL_CH1);
        }
    }
}

void TIM4_IRQHandler(void) {
    if (LL_TIM_IsActiveFlag_CC1(TIM4) == SET) {
        LL_TIM_ClearFlag_CC1(TIM4);
    }
}
