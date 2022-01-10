/*
 * Andre D'Souza
 * #:0952594
 * Deadline: 02/02/22
 *
 * This file comprises the functions to complete
 * Set 1 Functions of Assignment 1
*/

// Standard Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

// Local Libraries
#include "FuncSet1.h"

/*
 * [display_Shell desciption]
 * If Shell is started for the first time (on bootup)
 * function clears terminal display and prints Shell prompt for user
*/
void display_Shell()
{
  static bool bootup = true;
  if (bootup == true) { //On bootup Clear Terminal Window
    //const char* CLEAN_TERMINAL = " \e[1;1H\e[2J";
    /*
     * \e = escape
     * [1;1H = Coordinates to Upper Left Corner of the Terminal
     * [2J = Create a Screen for the Shell in the Terminal Window
    */
    //write(STDOUT_FILENO, CLEAN_TERMINAL, 12);
    system("clear");
    bootup = false;
  }
  printf("<adsouz03Shell>"); // Display Shell Prompt
}

/*
 * [shell_input desciption]
 * @param   char cmd[], user command input string
 * @param   char *arg[], user command arguments input string array
 * User enters a
*/
void shell_input(char cmd[], char *arg[])
{
  char userInput[1024];
  int index = 0, i = 0, j = 0, c;
  char *userArray[50], *tmp;

  // Read Single Line of User Input
  do {
    c = fgetc(stdin);
    userInput[index++] = (char)c;
  } while( c != '\n'); // Exit loop when user inputs return ("enter")

  if (index == 1 ) {return;} //No valid input
  tmp = strtok(userInput, " \n");

  // Parse Line into Segmented Command and Arguments
  while (tmp != NULL) {
    userArray[i++] = strdup(tmp);
    tmp = strtok(NULL, " \n");
  }

  // First User Input is the Command
  strcpy(cmd, userArray[0]);

  // All Other User Inputs are Arguments
  for (j=0;j<i;j++) {
    arg[j] = userArray[j];
  }
  arg[i] = NULL; //Terminate the Argument Array with a NULL pointer
}
