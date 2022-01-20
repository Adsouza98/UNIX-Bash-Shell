/*
 * Andre D'Souza
 * #:0952594
 * Deadline: 02/02/22
 *
 * This file comprises the functions to complete
 * Set 3 Functions of Assignment 1
*/

// Global Variable
int commandCount = 0;

// Shared Global Variables
extern char myHOME[500];
extern char myHISTFILE[500];
extern char myUSER[50];

// Define Statements
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

void funcSet3Print()
{
  printf("Hello FuncSet3!\n");
}

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
    putenv(myUSERenv);

    if (getcwd(myHOME, sizeof(myHOME)) == NULL) {
      perror("Error Getting Current Working Directory\n");
    } else {
      // Setting Environment Variable $myHOME
      strcat(myHOMEenv, myHOME);
      putenv(myHOMEenv);

      strcpy(myHISTFILE, myHOME);
      strcat(myHISTFILE, "/bin/.CIS3110_history");

      // Setting Environment Variable $myHISTFILE
      strcat(myHISTFILEenv, myHISTFILE);
      putenv(myHISTFILEenv);
    }
  } else {
    strcpy(myUSER, p->pw_name);
    // Seting Environment Variable $myUSER
    strcat(myUSERenv, myUSER);
    putenv(myUSERenv);

    strcpy(myHOME, p->pw_dir);
    // Setting Environment Variable $myHOME
    strcat(myHOMEenv, myHOME);
    putenv(myHOMEenv);

    strcpy(myHISTFILE, myHOME);
    strcat(myHISTFILE, "/.CIS3110_history");

    // Setting Environment Variable $myHISTFILE
    strcat(myHISTFILEenv, myHISTFILE);
    putenv(myHISTFILEenv);
  }
}
