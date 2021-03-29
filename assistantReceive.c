/*
 * Author Name: Maksim Tybar
 * Email: mtybar@okstate.edu
 * Date: 03/15/2021
 * Program Description: This program implements the assistant role of the mini group project (receiving part)
*/

// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <stdbool.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <stdlib.h>
#include <pthread.h>

#define PORT 8080 
#define BUFFER_SIZE 512
   
int main(int argc, char const *argv[]) 
{ 
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    char buffer[BUFFER_SIZE];  

    char empName[100];
    char empID[100];
    char jobTitle[100];
    char pay[100];
    char overtimePay[100];
    char benefitPay[100];
    char statusReceived[100];
    char satisfactionLevel[5];
    char numberProject[5];
    char monthlyHours[5];
    char yearsAtCompany[5];
    char workAccident[5];
    char promotionGiveYears[5];

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <=0 ) { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 

    while (1) { 

        int lineCount = 0;
        int count = 0;
        int lineToRemove = 0;
        
        /*
            Reading each parameter from the server.
        */
        read(sock, empName, 100);
        printf("Job title recieved from server: %s\n", empName);

        read(sock, empID, 100);
        printf("Job title recieved from server: %s\n", empID);

        read(sock, jobTitle, 100); 
        printf("Job title recieved from server: %s\n", jobTitle);

        read(sock, pay, 100); 
        printf("Pay recieved from server: %s\n", pay);

        read(sock, overtimePay, 100); 
        printf("Overtime pay recieved from server: %s\n", overtimePay);

        read(sock, benefitPay, 100); 
        printf("Benefit pay recieved from server: %s\n", benefitPay);

        read(sock, statusReceived, 100); 
        printf("Status recieved from server: %s\n", statusReceived);

        read(sock, satisfactionLevel, 100);
        printf("Satisfaction level received from server: %s\n", satisfactionLevel);
        
        read(sock, numberProject, 100);
        printf("Number project received from server: %s\n", numberProject);

        read(sock, monthlyHours, 100);
        printf("Monthly numbers received from server: %s\n", monthlyHours);

        read(sock, yearsAtCompany, 100);
        printf("Years at company received from server: %s\n", yearsAtCompany);

        read(sock, workAccident, 100);
        printf("Work accident received from server: %s", workAccident);

        read(sock, promotionGiveYears, 100);
        printf("Promotion give years received from server: %s", promotionGiveYears);
        
        lineToRemove = (lineToRemove + 1) % 11;
        FILE *fp;
        FILE *temp;

        /*
            If there is 10 entrees in the history file, 
            copy everything to the new history file and rewrite
            the appropriate line.
        */
        if (lineCount == 10) {
            fp = fopen("history.txt", "r");
            temp = fopen("history_temp.txt", "w");

            while ((fgets(buffer, BUFFER_SIZE, fp)) != NULL) { 
                count = (count + 1) % 11;
                if (count == 0) {
                    count ++;
                }

                if (lineToRemove == count) {
                    fprintf(fp, "%s,", empName);
                    fprintf(fp, "%s,", empID);
                    fprintf(fp, "%s,", jobTitle);
                    fprintf(fp, "%s,", pay);
                    fprintf(fp, "%s,", overtimePay);
                    fprintf(fp, "%s,", benefitPay);
                    fprintf(fp, "%s,", statusReceived);
                    fprintf(fp, "%s,", satisfactionLevel);
                    fprintf(fp, "%s,", numberProject);
                    fprintf(fp, "%s,", monthlyHours);
                    fprintf(fp, "%s,", yearsAtCompany);
                    fprintf(fp, "%s,", workAccident);
                    fprintf(fp, "%s,", promotionGiveYears);
                    fprintf(fp, "\n");
                } else {
                    fprintf(fp, "%s,", buffer);
                }
            }

            fclose(fp);
            fclose(temp);

        } else {
            lineCount ++;
            fp = fopen("history.txt", "a");

            if (!fp) {
                perror("Couldn't open history.txt file in the Assistant thread.\n");
                return -1;
            } 
            fprintf(fp, "%s,", empName);
            fprintf(fp, "%s,", empID);
            fprintf(fp, "%s,", jobTitle);
            fprintf(fp, "%s,", pay);
            fprintf(fp, "%s,", overtimePay);
            fprintf(fp, "%s,", benefitPay);
            fprintf(fp, "%s,", statusReceived);
            fprintf(fp, "%s,", satisfactionLevel);
            fprintf(fp, "%s,", numberProject);
            fprintf(fp, "%s,", monthlyHours);
            fprintf(fp, "%s,", yearsAtCompany);
            fprintf(fp, "%s,", workAccident);
            fprintf(fp, "%s,", promotionGiveYears);
            fprintf(fp, "\n");

            fclose(fp);
        }

        remove("history.txt");
        rename("history_temp.txt", "history.txt");

        // int status = system("open -a Terminal \"`pwd`\""); // TO OPEN NEW TERMINAL
        // printf("New terminal is opened.\n");

        }

    return 0; 
} 


/*
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
    } else {

        while (feof(fp) || (!nameFound)) {
            fgets(buffer, 512, fp);
            empFileName = strtok(buffer, ",");
            empFileName = strtok(NULL, ","); // to get the second element in the line

            if (*(empFileName) == (*empManagerName)) {

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

            nameFound = true;
        }

        if (nameFound == false) {
            
        }

    }
            
	return NULL;
}
*/
