#ifndef __s08_stm32l152rb_conf
#define __s08_stm32l152rb_conf

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
#include "s08_matrix_switch_config.h"
#include "s08_lcd_config.h"
#include "s08_led_config.h"
#include "s08_buzzer_config.h"
#include "s08_speaker_config.h"

void S08_STM32L152RB_CONFIG(void)
{
	SystemClock_Config();               // Max-performance configure
	S08_STM_LCD_CONFIG();				// LCD Configuration
	S08_STM_MATRIX_SWITCH_CONFIG();		// 1x2 Matrix switch Configuration
	S08_STM_BUZZER_CONFIG();			// Buzzer Configuration
	S08_STM_LED_CONFIG();				// 2xLED Configuration
	STM_SOUNDTRACK_CONFIG();			// Speaker Configuration
}
#endif
