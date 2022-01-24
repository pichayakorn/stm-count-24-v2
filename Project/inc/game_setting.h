#include <stdio.h>
#include <stdbool.h>
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
/* EXTI driver included */
#include "stm32l1xx_ll_exti.h"
/* LCD driver included */
#include "stm32l1xx_ll_lcd.h"
#include "stm32l152_glass_lcd.h"
/* Configuration */
#include "systemclock_config.h"
#include "irqhandler_config.h"

#ifndef __game_setting
#define __game_setting

/** BUZZER **/
void BUZZER_ON(void) {
    LL_DAC_Enable(DAC1, LL_DAC_CHANNEL_2);
} // ON

void BUZZER_OFF(void) {
    LL_DAC_Disable(DAC1, LL_DAC_CHANNEL_2);
} // OFF

/** LCD Display **/
void LCD_DISPLAY(char * disp_str) {
    LCD_GLASS_DisplayString((uint8_t*)disp_str);
} // Display string to LCD

void LCD_CLEAR() {
    LCD_GLASS_Clear();
}

/** Is user botton pressed **/
bool isUserBtnPinSet(void) {
    return LL_GPIO_IsInputPinSet(GPIOA, LL_GPIO_PIN_0);
}

/** Matrix switch value **/
uint8_t MATRIX_VALUE(void) {
    if (!state_m1 && !state_m2)     // PA = 0 and PC = 0
        return 0x00;
    if (state_m1 && !state_m2)      // PA = 1 and PC = 0
        return 0x01;
    if (!state_m1 && state_m2)      // PA = 0 and PC = 1
        return 0x02;
    if (state_m1 && state_m2)       // PA = 1 and PC = 1
        return 0x03;
    return 0x00;
}

void RESET_MATRIX_VALUE(void) {
    state_m1 = false;
    state_m2 = false;
}

/** LED **/
void LED_GREEN_ON(void) {
    LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_7);
} // PB7 ON

void LED_GREEN_OFF(void) {
    LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_7);
} // PB7 OFF

void LED_BLUE_ON(void) {
    LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_6);
} // PB6 ON

void LED_BLUE_OFF(void) {
    LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_6);
} // PB6 OFF

void LED_ALL_ON(void) {
    LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_6);
    LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_7);
} // PB6 and PB7 ON

void LED_ALL_OFF(void) {
    LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_6);
    LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_7);
} // PB6 and PB7 ON

#endif
