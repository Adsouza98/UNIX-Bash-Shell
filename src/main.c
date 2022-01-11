//Define Statements
//To Allow use of strtok(), without compiler warnings, taken from Man-Page
#define _POSIX_C_SOURCE 200809L

// Standard Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <unistd.h>
#include <sys/types.h>

//Local Libraries
#include "FuncSet1.h"
#include "FuncSet2.h"
#include "FuncSet3.h"

int main ()
{
  char cmd[50], command[50], *arguments[50];
  int j = 0;


  uid_t uid=getuid(), euid=geteuid(); // User Information Variables
  char *userName;                     // User ID string
  struct passwd *p;                   // User Infromation Struct

  //User Name Check
  if (((p = getpwuid(uid)) == NULL) ) {
    fprintf(stderr, "%s", "User Name Error\n");
    userName = (char *) malloc(5);
    strcpy(userName, "user");
  } else {
    userName = strdup(p->pw_name);
  }
  
  //char *envp[] = {(char *) "PATH=/bin", 0}; //Environment Variables Commands /bin

  while(1) { //Repeat Forever
    j=0;

    //Display User Shell Prompt for Command
    displayShell(uid, euid, userName);
    //Read Input from Terminal
    shellInput(command, arguments);
    //Fork
      //Parent
        //Wait for Child
    //Execute Command

    //Exit Command
    printf("Command = %s\n", command);
    while (arguments[j] != NULL) {
      printf("Argument[%d] = %s\n", j, arguments[j]);
      j++;
    }
    if (strcmp(command, "clear") == 0) {
      clear();
    }
    if (strcmp(command, "exit") == 0) {
      exit(0);
    }
  }

  free(userName);
  return 0;
}
