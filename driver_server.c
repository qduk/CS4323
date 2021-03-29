/*
 * Author Name: Adam Byczkowski
 * Email: abyczko@ostatemail.okstate.edu
 * Date: 03/14/2021
 * Program Description: Driver file for server process
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include "server.h"
#include "assistant.h"
#include "manager.h"

int main(){
    pthread_t server_id;
    int ret_server;

    // Start server thread
    ret_server=pthread_create(&server_id,NULL,&server,NULL);

    pthread_join(server_id, NULL);

}