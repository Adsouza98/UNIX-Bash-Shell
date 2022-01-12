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
#include <sys/wait.h>

//Local Libraries
#include "FuncSet1.h"
#include "FuncSet2.h"
#include "FuncSet3.h"

int main ()
{
  char cmd[50], command[50], *arguments[50];
  int j = 0;

  pid_t parentID = getpid();                // Parent Process ID
  pid_t pid;                                // Child Process ID

  uid_t uid=getuid(), euid=geteuid();       // User Information Variables
  char *userName;                           // User ID string
  struct passwd *p;                         // User Infromation Struct

  //User Name Check
  if (((p = getpwuid(uid)) == NULL) ) {
    fprintf(stderr, "%s", "User Name Error\n");
    userName = (char *) malloc(5);
    strcpy(userName, "user");
  } else {
    userName = strdup(p->pw_name);
  }

  char *envp[] = {(char *) "PATH=/bin", 0}; //Environment Variables Commands /bin

  while(1) { //Repeat Forever
    j=0;
    printf("Parent ID = %d\n", (int)parentID);
    // Display User Shell Prompt for Command
    displayShell(uid, euid, userName);

    // Read Input from Terminal
    shellInput(command, arguments);

    //Fork
    if (fork() != 0) {                      // Check if Parent has a Child Process
      printf("Waiting for Child\n");
      wait(NULL);                           // Wait for Chiild
    } else {
      printf("Attempting to Execute Command = %s\n", command);
      strcpy(cmd, "/bin/");                 // Command Base Directory
      strcat(cmd, command);                 // Concatenate command to directory string
      execve(cmd, arguments, envp);         // Execute Command
      printf("Finished Executing Command = %s\n", command);
    }

    // Clear Command
    if (strcmp(command, "clear") == 0) {
      clear();
    }
    // Exit Command
    else if (strcmp(command, "exit") == 0) {
      exit(0);
    }

    printf("Command = %s\n", command);
    while (arguments[j] != NULL) {
      printf("Argument[%d] = %s\n", j, arguments[j]);
      j++;
    }
  }

  free(userName);
  return 0;
}
