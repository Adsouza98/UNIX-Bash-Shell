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
  char cmd[50], cmdUsrLocal[50], command[50], *arguments[50], *operands[50];
  int i = 0, j = 0;
  int k = 0, l = 0;

  int status;                                     // Execve Return Status
  int operator;                                   // shellInput Return Status
  int pipefd[2];                                  /* Pipe File Desciptors
                                                   * pipefd[0] = Read End
                                                   * pipefd[1] = Write End
                                                   */

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

  while(1) { //Repeat Forever
    i=0;
    j=0;
    k=0;
    l=0;
    status = 0;
    printf("Parent ID = %d\n", (int)parentID);
    // Display User Shell Prompt for Command
    displayShell(uid, euid, userName);

    // Read Input from Terminal
    operator = shellInput(command, arguments, operands);

    //Piping
    if (operator == 7) {
      if (pipe(pipefd) == -1) {
        perror("Pipe Failed\n");
      }
    }

    //Forking
    // Fork Failed
    if ((pid = fork()) < 0) {
      perror("Fork Failed\n");
      wait(NULL);                                 // Wait for Potential Chiild
      exit(-1);
    }
    // Child Process
    else if (pid == 0) {
      printf("Child with pid = %d, Attempting to Execute Command = %s\n", (int)getpid(), command);

      if (operator == 5) {                        // '>'
        printf("Attempting outRedirToFile\n");
        status = outRedirToFile(command, arguments, operands);
      }
      else if (operator == 6) {                   // '<'
        printf("Attempting inRedirFromFile\n");
        status = inRedirFromFile(command, arguments, operands);

      } else if (operator == 7) {
        printf("Attempting Piping Command\n");
        status = piping(command, arguments, pipefd);
        status = 7;

      } else if (operator == -2) {                  // No Valid Arguments or Operands
        strcpy(command, "");
        while (arguments[k] != NULL) {
          free(arguments[k]);
          k++;
        }
        while (operands[l] != NULL) {
          free(operands[l]);
          l++;
        }
      } else {
        status = -1;
      }

      //Command is in PATH=/bin/
      if (status == -1) {
        status = execvp(command, arguments);          // Execute in PATH=/bin Dir
      }


      // Command is in PATH=/usr/bin/
      if (status == -1) {
        status = execvp(command, arguments);
      }
      // Command is an Executable File in Local Bin Dir
      if (command[0] == '.' && command[1] == '/') {
        printf("Command started with slash\n");
        strcpy(cmdUsrLocal, "bin/");
        strcat(cmdUsrLocal, command);
        status = execvp(cmdUsrLocal, arguments);
      }
    }
    // Parent Process
      printf("Parent Process pid = %d\n", (int)getpid());
      wait(NULL);                                     // Parent Wait for Child

    if (status < 0 || pid == 0) {
      printf("Process with pid = %d, execve Failed\n", (int)getpid());
      exit(0);
    }

    // Continue Piping
    if (status == 7) {
      printf("Continue Piping\n");
      close(pipefd[1]);                               // Close Write end of Pipe
      dup2(pipefd[0], STDIN_FILENO);                  // Replace STDIN with Read end of Pipe
      strcpy(cmd, "bin/");
      strcat(cmd, operands[0]);
      dup2(pipefd[0], STDIN_FILENO);
      close(pipefd[0]);
      execvp(cmd, operands);
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
    while (arguments[i] != NULL) {
      printf("Argument[%d] = %s\n", i, arguments[i]);
      i++;
    }

    while (operands[j] != NULL) {
      printf("Operands[%d] = %s\n", j, operands[j]);
      j++;
    }

  }

  free(userName);
  return 0;
}
