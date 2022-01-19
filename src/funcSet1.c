/*
 * Andre D'Souza
 * #:0952594
 * Deadline: 02/02/22
 *
 * This file comprises the functions to complete
 * Set 1 Functions of Assignment 1
*/

// Shared Global Variables
extern char myHOME[500];
extern char myHISTFILE[500];
extern char myUSER[50];

// Define Statements
// To Allow use of strtok(), without compiler warnings, taken from Man-Page
#define _POSIX_C_SOURCE 200809L

// Standard Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>                           // For Strings
#include <stdbool.h>                          // For Bool
#include <unistd.h>                           // For uid_t
#include <errno.h>

// Local Libraries
#include "FuncSet1.h"
#include "FuncSet3.h"


/*
 * [display_Shell desciption]
 * If Shell is started for the first time (on bootup)
 * function clears terminal display and prints Shell prompt for user
*/
void displayShell()
{
  static bool bootup = true;
  char cwd[500];

  if (bootup == true) { //On bootup Clear Terminal Window
    system("clear");
    bootup = false;
  }
  printf("[%s@socs]:%s> ", myUSER, getcwd(cwd, sizeof(cwd)));
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
  char userInput[500];
  int i = 0, j = 0, k = 0;
  char *userArray[500], *userArray2[500], *tmp;
  bool reDirecTo = false;
  bool reDirecFrom = false;
  bool piping = false;

  // Read Single Line of User Input
  fgets(userInput, 500, stdin);

  historyWrite(userInput);

  //No valid input, return for new user input
  if (strcmp(userInput, "\n") == 0) {return -2;}

  // Segments User Input into Command and Arugments, delimited by spaces and newline
  tmp = strtok(userInput, " \n");

  // Parse Line into Segmented Command and Arguments then store pointers in
  // temporary array userArray[]
  while (tmp != NULL) {

    // Command Whose Output is Redirected To a file
    if (strcmp(tmp, ">") == 0){
      printf("Found >\n");
      tmp = strtok(NULL, " \n");

      if (tmp == NULL) {
        perror("No Arguments or Operands");
        return -2;
      }
      reDirecTo = true;
    }

    // Command Whose Input is Redirected From a File
    if (strcmp(tmp, "<") == 0) {
      printf("Found <\n");
      tmp = strtok(NULL, " \n");

      if (tmp == NULL) {
        perror("No Arguments or Operands");
        return -2;
      }
      reDirecFrom = true;
    }
    // Command Whos Output is Piped into the Input of Another Command
    if (strcmp(tmp, "|") == 0) {
      printf("Found |\n");
      tmp = strtok(NULL, " \n");

      if (tmp == NULL) {
        perror("No Arguments or Operands");
        return -2;
      }
      piping = true;
    }

    if (reDirecTo == true || reDirecFrom == true || piping == true) {
      printf("tmp = %s\n", tmp);
      userArray2[k++] = strdup(tmp);
      tmp = strtok(NULL, " \n");
    } else {
      // Normal Input
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
  if (reDirecTo == true || reDirecFrom == true || piping == true) {
    for(j=0;j<k;j++) {
      arg2[j] = userArray2[j];
    }
    arg2[k] = NULL; // Terminate the Operand Array with a NULL pointer
    if (reDirecTo == true) {
      printf("Returing 5 = '>'\n");
      return 5;
    }
    if (reDirecFrom == true) {
      printf("Returning 6 = '<'\n");
      return 6;
    }
    if (piping == true) {
      printf("Return 7 = '|'\n");
      return 7;
    }
  }
  arg2[0] = NULL;
  return 0;
}

void clear()
{
  system("clear");           // Clear Terminal Display
}
