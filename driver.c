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

int main(){
    // Create server thread
    pthread_t server_id;
    pthread_t client_id;
    int ret_server;
    int ret_client;

    // Start server thread
    ret_server=pthread_create(&server_id,NULL,&server,NULL);

    //Start client thread
    //ret_server=pthread_create(&server_id,NULL,&tclient,NULL);


    pthread_join(server_id, NULL);

}