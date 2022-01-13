/*
 * Andre D'Souza
 * #:0952594
 * Deadline: 02/02/22
 *
 * This file comprises the functions to complete
 * Set 1 Functions of Assignment 1
*/

//Define Statements
//To Allow use of strtok(), without compiler warnings, taken from Man-Page
#define _POSIX_C_SOURCE 200809L

// Standard Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>                           // For Strings
#include <stdbool.h>                          // For Bool
#include <unistd.h>                           // For uid_t

// Local Libraries
#include "FuncSet1.h"


/*
 * [display_Shell desciption]
 * If Shell is started for the first time (on bootup)
 * function clears terminal display and prints Shell prompt for user
*/
void displayShell(uid_t uid, uid_t euid, char* userName)
{
  static bool bootup = true;
  if (bootup == true) { //On bootup Clear Terminal Window
    system("clear");
    bootup = false;
  }
  if (uid < 0 || uid!=euid) {          // Privalage Check
    printf("[%s@socs]$ ", userName); // Regular User
  } else {
    printf("[%s@socs]#", userName);  // Super User
  }
}

/*
 * [shell_input desciption]
 * @param   char cmd[], user command input string
 * @param   char *arg[], user command arguments input string array
 * #TODO: Desciption
 * @return  0, No Operators {<,>,&,|}
 * @return  5, Operator ">"
 * @return  -2, No User Input
*/
int shellInput(char cmd[], char *arg[], char *arg2[])
{
  char userInput[1024];
  int i = 0, j = 0, k = 0;
  char *userArray[50], *userArray2[50], *tmp;
  bool reDirecTo = false;

  // Read Single Line of User Input
  fgets(userInput, 1024, stdin);

  //No valid input, return for new user input
  if (strcmp(userInput, "\n") == 0) {return -2;}

  // Segments User Input into Command and Arugments, delimited by spaces and newline
  tmp = strtok(userInput, " \n");

  // Parse Line into Segmented Command and Arguments then store pointers in
  // temporary array userArray[]
  while (tmp != NULL) {

    // Command Whos Output is Redirected to a file
    if (strcmp(tmp, ">") == 0){
      printf("Found >\n");
      tmp = strtok(NULL, " \n");
      reDirecTo = true;
    }
    if (reDirecTo == true) {
      userArray2[k++] = strdup(tmp);
      tmp = strtok(NULL, " \n");
    }
    if (reDirecTo == false) {
      userArray[i++] = strdup(tmp);
      tmp = strtok(NULL, " \n");
    }

  }

  // First User Input is the Command
  strcpy(cmd, userArray[0]);

  // All Other User Inputs are Arguments
  for (j=0;j<i;j++) {
    arg[j] = userArray[j];
  }
  arg[i] = NULL; // Terminate the Argument Array with a NULL pointer

  // Operands Arguments
  if (reDirecTo == true) {
    for(j=0;j<k;j++) {
      arg2[j] = userArray2[j];
    }
    arg2[k] = NULL; // Terminate the Operand Array with a NULL pointer
    return 5;
  }
  arg2[0] = NULL;
  return 0;
}

void clear()
{
  system("clear");           // Clear Terminal Display
}
