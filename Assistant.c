#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "structure.h"
#define PORT 8080

/*
Assistant.c is the first half of the assistant
Written by Kayla Walkup
*/

//function declaration
int fileSearch();

struct User *userPtr, user;

int main(int argc, char const *argv[])
{

    //printf("Hello, World! \n");

//====== Socket Setup ======================================================
    //initializing socket vars
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    //create socket, print error and exit if fail
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket");
        return -1;
    }

    //setting addresses
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Converting IPv4 and IPv6 addresses to binary, exit if fail
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
    {
        perror("inet_pton");
        return -1;
    }

//==================================================================================
    
    
//==== Open History File ==================================================================
    

//==================================================================================


    userPtr = &user;
    //int for the pipe
    int fd1;

    // FIFO file path
    char *myfifo = "myfifo.txt";

    char str1[80];
    char str2[80];
    char str3[80];

    
    int i = 0;

    fd1 = open(myfifo, O_RDONLY);
    //printf("pipe open!\n");
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    {
        perror("connect");
    }

    while(1)
    {
        if(read(fd1, str1, 80) > 0)
        {
            strcpy(userPtr->employeeName, str1);

            read(fd1, str2, 80); 
            strcpy(userPtr->jobTitle, str2); 

            read(fd1, str3, 80);
            strcpy(userPtr->status, str3); 
            

            if(fileSearch() == 1)
            {
                //sending employee information to server from struct
                send(sock, userPtr->employeeName, strlen(userPtr->employeeName), 0);
                send(sock, userPtr->jobTitle, strlen(userPtr->jobTitle), 0);
                send(sock, userPtr->status, strlen(userPtr->status), 0);

                //print statement to test the send worked
                printf("Employee sent!\n"); 
            }

     
        }
    }
        
        

    

//======================================================================================

    
    return 0;
}

int fileSearch()
{
    //opening file
    FILE *filep;
    char *filename = "history.txt";
    filep = fopen(filename, "a+");
    if (filep == NULL)
    {
        perror("Error: ");
        exit(0); 
    }

    char line[256];

    
    while (fgets(line, sizeof(line), filep)) 
    {
      
       if(strstr(line, userPtr->employeeName))
       {
           if(strstr(line, userPtr->jobTitle) && strstr(line, userPtr->status))
           {
               printf("%s\n", line);
               return 0;
           }
           
       }
       else
       {
           return 1;
       }

       return 1;
    }
    

  


    fclose(filep);

    return 0;
}