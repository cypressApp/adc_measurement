#include "context.h"

#if (defined SMART_SWITCH_1_DEF || defined SMART_SWITCH_2_DEF || defined SMART_SWITCH_3_DEF || \
     defined SECURITY_LOCK_DEF )
    int new_sipo_output_array[20]  = {0};
    int old_sipo_output_array[20]  = {0}; 
    bool sipo_input_changed        = false;
#endif

void init_gpio_pins(void){

#if (defined FOUR_CHANNEL_RELAY_DEF ||  \
     defined SMART_SWITCH_1_DEF || defined SMART_SWITCH_2_DEF || defined SMART_SWITCH_3_DEF || \
     defined SMART_OUTLET_1_DEF || defined SMART_OUTLET_2_DEF || defined SMART_OUTLET_3_DEF || \
     defined DHT_SENSOR_DEF     || defined SECURITY_LOCK_DEF )

    gpio_config_t io_conf;
    //disable interrupt
    io_conf.intr_type = GPIO_INTR_DISABLE;
    //set as output mode
    io_conf.mode = GPIO_MODE_INPUT_OUTPUT;
    //bit mask of the pins that you want to 
    io_conf.pin_bit_mask = GPIO_OUTPUT_PIN_SEL;
    //disable pull-down mode
    io_conf.pull_down_en = 0;
    //disable pull-up mode
    io_conf.pull_up_en = 0;
    //configure GPIO with the given settings
    gpio_config(&io_conf);

#if (defined FOUR_CHANNEL_RELAY_DEF || \
    defined SMART_SWITCH_1_DEF || defined SMART_SWITCH_2_DEF || defined SMART_SWITCH_3_DEF || \
    defined SMART_OUTLET_1_DEF || defined SMART_OUTLET_2_DEF || defined SMART_OUTLET_3_DEF || \
    defined DHT_SENSOR_DEF     || defined SECURITY_LOCK_DEF )
    //disable interrupt
    io_conf.intr_type = GPIO_INTR_DISABLE;
    //set as output mode
    io_conf.mode = GPIO_MODE_INPUT;
    //bit mask of the pins that you want to 
    io_conf.pin_bit_mask = GPIO_INPUT_SEL;
    //disable pull-down mode
    io_conf.pull_down_en = 0;
    //disable pull-up mode
    io_conf.pull_up_en = 1;
    //configure GPIO with the given settings
    gpio_config(&io_conf);
#endif

#endif

    // //disable interrupt
    // io_conf.intr_type = GPIO_INTR_NEGEDGE;
    // //bit mask of the pins, use GPIO14 here
    // io_conf.pin_bit_mask = GPIO_INPUT_SEL;
    // //set as input mode
    // io_conf.mode = GPIO_MODE_INPUT;
    // //enable pull-up mode
    // io_conf.pull_up_en = 1;
    // //disable pull-down mode
    // io_conf.pull_down_en = 0;
    // gpio_config(&io_conf);
    
    
    // //create a queue to handle gpio event from isr
    // gpio_evt_queue = xQueueCreate(10, sizeof(uint32_t));
    
    // //install gpio isr service
    // gpio_install_isr_service(0);
    // //hook isr handler for specific gpio pin
    // gpio_isr_handler_add(GPIO_INPUT_RESET_BUTTON, gpio_isr_handler, (void *) GPIO_INPUT_RESET_BUTTON);
    
}

