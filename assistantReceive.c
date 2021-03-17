/*
 * Author Name: Maksim Tybar
 * Email: mtybar@okstate.edu
 * Date: 03/15/2021
 * Program Description: This program implements the assistant role of the mini group project (receiving part)
 */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define BUFFER_SIZE 512
#define MAX_LINES 10

typedef struct Employee {
    int id;
    char name[100];
    char jobTital[100];
    float pay;
    float overtimePay;
    float benefit;
    char status[2];
    int satisfactionLevel;
    int numProject;
    int averageHoursMonthly;
    int timeAtCompanyYears;
    bool workAccident;
    bool promotionFiveYears;
} Employee;

/*
readInputFromManager():
    Reading employee name from Manager thread via pipe and returns the name.
    After phtread_join store the value 
*/

int fd[2]; // File descriptor for pipe queues between Manager and Asisstant

char *readInputFromManager() {

    char *name;
    name = (char*)malloc(sizeof(char) * 30);

    if (read(fd[0], name, sizeof(name)) < 0) {
        perror("Couldn't read from the pipe in Assistant thread.\n");
        return -1;
    }

    printf("Received employee name: %s\n", *name);

    return name;
}

void *assistantReceive() {

    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    printf("Assistant has been created.\n");
	
    /*
    Record result from server in History File (assuming that we already have a history.txt file).
    */

    Employee employee;

    char buffer[BUFFER_SIZE];
    char *empFileName;
    char *empManagerName;
    bool nameFound = false;
    empManagerName = readInputFromManager(); // get employee name from the Manager thread

    FILE *fp;
    fp = fopen("history.txt", "r");
    if (!fp) {
        perror("Couldn't open history.txt file in the Assistant thread.\n");
        return -1;
    }
    
	/* If information found:
            Display info on Separate Terminal
    */

    while (feof(fp) || (!nameFound)) {
        fgets(buffer, 512, fp);
        empFileName = strtok(buffer, ",");
        empFileName = strtok(NULL, ","); // to get the second element in the line

        if (*(empFileName) == (*empManagerName)) {
            /* 
            We found a match in the history file
                so we can send the information back
                to the Manager thread

                employee.id = strtok(buffer, ",");
                strcpy(employee.name, strtok(NULL, ","));
                strcpy(employee.jobTital, strtok(NULL, ","));
                employee.pay = strtok(NULL, ",");
                employee.overtimePay = strtok(NULL, ",");
                employee.benefit = strtok(NULL, ",");
                strcpy(employee.status, strtok(NULL, ","));
                employee.satisfactionLevel = strtok(NULL, ",");
                employee.numProject = strtok(NULL, ",");
                employee.averageHoursMonthly = strtok(NULL, ",");
                employee.timeAtCompanyYears = strtok(NULL, ",");
                employee.workAccident = strtok(NULL, ",");
                employee.promotionFiveYears = strtok(NULL, ",");

            */

        nameFound = true;
    }

    if (nameFound == false) {
        /*
        We don't have a match in the file 
            so we need to make a request to the server
            and fetch the appropriate information via message queue.
        */

       /* 
        We wait for the queue from the server, 
            read the received information
            and display it in the separate terminal.
        Also, we add the employee information to the 
            history.txt file and check if its size
            is greater than 10. If it is greater than 10,
            delete the oldest one.
        */

        
    }


            
	return NULL;
}

/*
History.txt file:

1. Initially empty
2. Can hold only 10 entries (employees) at the time
3. If full, delete oldest entry before adding new one

*/
