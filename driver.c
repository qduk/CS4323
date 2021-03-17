/*
 * Author Name: Adam Byczkowski
 * Email: abyczko@ostatemail.okstate.edu
 * Date: 03/14/2021
 * Program Description: This program creates two threads one for Server and one for Client
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "server.h"
#include "assistant.h"
#include "manager.h"

int main(){
    // Create server thread
    pthread_t server_id;
    pthread_t assistant_id;
    pthread_t manager_id;
    int ret_server;
    int ret_assistant;
    int ret_manager;

    // Start server thread
    ret_server=pthread_create(&server_id,NULL,&server,NULL);

    //Start assistant thread
    ret_assistant=pthread_create(&assistant_id,NULL,&assistant,NULL);

    //Start assistant thread
    ret_manager=pthread_create(&manager_id,NULL,&manager,NULL);

    pthread_join(server_id, NULL);
    pthread_join(assistant_id, NULL);
    pthread_join(manager_id, NULL);

}