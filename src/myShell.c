/*
 * Andre D'Souza
 * #:0952594
 * Deadline: 02/02/22
 * Extension: 02/06/22
 *
 * This File comprises of the main.c infinite loop of the program,
 * and handels all the negotations with the functionSet#.c files
*/

// Global Variables
char myHOME[500];
char myHISTFILE[500];
char myUSER[50];

// Define Statements
// To Allow use of strtok(), without compiler warnings, taken from Man-Page
#define _POSIX_C_SOURCE 200809L

//Uncommnet to toggle ON debug print statements
// #define DEBUG

#ifdef DEBUG
# define DEBUG_PRINT(x) printf x
#else
# define DEBUG_PRINT(x) do {} while (0)
#endif

// Standard Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

//Local Libraries
#include "FuncSet1.h"
#include "FuncSet2.h"
#include "FuncSet3.h"

int main ()
{
  char cmdUsrLocal[500], command[500], *arguments[500], *operands[500];
  int i = 0, j = 0;
  int k = 0, l = 0;
  int index = 0;

  int status;                                     // Execve Return Status
  int operator;                                   // shellInput Return Status
  int pipefd[2];                                  // Pipe File Desciptors, pipefd[0] = Read End, pipefd[1] = Write End

  //pid_t parentID = getpid();                      // Parent Process ID
  pid_t pid;                                      // Child Process ID
  pid_t pidPipeOut;                               // Piped Process ID

  setEnvironment();

  while(1) { //Repeat Forever
    i=0;
    j=0;
    k=0;
    l=0;
    status = 0;

    //DEBUG_PRINT(("Debug Parent ID = %d\n", (int)parentID));
    // Display User Shell Prompt for Command
    displayShell();

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
      DEBUG_PRINT(("Child with pid = %d, Attempting to Execute Command = %s\n", (int)getpid(), command));

      if (operator == 5) {                        // '>'
        DEBUG_PRINT(("Attempting outRedirToFile\n"));
        status = outRedirToFile(command, arguments, operands);
      }
      else if (operator == 6) {                   // '<'
        DEBUG_PRINT(("Attempting inRedirFromFile\n"));
        status = inRedirFromFile(command, arguments, operands);

      } else if (operator == 7) {                 // '|'
        // Attempting Input Piping Command
        DEBUG_PRINT(("Attempting Input Piping Command\n"));
        status = pipeIn(command, arguments, pipefd);

      } else if (operator == -2) {                // No Valid Arguments or Operands
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

      //Command is in $PATH
      if (status == -1) {
        status = execvp(command, arguments);      // Execute in PATH=/bin Dir
      }

      // Command is an Executable File in Local Bin Dir
      if (command[0] == '.' && command[1] == '/') {
        DEBUG_PRINT(("Command started with slash\n"));
        //strcpy(cmdUsrLocal, "bin/");
        strcat(cmdUsrLocal, command);
        status = execvp(cmdUsrLocal, arguments);
      }
    }

    if (operator == 7) {
      // Attempting Output Piping Command
      pidPipeOut = fork();
      if (pidPipeOut < 0) {
        perror("pidPipeOut Failed\n");
        exit(-1);
      }
      if (pidPipeOut == 0) {
        status = pipeOut(operands[0], operands, pipefd);
      }
    }

    // Parent Process
    if (operator == 7) {
      // Close Pipe Ends in the Parent Process
      close(pipefd[0]);
      close(pipefd[1]);
      // Wait for Child Piping Processes to Finish
      waitpid(pid, NULL, 0);
      waitpid(pidPipeOut, NULL, 0);
    } else {
      wait(NULL);                                 // Parent Wait for Child
    }
    DEBUG_PRINT(("Parent Process pid = %d\n", (int)getpid()));


    if (status < 0 || pid == 0) {
      DEBUG_PRINT(("Process with pid = %d, execve Failed\n", (int)getpid()));
      exit(0);
    }

    // Clear Command
    if (strcmp(command, "clear") == 0) {
      clear();
    }
    // Change Directory Command
    else if (strcmp(command, "cd") == 0) {
      if (arguments[1] != NULL) {
        if (strcmp(arguments[1], "~") == 0) {
          chdir(myHOME);
        } else {
          chdir(arguments[1]);
        }
      }
    }
    // History Command
    else if (strcmp(command, "history") == 0) {
      if (arguments[1] != NULL && strcmp(arguments[1], "-c") == 0) {
        historyDelete();
      }
      else if (arguments[1] != NULL && (index = atoi(arguments[1])) != 0) {
        historyRead(index);
      } else {
        historyRead(0);
      }
    }
    // Export Command
    else if (strcmp(command, "export") == 0) {
      printf("myUSER=%s\n", myUSER);
      printf("myHOME=%s\n", myHOME);
      printf("myHISTFILE=%s\n", myHISTFILE);
    }
    // Exit Command
    else if (strcmp(command, "exit") == 0) {
      historyDelete();
      exit(0);
    }

    DEBUG_PRINT(("Command = %s\n", command));
    while (arguments[i] != NULL) {
      DEBUG_PRINT(("Argument[%d] = %s\n", i, arguments[i]));
      i++;
    }

    while (operands[j] != NULL) {
      DEBUG_PRINT(("Operands[%d] = %s\n", j, operands[j]));
      j++;
    }

  }

  return 0;
}
