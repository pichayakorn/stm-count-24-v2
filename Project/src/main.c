#include <stdio.h>
#include <stdbool.h>
#include "stdlib.h"
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
#include "c11_stm32l152rb_config.h"
#include "irqhandler_config.h"
/* In-game functions */
#include "game_setting.h"

void game_loading(void);

int main()
{
    /** C11:Count 24 game register configuration **/
    C11_STM32L152RB_CONFIG();

    while(1) {
        int sum = 0;                                // In-game main counter
        int i = 1;                                  // For random rand() seed
        bool check_win = true;		                // Check player status: default true
        int playerSelect = 0;                       // Player selected value
        int computerSelect = 0;                     // Computer selected value
        char disp_str[7];                           // Temporary LCD output string
        
        game_loading();

        /** Game start **/
        while (sum < 24) {
            /**  Player turn
              *  Player select value using matrix switch 
              *  Press user-botton to confirm selected value
              **/
            BUZZER_ON();
            LL_mDelay(200);
            BUZZER_OFF();
            while(!isUserBtnPinSet()) {
                switch(MATRIX_VALUE()) {
                    case 0:                         // Default value +1
                        playerSelect = 1;
                        sprintf(disp_str, "%2d-P-%d", sum, playerSelect);
                        LCD_DISPLAY(disp_str);
                        LED_ALL_OFF();
                        break;
                    case 1:
                        playerSelect = 2;
                        sprintf(disp_str, "%2d-P-%d", sum, playerSelect);
                        LCD_DISPLAY(disp_str);
                        LED_ALL_OFF();
                        LED_BLUE_ON();
                        break;
                    case 2:
                        playerSelect = 3;
                        sprintf(disp_str, "%2d-P-%d", sum, playerSelect);
                        LCD_DISPLAY(disp_str);
                        LED_ALL_OFF();
                        LED_GREEN_ON();
                        break;
                    case 3:
                        srand(i++);
                        playerSelect = rand() % 3 + 1;
                        sprintf(disp_str, "%2d-P-R", sum);
                        LCD_DISPLAY(disp_str);
                        LED_ALL_ON();
                        break;
                }
            }
            LED_ALL_OFF();
            /** Display player selected value **/
            sprintf(disp_str, "%2d-P-%d", sum, playerSelect);
            LCD_DISPLAY(disp_str);
            LL_mDelay(500);

            /** Increase counter value **/
            sum += playerSelect;

            /** Checking if over 24, player lose **/
            if (sum >= 24)
                check_win = false;
            
            /** Player display: Limited display at 24 **/
            sprintf(disp_str, "%2d-P--", check_win?sum:24);
            LCD_DISPLAY(disp_str);
            LL_mDelay(800);
            
            /** Computer turn **/
            if (check_win) {
                if (sum < 20) {
                    srand(i++);
                    computerSelect = rand() % 3 + 1;
                }
                else if (sum < 23) {
                    computerSelect = 23 - sum;
                }
                else {
                    computerSelect = 1;              // Player left at 23. Computer +1 lose
                }
                /** Display computer selected value **/
                sprintf(disp_str, "%2d-C-%d", sum, computerSelect);
                LCD_DISPLAY(disp_str);
                LL_mDelay(800);

                /** Increase counter value **/
                sum += computerSelect;

                /** Computer display: Limited display at 24 **/
                sprintf(disp_str, "%2d-C--", check_win?sum:24);
                LCD_DISPLAY(disp_str);
                LL_mDelay(600);
            }

            /** Reset Matrix value to default **/
            RESET_MATRIX_VALUE();
        }
        
        /** Display player status **/
        sprintf(disp_str, "P-%s", check_win?"WIN ":"LOSE");
        LCD_DISPLAY(disp_str);

        /** Bip! Bip! **/
        BUZZER_ON();
        LL_mDelay(200);
        BUZZER_OFF();
        LL_mDelay(200);
        BUZZER_ON();
        LL_mDelay(200);
        BUZZER_OFF();

        /** Try again **/
        while(!isUserBtnPinSet());      // Press user button to play again
        LL_mDelay(500);
    }
}

void game_loading(void) {
    LCD_DISPLAY("I");
    LL_mDelay(100);
    LCD_DISPLAY("II");
    LL_mDelay(100);
    LCD_DISPLAY("III");
    LL_mDelay(100);
    LCD_DISPLAY("IIII");
    LL_mDelay(100);
    LCD_DISPLAY("IIIII");
    LL_mDelay(100);
    LCD_DISPLAY("IIIIII");
    LL_mDelay(100);

    LCD_DISPLAY("READY ");
    while(!isUserBtnPinSet());      // Press user button to start
    LL_mDelay(400);
    LCD_CLEAR();
}
