#include <stdio.h>
#include <unistd.h>// for fork
#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <stdlib.h>


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
  char ch, temp;
  // Open file fo write only
  fd = open(myfifo, O_WRONLY);

  printf("click enter to continue\n");
  while(1){
      scanf("%c",&temp); // temp statement to clear buffer
      // Take user UserInput and write to file
      printf("Enter Employee Name: ");
      scanf("%[^\n]", userPtr->employeeName);

      printf("Enter Job Title: ");
      scanf("%c",&temp); // temp statement to clear buffer
      scanf("%[^\n]", userPtr->jobTitle);

      printf("Enter Status: ");
      scanf("%c",&temp); // temp statement to clear buffer
      scanf("%[^\n]", userPtr->status);

      char *space = ",";   
      char *arr = userPtr->employeeName;
      char *arr1 = userPtr->jobTitle;
      char *arr2 = userPtr->status;
     
      // Concanating 3 strings together
      unsigned int const sz1  = strlen(arr);
      unsigned int const sz2  = strlen(arr1);
      unsigned int const sz3  = strlen(arr2);
      unsigned int const szSpace  = strlen(space);

      char *concat = (char*)malloc(sz1+sz2+sz3+3);

      memcpy( concat, arr  , sz1 );
      memcpy( concat+sz1, space , szSpace);
      memcpy( concat+sz1+szSpace, arr1 , sz2 );
      memcpy( concat+sz1+szSpace+sz2, space , szSpace);
      memcpy( concat+sz1+szSpace+sz2+szSpace, arr2 , sz3 );
     memcpy( concat+sz1+szSpace+sz2+szSpace+sz3, space , szSpace);
    
    concat[sz1+ szSpace + sz2 + szSpace + sz3 +szSpace] = '\0';

    write(fd, concat, strlen(concat));

    //printf("%s\n", concat);

      printf("Do you want to continue? y/n: ");
      scanf("%s", &ch);

      if(ch == 'y'){
        continue;
      }
      // End program if user input is 'n'
      else if(ch == 'n'){
        close(fd);
        return 0;
      }
  }
  return 0;
}