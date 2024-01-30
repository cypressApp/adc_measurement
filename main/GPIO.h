
// 34 35 36 37 38 39 are INPUT olny pins

#if defined SMART_SWITCH_1_DEF || defined SMART_SWITCH_2_DEF || defined SMART_SWITCH_3_DEF

    // #define GPIO_OUTPUT_RELAY_1     18 // 34 INPUT OLNY PINNNN
    // #define GPIO_OUTPUT_RELAY_2     2
    // #define GPIO_OUTPUT_RELAY_3     5
    // #define GPIO_RED_1              19
    // #define GPIO_GREEN_1            19
    // #define GPIO_BLUE_1             23
    // #define GPIO_RED_2              32
    // #define GPIO_GREEN_2            32  /// 35 INPUT OLNY PINNNN
    // #define GPIO_BLUE_2             33
    // #define GPIO_RED_3              26
    // #define GPIO_GREEN_3            26  /// 36 INPUT OLNY PINNNN
    // #define GPIO_BLUE_3             25

    // #define GPIO_OUTPUT_PIN_SEL     ((1ULL<<GPIO_OUTPUT_RELAY_1) | (1ULL<<GPIO_OUTPUT_RELAY_2) | (1ULL<<GPIO_OUTPUT_RELAY_3) | (1ULL<<GPIO_RED_1) | (1ULL<<GPIO_GREEN_1) | (1ULL<<GPIO_BLUE_1))
    #define GPIO_INPUT_REGISTERATION_BUTTON 0
    #define GPIO_INPUT_SEL     (1ULL<<GPIO_INPUT_REGISTERATION_BUTTON)

    #define GPIO_SHIFT_CLK          25  
    #define GPIO_LATCH_CLK          26  
    #define GPIO_SIPO_DATA          23  
    #define GPIO_RS485_DE           18
    #define GPIO_RS485_RE           5
    #define GPIO_REGISTRATION_LED   26
    #define GPIO_OUTPUT_PIN_SEL     ((1ULL<<GPIO_SHIFT_CLK) | (1ULL<<GPIO_LATCH_CLK) | (1ULL<<GPIO_SIPO_DATA) | \
                                     (1ULL<<GPIO_RS485_DE ) | (1ULL<<GPIO_RS485_RE ) | (1ULL<<GPIO_REGISTRATION_LED))

    #define SIPO_RED1_INDEX    6
    #define SIPO_GREEN1_INDEX  5
    #define SIPO_BLUE1_INDEX   7
    #define SIPO_RELAY1_INDEX  1

    #define SIPO_RED2_INDEX    3
    #define SIPO_GREEN2_INDEX  2
    #define SIPO_BLUE2_INDEX   4
    #define SIPO_RELAY2_INDEX  15

    #define SIPO_RED3_INDEX    12
    #define SIPO_GREEN3_INDEX  11
    #define SIPO_BLUE3_INDEX   13
    #define SIPO_RELAY3_INDEX  14	

    extern int  new_sipo_output_array[20];
    extern int  old_sipo_output_array[20]; 
    extern bool sipo_input_changed;
	
#elif defined SMART_OUTLET_1_DEF || defined SMART_OUTLET_2_DEF || defined SMART_OUTLET_3_DEF

    #define GPIO_OUTPUT_RELAY_1          33
    #define GPIO_OUTPUT_RELAY_2          25
    #define GPIO_REGISTRATION_LED        26

    #define GPIO_OUTPUT_PIN_SEL    ((1ULL<<GPIO_OUTPUT_RELAY_1  ) | (1ULL<<GPIO_OUTPUT_RELAY_2    ) | \
                                    (1ULL<<GPIO_REGISTRATION_LED))

    #define GPIO_INPUT_REGISTERATION_BUTTON 0
    #define GPIO_INPUT_BUTTON_1             2
    #define GPIO_INPUT_BUTTON_2             15
    #define GPIO_INPUT_SEL              ((1ULL<<GPIO_INPUT_REGISTERATION_BUTTON) | \
                                         (1ULL<<GPIO_INPUT_BUTTON_1) | (1ULL<<GPIO_INPUT_BUTTON_2)) 
    
#elif defined SECURITY_LOCK_DEF

    #define GPIO_SHIFT_CLK               27//25  
    #define GPIO_LATCH_CLK               14//33  
    #define GPIO_SIPO_DATA               4 //32

    #define GPIO_RS485_DE                15//27
    #define GPIO_RS485_RE                5 //26

    #define GPIO_OUTPUT_RELAY_1          33
    #define GPIO_REGISTRATION_LED        25
    #define GPIO_ADMIN_REGISTRATION_LED  32

    #define GPIO_OUTPUT_PIN_SEL    ((1ULL<<GPIO_SHIFT_CLK       ) | (1ULL<<GPIO_LATCH_CLK             ) | (1ULL<<GPIO_SIPO_DATA     ) | \
                                    (1ULL<<GPIO_RS485_DE        ) | (1ULL<<GPIO_RS485_RE              ) | (1ULL<<GPIO_OUTPUT_RELAY_1) | \
                                    (1ULL<<GPIO_REGISTRATION_LED) | (1ULL<<GPIO_ADMIN_REGISTRATION_LED) )

    #define GPIO_INPUT_REGISTERATION_BUTTON 0
    #define GPIO_INPUT_SEL         (1ULL<<GPIO_INPUT_REGISTERATION_BUTTON) 

    #define SIPO_SEG_1_INDEX   1
    #define SIPO_SEG_2_INDEX   4
    #define SIPO_SEG_3_INDEX   6
    #define SIPO_SEG_4_INDEX   7

    #define SIPO_SEG_A_INDEX   2
    #define SIPO_SEG_B_INDEX   5
    #define SIPO_SEG_C_INDEX   14
    #define SIPO_SEG_D_INDEX   12
    #define SIPO_SEG_E_INDEX   11
    #define SIPO_SEG_F_INDEX   3
    #define SIPO_SEG_G_INDEX   15
    #define SIPO_SEG_H_INDEX   13

// #elif  FOUR_CHANNEL_RGB_DEF
    
#elif defined FOUR_CHANNEL_RELAY_DEF

    #define GPIO_OUTPUT_RELAY_1          33
    #define GPIO_OUTPUT_RELAY_2          25
    #define GPIO_OUTPUT_RELAY_3          32
    #define GPIO_OUTPUT_RELAY_4          27
    #define GPIO_REGISTRATION_ALARM      14
    #define GPIO_REGISTRATION_LED        26

    #define GPIO_OUTPUT_PIN_SEL    ((1ULL<<GPIO_OUTPUT_RELAY_1  ) | (1ULL<<GPIO_OUTPUT_RELAY_2    ) | \
                                    (1ULL<<GPIO_OUTPUT_RELAY_3  ) | (1ULL<<GPIO_OUTPUT_RELAY_4    ) | \
                                    (1ULL<<GPIO_REGISTRATION_LED) | (1ULL<<GPIO_REGISTRATION_ALARM) )

    #define GPIO_INPUT_REGISTERATION_BUTTON 0
    #define GPIO_INPUT_SEL (1ULL<<GPIO_INPUT_REGISTERATION_BUTTON) 

#elif defined DHT_SENSOR_DEF

    #define GPIO_OUTPUT_RELAY_1     33 // 34 INPUT OLNY PINNNN
    #define GPIO_OUTPUT_RELAY_2     25
    #define GPIO_OUTPUT_RELAY_3     32
    #define GPIO_REGISTRATION_LED   26 
    #define GPIO_OUTPUT_PIN_SEL     ((1ULL<<GPIO_OUTPUT_RELAY_1  ) | (1ULL<<GPIO_OUTPUT_RELAY_2) | (1ULL<<GPIO_OUTPUT_RELAY_3) | \
                                     (1ULL<<GPIO_REGISTRATION_LED) )

    #define GPIO_INPUT_REGISTERATION_BUTTON 0
    #define GPIO_INPUT_SEL          (1ULL<<GPIO_INPUT_REGISTERATION_BUTTON)

#elif defined FOUR_CHANNEL_RGB_DEF

#define GPIO_RS485_DE           18
#define GPIO_RS485_RE           5
/*
#define GPIO_OUTPUT_PIN_SEL     ((1ULL<<GPIO_SHIFT_CLK) | (1ULL<<GPIO_LATCH_CLK   ) | (1ULL<<GPIO_SIPO_DATA) | \
                                 (1ULL<<GPIO_RS485_DE) | (1ULL<<GPIO_RS485_RE) )
*/
#define GPIO_RED              33
#define GPIO_GREEN            25 
#define GPIO_BLUE             32
#define GPIO_REGISTRATION_LED 26 

#define GPIO_OUTPUT_PIN_SEL     ((1ULL<<GPIO_RED) | (1ULL<<GPIO_GREEN) | (1ULL<<GPIO_BLUE) | (1ULL<<GPIO_DISCOVERANLE_LED))
#define GPIO_INPUT_REGISTERATION_BUTTON 0
#define GPIO_INPUT_SEL          (1ULL<<GPIO_INPUT_RESET_BUTTON)

#endif

void init_gpio_pins(void);

