#ifndef __s08_speaker_conf
#define __s08_speaker_conf

/* Key note */
#define SP                  (uint16_t)1

#define B_3                 (uint16_t)245
#define C_4                 (uint16_t)262
#define Db_4                (uint16_t)277
#define D_4                 (uint16_t)293
#define Eb_4                (uint16_t)311
#define E_4                 (uint16_t)329
#define F_4                 (uint16_t)349
#define Gb_4                (uint16_t)370
#define G_4                 (uint16_t)392
#define Ab_4                (uint16_t)415
#define A_4                 (uint16_t)440
#define Bb_4                (uint16_t)466
#define B_4                 (uint16_t)494
#define C_5                 (uint16_t)523
#define Db_5                (uint16_t)554
#define D_5                 (uint16_t)587
#define E_5                 (uint16_t)659
#define F_5                 (uint16_t)698
#define Gb_5                (uint16_t)740
#define G_5                 (uint16_t)784
#define Ab_5                (uint16_t)830
#define A_5                 (uint16_t)880
#define Bb_5                (uint16_t)932
#define B_5                 (uint16_t)988
#define C_6                 (uint16_t)1046
#define Db_6                (uint16_t)1109
#define D_6                 (uint16_t)1174
#define Eb_6                (uint16_t)1244
#define E_6                 (uint16_t)1318

void TIM_BASE_Config(uint16_t);
void TIM_OC_GPIO_Config(void);
void TIM_OC_Config(uint16_t);
void UPDATE_Keynote(uint16_t);
void STM_SOUNDTRACK_CONFIG(void);
void RESET_SOUNDTRACK(void);

#endif
