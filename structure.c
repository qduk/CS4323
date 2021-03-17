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
  char option = 'y';
  char ch;
  char *arr;

  int fd;
  // FIFO file path
  char * myfifo = "myfifo.txt";
  // Creating file FIFO
  mkfifo(myfifo, 0644);



  if (option == 'y'){
    do{
      printf("Enter Employee Name: ");
      scanf("%s", userPtr->employeeName);

      printf("Enter Job Title: ");
      scanf("%s", userPtr->jobTitle);

      printf("Enter Status: ");
      scanf("%s", userPtr->status);

      arr = userPtr->employeeName;
      write(fd, arr, strlen(arr)+1);

      printf("Do you want to continue? y/n: ");
      scanf("%s", &ch);
    }
    while(ch == 'y');
  }
    fd = open(myfifo, O_WRONLY);
    close(fd);

    //fd = open(myfifo, O_RDONLY);
    //read(fd, arr1, sizeof(arr1) != strlen(arr1));

    //printf("User2: %s\n", arr1);
    //close(fd);

  return 0;
}