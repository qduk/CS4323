/*
 * Author Name: Adam Byczkowski
 * Email: abyczko@ostatemail.okstate.edu
 * Date: 03/14/2021
 * Program Description: This program implements the server role of the mini group project
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h> 
#include "server.h"

#define PORT 8080 

struct employee {
    int id;
    char name[100];
    char job_tital[100];
    float pay;
    float overtime_pay;
    float benefit;
    char status[2];
    int satisfaction_level;
    int num_project;
    int average_hours_monthly;
    int time_at_company_years;
    bool work_accident;
    bool promotion_five_years;
};

struct salary_sheet {
    char id[100];
    char job_title[100];
    char pay[100];
    char overtime_pay[100];
    char benefit[100];
    char status[100];
};

struct satisfaction_sheet {
    char id[5];
    char satisfaction_level[5];
    char number_project[5];
    char monthly_hours[5];
    char years_at_company[5];
    char work_accident[5];
    char promotion_give_years[5];
};

struct salary_input {
    char id[10];
    struct salary_sheet *s;
};

struct satisfaction_input {
    char id[10];
    struct satisfaction_sheet *s;
};

/* Function Declaration */
char* get_id(char* emp_name);
char* get_id_from_line(char* file_line);
int ensure_correct_line(char* fileline, char* );
void* search_salaries(void *_args);
void server();

int ensure_correct_line(char* file_line, char* emp_id){
    /* Function: ensure_correct_line
    * ------------------------
    * 
    *  Ensure the id is matched at the beginning of the line.
    * 
    *  returns: bool value saying true or false if the line has emp_id in the beginning.
    */
    char* first_value;
    char copy_file_line[512];
    int does_match; 
    strcpy(copy_file_line, file_line);
    first_value = strtok(copy_file_line, ",");

    if (strcmp(first_value, emp_id) == 0){
        return 0;
    };
    return 1;
}

void* search_salaries(void *_args) {
    /* Function: search_salaries
    * ------------------------
    * 
    *  Gets the information needed from the salary sheet for a given employee id.
    * 
    *  returns: void
    */
    FILE *fp;
    char temp[512];
    char* correct_salary_line;
    int correct_line;
    struct salary_input *args = (struct salary_input *) _args;

    fp = fopen("salaries.txt", "r");
    char *emp_id = args->id;

    while (fgets(temp, 512, fp) != NULL){
        if((strstr(temp, emp_id)) != NULL){
            //printf("%s", temp);
            correct_line = ensure_correct_line(temp, emp_id);
            //printf("%s", temp);
            if (correct_line == 0){
                break;
            }
        }
    }
    strcpy(args->s->id, strtok(temp, ","));
    strcpy(args->s->job_title, strtok(NULL, ","));
    strcpy(args->s->pay, strtok(NULL, ","));
    strcpy(args->s->overtime_pay, strtok(NULL, ","));
    strcpy(args->s->benefit, strtok(NULL, ","));
    strcpy(args->s->status, strtok(NULL, ","));

    free(args);
}

void* search_satisfaction(void *_args) {
    /* Function: search_satisfaction
    * ------------------------
    * 
    *  Gets the information needed from the satisfaction sheet for a given employee id.
    * 
    *  returns: void
    */
    FILE *fp;
    char temp[512];
    char* correct_satisfaction_line;
    int correct_line;
    struct satisfaction_input *args = (struct satisfaction_input *) _args;

    fp = fopen("satisfaction.txt", "r");
    char *emp_id = args->id;

    while (fgets(temp, 512, fp) != NULL){
        if((strstr(temp, emp_id)) != NULL){
            //printf("%s", temp);
            correct_line = ensure_correct_line(temp, emp_id);
            //printf("%s", temp);
            if (correct_line == 0){
                break;
            }
        }
    }
    //printf("%s", temp);
    strcpy(args->s->id, strtok(temp, ","));
    strcpy(args->s->satisfaction_level, strtok(NULL, ","));
    strcpy(args->s->number_project, strtok(NULL, ","));
    strcpy(args->s->monthly_hours, strtok(NULL, ","));
    strcpy(args->s->years_at_company, strtok(NULL, ","));
    strcpy(args->s->work_accident, strtok(NULL, ","));
    strcpy(args->s->promotion_give_years, strtok(NULL, ","));

    free(args);

}

char* get_id_from_line(char* file_line){
    /* Function: get_id_from_line
    * ------------------------
    * 
    *  Gets id for employee from the line found in the text file. 
    * 
    *  returns: int
    */
    char *id;
    id = strtok(file_line, ",");
    return id;

}

char* get_id(char* emp_name){
    /* Function: get_id
    * ------------------------
    * 
    *  Gets id for employee from provided employee name
    * 
    *  returns: int
    */
   char temp[512];
   char* name_id;
   FILE *fp;
   fp = fopen("id_name.txt", "r");

   /* Loop through the file looking for the line containing the name */
   while (fgets(temp, 512, fp) != NULL){
       if((strstr(temp, emp_name)) != NULL){
           name_id = get_id_from_line(temp);
           break;
       }
   }
   return name_id;
}

void server() {
// Declare socket variables
int server_fd, new_socket, valread; 
struct sockaddr_in address; 
int opt = 1; 
int addrlen = sizeof(address); 
char buffer[100]; 

// Creating socket file descriptor 
if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) { 
    perror("socket failed"); 
    exit(EXIT_FAILURE); 
} 
    
// Forcefully attaching socket to the port 8080 
if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt))) { 
    perror("setsockopt"); 
    exit(EXIT_FAILURE); 
} 

address.sin_family = AF_INET; 
address.sin_addr.s_addr = INADDR_ANY; 
address.sin_port = htons(PORT); 

// Forcefully attaching socket to the port 8080 
if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) { 
    perror("bind failed"); 
    exit(EXIT_FAILURE); 
} 

if (listen(server_fd, 3) < 0) { 
    perror("listen"); 
    exit(EXIT_FAILURE); 
} 

if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) { 
    perror("accept"); 
    exit(EXIT_FAILURE); 
}

/* Declare variables */
char* emp_id;
struct salary_sheet *ss = malloc(sizeof (struct salary_sheet));
struct salary_input *si = malloc(sizeof (struct salary_input));

struct satisfaction_sheet *sat_sheet = malloc(sizeof (struct satisfaction_sheet));
struct satisfaction_input *sat_in = malloc(sizeof (struct satisfaction_input));

char emp_name[20] = "Benjamin Tai";
while ( (valread = read(new_socket, buffer, 100)) > 0) { 
    printf("Name received from the client: %s\n", buffer);

    //Get ID from name.
    emp_id = get_id(buffer);

    //Set up structs to pass to threads
    strcpy(si->id, emp_id);
    si->s = ss;
    strcpy(sat_in->id, emp_id);
    sat_in->s = sat_sheet;

    //Create salary sheet thread
    pthread_t sal_thread_id;
    pthread_create(&sal_thread_id, NULL, search_salaries, si);
    pthread_join(sal_thread_id, NULL);

    //Create satisfaction thread
    pthread_t sat_thread_id;
    pthread_create(&sat_thread_id, NULL, search_satisfaction, sat_in);
    pthread_join(sat_thread_id, NULL);

    send(new_socket, si->s->job_title, 100, 0);
    send(new_socket, si->s->pay, 100, 0);
    send(new_socket, si->s->overtime_pay, 100, 0);
    send(new_socket, si->s->benefit, 100, 0);
    send(new_socket, si->s->status, 100, 0);
    //printf("New name sent back to the client.\n");

    memset(buffer, 0, 100); 
}
}