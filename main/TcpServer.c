#include "context.h"

#define CLOSE_TCP_SOCKET_DELAY  100
#define MAX_TCP_ACCOUNT_SIZE    100

int  tcp_timeout_counter  = 0    ;
int  tcp_rec_data_counter = 0    ;
bool is_tcp_timeout       = false;
bool valid_data_received  = false;
struct account_struct account_struct_list[MAX_TCP_ACCOUNT_SIZE];
int   account_list_size = 0;

void init_tcp_server(){

    for(int i = 0 ; i < MAX_TCP_ACCOUNT_SIZE ; i++){
        account_struct_list[i].sock = -1; 
    }

}

void tcp_send_to_clients(char *data , int len){
  
    for(int i = 0 ; i < MAX_TCP_ACCOUNT_SIZE ; i++){

        if(account_struct_list[i].sock != -1){

            if(account_struct_list[i].ip4 > 0 && account_struct_list[i].ip4 < 255){
                send(account_struct_list[i].sock, data, len, 0);
            }            
            
        }

    }

}

void process_tcp_data(char* rx_buffer , int sock){



}

void check_tcp_recv_timeout_task(void *pvParameters){

    while(tcp_timeout_counter < 5){
        if(!valid_data_received){
            tcp_timeout_counter ++;
            vTaskDelay(1 / portTICK_PERIOD_MS);
        }else{
            break;
        }
    }

    is_tcp_timeout = true;

    vTaskDelete(NULL);
}

void receiving_tcp_data(int sock , int account_index){

    char temp_rx_buffer[5];
    char rx_buffer[8192];
    
    valid_data_received = true;
    vTaskDelay(2 / portTICK_PERIOD_MS);
    valid_data_received = false;
    tcp_timeout_counter = 0;
    tcp_rec_data_counter = 0;
    is_tcp_timeout      = false;

    while (1) {
        //vTaskDelay(50 / portTICK_RATE_MS);
        //int len = recv(sock, rx_buffer, 8 , 0);
        int len = recv(sock, temp_rx_buffer, 1 , 0);
        tcp_rec_data_counter ++;
        // Error occured during receiving
        if (len < 0) {
#ifdef TCP_TEST_MODE            
            ESP_LOGE(TAG, "recv failed: errno %d", errno);
#endif            
            break;
        }
        // Connection closed
        else if (len == 0) {
#ifdef TCP_TEST_MODE            
            ESP_LOGI(TAG, "Connection closed");
#endif            
            break;
        }
        // Data received
        else {

            rx_buffer[tcp_rec_data_counter - 1] = temp_rx_buffer[0];
            if(tcp_rec_data_counter > 6144){
                tcp_rec_data_counter = 0;
            }else if(tcp_rec_data_counter >= 2){
                if(!update_firmware_mode){
                    if(rx_buffer[tcp_rec_data_counter - 2] == 0x0D && rx_buffer[tcp_rec_data_counter - 1] == 0x0A){
                        
                        rx_buffer[tcp_rec_data_counter] = 0; 
                        tcp_rec_data_counter = 0;
#ifdef TCP_TEST_MODE                         
                        ESP_LOGI(TAG, "%s   %d", rx_buffer , sizeof(rx_buffer));
#endif                        
                        valid_data_received = true;
                        //process_tcp_data(rx_buffer , account_struct_list[account_index].sock);
                        process_tcp_data(rx_buffer , sock);
                        vTaskDelay(1 / portTICK_PERIOD_MS);

                    }
                }else{
                    
                    if(tcp_rec_data_counter >= update_firmware_buffer_size){
                        rx_buffer[tcp_rec_data_counter] = 0; 
                        tcp_rec_data_counter = 0;
#ifdef TCP_TEST_MODE 
                        ESP_LOGI(TAG, "%s   %d", rx_buffer , sizeof(rx_buffer));
#endif
                        valid_data_received = true;
                        process_tcp_data(rx_buffer , sock);
                        vTaskDelay(1 / portTICK_PERIOD_MS);                       
                    }
                }


            }else if(tcp_rec_data_counter == 1){
                valid_data_received = false;
                tcp_timeout_counter = 0;
                is_tcp_timeout = false;
                //xTaskCreate(check_tcp_recv_timeout_task, "check_tcp_recv_timeout", 4096, account_struct_list[account_index].sock , 5, NULL);
                xTaskCreate(check_tcp_recv_timeout_task, "check_tcp_recv_timeout", CHECK_TCP_TIMEOUT_TASK_STACK_DEPTH, sock , 5, NULL);
            }

        }
        
    }
#ifdef TCP_TEST_MODE
    ESP_LOGE(TAG, "Shutting down socket and restarting...");
#endif    
    shutdown(account_struct_list[account_index].sock, 0);
    close(account_struct_list[account_index].sock);
    account_struct_list[account_index].sock = -1;

    vTaskDelete(NULL);
        
}

int is_tcp_socket_exist(int ip){

    // if(account_list_size == 0){
    //     return -1;
    // }

    // for(int i = 0 ; i < account_list_size ; i++){
    //     if(account_struct_list[i].ip4 == ip){
    //         return i;
    //     }
    // }

    for(int i = 0 ; i < MAX_TCP_ACCOUNT_SIZE ; i++){
        if(account_struct_list[i].sock == -1){
            return i;
        }
    }    

    return -1;
}

void tcp_server_task(void *pvParameters)
{
    char addr_str[128];
    int addr_family = (int)pvParameters;
    int ip_protocol = 0;
    struct sockaddr_storage dest_addr;
    int listen_sock;

    while(1){

        if (addr_family == AF_INET) {
            struct sockaddr_in *dest_addr_ip4 = (struct sockaddr_in *)&dest_addr;
            dest_addr_ip4->sin_addr.s_addr = htonl(INADDR_ANY);
            dest_addr_ip4->sin_family = AF_INET;
            dest_addr_ip4->sin_port = htons(TCP_PORT);
            ip_protocol = IPPROTO_IP;
        }

        listen_sock = socket(addr_family, SOCK_STREAM, ip_protocol);
        if (listen_sock < 0) {
#ifdef TCP_TEST_MODE
            ESP_LOGE(TAG, "Unable to create socket: errno %d", errno);
#endif                        
            vTaskDelete(NULL);
            return;
        }

        int opt = 1;
        setsockopt(listen_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
#ifdef TCP_TEST_MODE
        ESP_LOGI(TAG, "Socket created");
#endif
        int err = bind(listen_sock, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
#ifdef TCP_TEST_MODE
        if (err != 0) {            
            ESP_LOGE(TAG, "Socket unable to bind: errno %d", errno);
            ESP_LOGE(TAG, "IPPROTO: %d", addr_family);           
        //    goto CLEAN_UP;
        }      
        ESP_LOGI(TAG, "Socket bound, port %d", TCP_PORT);
#endif
        err = listen(listen_sock, 10);

#ifdef TCP_TEST_MODE
        if (err != 0) {
            ESP_LOGE(TAG, "Error occurred during listen: errno %d", errno);
        //    goto CLEAN_UP;
        }
#endif
        while (1) {
#ifdef TCP_TEST_MODE
            ESP_LOGI(TAG, "Socket listening");
#endif
            struct sockaddr_storage source_addr; 
            socklen_t addr_len = sizeof(source_addr);
            int sock = accept(listen_sock, (struct sockaddr *)&source_addr, &addr_len);
            if (sock < 0) {
#ifdef TCP_TEST_MODE                
                ESP_LOGE(TAG, "Unable to accept connection: errno %d", errno);
#endif                
                break;
            }

            if (source_addr.ss_family == PF_INET) {
                inet_ntoa_r(((struct sockaddr_in *)&source_addr)->sin_addr, addr_str, sizeof(addr_str) - 1);
            }
#ifdef TCP_TEST_MODE             
            printf("SOCKET SIZE: %d\n" , account_list_size);
#endif            
            int temp_ip4 = get_ip4(addr_str , sizeof(addr_str));
#ifdef TCP_TEST_MODE
            ESP_LOGI(TAG, "Socket accepted ip address: %d", temp_ip4);
#endif
            if(temp_ip4 < 255){
                
                int temp_tcp_sock_index = is_tcp_socket_exist(temp_ip4);

                if(temp_tcp_sock_index != -1){
                    close(account_struct_list[temp_tcp_sock_index].sock);
                    vTaskDelay(CLOSE_TCP_SOCKET_DELAY / portTICK_PERIOD_MS);
                    account_struct_list[temp_tcp_sock_index].sock = sock;
                    account_struct_list[temp_tcp_sock_index].ip4 = temp_ip4;
                    xTaskCreate(receiving_tcp_data, "receiving_tcp_data", TCP_SERVER_TASK_STACK_DEPTH, sock , 5, NULL); 
#ifdef TCP_TEST_MODE                    
                    ESP_LOGI(TAG, "Socket Exist");
#endif                    
                }else{
                    close(sock);
                } 

            }

        }
        
    }

    vTaskDelay(1000 / portTICK_PERIOD_MS);
    xTaskCreate(tcp_server_task, "tcp_server", TCP_SERVER_TASK_STACK_DEPTH, (void*)AF_INET, 5, NULL);
    vTaskDelete(NULL);

}

