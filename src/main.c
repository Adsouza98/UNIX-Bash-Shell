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
  char cmdBin[50], cmdUsrBin[50], command[50], *arguments[50];
  int j = 0;

  int status;                                     // Execve Return Status

  pid_t parentID = getpid();                      // Parent Process ID
  pid_t pid;                                      // Child Process ID

  uid_t uid=getuid(), euid=geteuid();             // User Information Variables
  char *userName;                                 // User ID string
  struct passwd *p;                               // User Infromation Struct

  //User Name Check
  if (((p = getpwuid(uid)) == NULL) ) {
    fprintf(stderr, "%s", "User Name Error\n");
    userName = (char *) malloc(5);
    strcpy(userName, "user");
  } else {
    userName = strdup(p->pw_name);
  }

  //char *envp[] = {(char *) "PATH=/bin", 0};     // Environment Variables Commands /bin/
  char *envp[] = {(char *) "PATH=/usr/bin", 0};   // Environment Variables Commands /usr/bin/

  while(1) { //Repeat Forever
    j=0;
    status = 0;
    printf("Parent ID = %d\n", (int)parentID);
    // Display User Shell Prompt for Command
    displayShell(uid, euid, userName);

    // Read Input from Terminal
    shellInput(command, arguments);

    //Forking

    // Fork Failed
    if ((pid = fork()) < 0) {
      perror("Fork Failed\n");
      wait(NULL);                                 // Wait for Potential Chiild
      return(-1);
    }
    // Child Process
    else if (pid == 0) {
      printf("Child with pid = %d, Attempting to Execute Command = %s\n", (int)getpid(), command);

      // Command is in PATH=/bin/
      strcpy(cmdBin, "/bin/");
      strcat(cmdBin, command);
      status = execvp(cmdBin, arguments);          // Execute in PATH=/bin Dir
      
      // Command is in PATH=/usr/bin/
      if (status == -1) {
        printf("Test\n");
        strcpy(cmdUsrBin, "/usr/bin/");              // Command Base Directory
        strcat(cmdUsrBin, command);                  // Concatenate command to directory string
        status = execve(cmdUsrBin, arguments, envp); // Execute Command
      }

    }
    //Parent Process
      printf("Parent Process pid = %d\n", (int)getpid());
      wait(NULL);

    if (status == -1) {
      printf("Process with pid = %d, execve Failed\n", (int)getpid());
      exit(0);
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
