// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 

#define PORT 8080 
   
int main(int argc, char const *argv[]) 
{ 
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    char name[100];
    char buffer[200]; 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 

    while (1) { 
        printf("Enter the name you want to send: ");
        fgets(name, 100, stdin);
        name[strcspn(name, "\n")] = 0; // Removing the new line

        send(sock, name, strlen(name), 0); 
        printf("Name sent from the client.\n");

        read(sock, buffer, 100); 
        printf("Job title recieved from client: %s\n", buffer);

        read(sock, buffer, 100); 
        printf("Pay recieved from client: %s\n", buffer);

        read(sock, buffer, 100); 
        printf("Overtime pay recieved from client: %s\n", buffer);

        read(sock, buffer, 100); 
        printf("Benefit pay recieved from client: %s\n", buffer);

        read(sock, buffer, 100); 
        printf("Status recieved from client: %s\n", buffer);
    }

    return 0; 
} 