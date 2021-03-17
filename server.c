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
#include "server.h"

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
    int id;
    char name[100];
    char job_tital[100];
    float pay;
    float overtime_pay;
    float benefit;
    char status[2];
};

/* Function Declaration */
char* get_id(char* emp_name);
char* get_id_from_line(char* file_line);
int ensure_correct_line(char* fileline, char* );
void* search_salaries(void *value);
void server();

int ensure_correct_line(char* file_line, char* emp_id){
    /* Function: ensure_correct_line
    * ------------------------
    * 
    *  ENsure the id is matched at the beginning of the line.
    * 
    *  returns: bool value saying true or false if the line has emp_id in the beginning.
    */
    char* first_value;
    first_value = strtok(file_line, ",");

    //printf("%s\n", file_line);
}

void* search_salaries(void *value) {
    /* Function: search_salaries
    * ------------------------
    * 
    *  Gets the information needed from the salary sheet for a given employee id.
    * 
    *  returns: struct salaray_sheet
    */

    struct salary_sheet s;
    FILE *fp;
    char temp[512];
    char* correct_salary_line;
    int correct_line;

    fp = fopen("salaries.txt", "r");
    char *emp_id = (char *)value;

    while (fgets(temp, 512, fp) != NULL){
        if((strstr(temp, emp_id)) != NULL){
            //printf("%s", temp);
            correct_line = ensure_correct_line(temp, emp_id);
        }
    }
    //fp = fopen("salaries.txt", "r");

    /* Loop through the file looking for the line containing the name */
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
/* Declare variables */
char* emp_id;

char emp_name[20] = "Benjamin Tai";
emp_id = get_id(emp_name);
//printf("%s  ", emp_id);

pthread_t thread_id;
pthread_create(&thread_id, NULL, search_salaries, (void*)emp_id);
pthread_join(thread_id, NULL);

printf("Server ran.\n");



}