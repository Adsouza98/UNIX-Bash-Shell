/*
 * Andre D'Souza
 * #:0952594
 * Deadline: 02/02/22
 * Extension: 02/06/22
 * This file comprises the functions to complete
 * Set 3 Functions of Assignment 1
*/

// Global Variable
int commandCount = 0;

// Shared Global Variables
extern char myHOME[500];
extern char myHISTFILE[500];
extern char myUSER[50];

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
#include <pwd.h>
#include <sys/types.h>

// Local Libraries
#include "FuncSet3.h"
#include "FuncSet1.h"


/*
 * @Desciption:
 * Opens file or creates a file if it does not exist in the user's home directory
 * called .CIS3110_history
 * Appends the user inputted command line to the end of the file with the format
 * (space) number (2 spaces) command line
 *
 * @param    char *userInput, user command input string
 *
 * @return  -1, File failed to open
 * @return   0, Successfully Wrote to file
*/
int historyWrite(char* userInput)
{
  FILE* fp;
  fp = fopen(myHISTFILE, "a");

  if (fp == NULL) {
    perror("File Failed to Open\n");
    return -1;
  }

  if (strcmp(userInput, "\n") != 0) {
    commandCount++;
    //(space) number (2 spaces) command line
    fprintf(fp, " %d  %s", commandCount, userInput);
    fclose(fp);
  }
  return 0;
}

/*
 * @Desciption:
 * Opens .CIS_3110_history file for reading in the user's home directory
 * If no index value is passed in it prints the entire CIS_3110_history file to STDOUT
 * If index is specified it only prints that many lines of the CIS3110_history file to STDOUT
 *
 *
 * @param    int index, number of commands to print
 *
 * @return  -1, File failed to open
 * @return   0, Successfully Wrote to file
*/
int historyRead(int index)
{
  FILE* fp;
  char c;
  int count = 0;

  fp = fopen(myHISTFILE, "r");

  if (fp == NULL) {
    perror("File Failed to Open\n");
    return -1;
  }

  if (index != 0 ) {                    // History n ;Where n is number of commands to print
    c = fgetc(fp);
    while(c != EOF && count != index) {
      printf("%c", c);
      c = fgetc(fp);
      if (c == '\n') {
        count++;
      }
    }
    printf("\n");
  } else {                              // Print all History
    c = fgetc(fp);
    while (c != EOF) {
      printf("%c", c);
      c = fgetc(fp);
    }
  }

  fclose(fp);
  return 0;
}

/*
 * @Desciption:
 * Deletes .CIS3110_history file and sets the command count to 0.
 *
 *
 * @param    int index, number of commands to print
 *
 * @return  0, File Successfully Deleted
 * @return -1, File Failed to be Deleted
 * @return  1, Unexpected Output
*/
int historyDelete()
{
  if (remove(myHISTFILE) == 0) {
    DEBUG_PRINT(("The History File Deleted Successfully\n"));
    commandCount = 0;
    return 0;
  } else {
    DEBUG_PRINT(("The history File Was Not Deleted\n"));
    return -1;
  }
  return 1;
}

/*
 * @Desciption:
 * Sets Global variables to PATH export format.
 * Gets uid of current parent process and finds User's passwd struct *p which
 * stores the user's NAME, and HOMEDIRECTORY. If the program fails to find the
 * user's passwd struct it sets the default username myUSER = "user"
 * and homedirectory myHOME = the current working directory.
 *
*/
void setEnvironment()
{
  char myHISTFILEenv[510] = "myHISTFILE=";
  char myUSERenv[60] = "myUSER=";
  char myHOMEenv[510] = "myHOME=";

  uid_t uid = getuid();
  //uid_t euid = geteuid();
  struct passwd *p;

  // Passwd Struct Check
  if (((p = getpwuid(uid)) == NULL)) {
    perror("getpwuid error\n");

    strcpy(myUSER, "user");

    // Setting Environment Variable $myUSER
    strcat(myUSERenv, myUSER);

    if (getcwd(myHOME, sizeof(myHOME)) == NULL) {
      perror("Error Getting Current Working Directory\n");
    } else {
      // Setting Environment Variable $myHOME
      strcat(myHOMEenv, myHOME);

      strcpy(myHISTFILE, myHOME);
      strcat(myHISTFILE, "/bin/.CIS3110_history");

      // Setting Environment Variable $myHISTFILE
      strcat(myHISTFILEenv, myHISTFILE);
    }
  } else {
    strcpy(myUSER, p->pw_name);
    // Seting Environment Variable $myUSER
    strcat(myUSERenv, myUSER);

    strcpy(myHOME, p->pw_dir);
    // Setting Environment Variable $myHOME
    strcat(myHOMEenv, myHOME);

    strcpy(myHISTFILE, myHOME);
    strcat(myHISTFILE, "/.CIS3110_history");

    // Setting Environment Variable $myHISTFILE
    strcat(myHISTFILEenv, myHISTFILE);
  }
}
