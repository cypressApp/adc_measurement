#include <stdio.h>

#define TAG "Cypress"

#define AP_MODE    
#undef STA_MODE    

#define WIFI_STA_TEST_MODE
#undef ENABLE_WIFI_STATIC_IP

#define ESP_AP_WIFI_PASS        "123456789"  
#define DEVICE_MAC_ADDRESS_STR  "C0428A15753C"
#define ESP_AP_WIFI_SSID        "CYPRESS_ADC_15753C"

#define ROUTER_SSID "Xiaomi326589"
#define ROUTER_PASS "majid4321"
#define TCP_PORT    1234

#define SEND_TO_ALL_SOCKET  -2

#define WIFI_STA_MODE_TASK_STACK_DEPTH       20480
#define TCP_SERVER_TASK_STACK_DEPTH          20480
#define CHECK_TCP_TIMEOUT_TASK_STACK_DEPTH   4096

 
