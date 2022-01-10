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
