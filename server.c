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
int get_id(char* emp_name);
int get_id_from_line(char* file_line);
struct salary_sheet search_salaries(int emp_id);

struct salary_sheet search_salaries(int emp_id) {
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
   char *string_emp_id;

   string_emp_id = itoa(emp_id);

   fp = fopen("salaries.txt", "r");

    /* Loop through the file looking for the line containing the name */
   while (fgets(temp, 512, fp) != NULL){
       if((strstr(temp, string_emp_id)) != NULL){
           printf("%s", temp);
       }
   }
}

int get_id_from_line(char* file_line){
    /* Function: get_id_from_line
    * ------------------------
    * 
    *  Gets id for employee from the line found in the text file. 
    * 
    *  returns: int
    */
    char *string_id;
    int id;
    string_id = strtok(file_line, ",");
    id = atoi(string_id);
    return id;

}

int get_id(char* emp_name){
    /* Function: get_id
    * ------------------------
    * 
    *  Gets id for employee from provided employee name
    * 
    *  returns: int
    */
   char temp[512];
   int name_id;
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

int main(int argc, char *argv[]) {
/* Declare variables */
int emp_id;

char emp_name[20] = "Benjamin Tai";
emp_id = get_id(emp_name);
//printf("%d", emp_id);

pthread_t thread_id;
pthread_create(&thread_id, NULL, search_salaries, NULL);
pthread_join(thread_id, NULL);

}