#include <stdio.h>
#include <unistd.h>// for fork
#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 


/**********Structure**********/
struct User{
  char employeeName[50];
  char jobTitle[50];
  char status[50];
};

/**********UserInput**********/
int structure(){

  struct User *userPtr, user;
  userPtr = &user;
  int fd;
  // file path
  char * myfifo = "myfifo.txt";
  // Creating the file
  mkfifo(myfifo, 0644);
  char arr, arr1, arr2;
  char ch;
  // Open file fo write only
  fd = open(myfifo, O_WRONLY);

  while(1){

      // Take user UserInput and write to file
      printf("Enter Employee Name: ");
      scanf("\n%s", userPtr->employeeName);

      printf("Enter Job Title: ");
      scanf("\n%s", userPtr->jobTitle);

      printf("Enter Status: ");
      scanf("\n%s", userPtr->status);
      
      char *arr = userPtr->employeeName;
      write(fd, arr, strlen(arr)+1);

      char *arr1 = userPtr->jobTitle;
      write(fd, arr1, strlen(arr1)+1);

      char *arr2 = userPtr->status;
      write(fd, arr2, strlen(arr2)+1);

      printf("Do you want to continue? y/n: ");
      scanf("%s", &ch);

      if(ch == 'y'){
        continue;
      }
      // End program if user input is 'n'
      else if(ch == 'n'){
        return 0;
      }
  }
  return 0;
}