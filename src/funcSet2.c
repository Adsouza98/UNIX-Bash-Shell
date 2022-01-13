/*
 * Andre D'Souza
 * #:0952594
 * Deadline: 02/02/22
 *
 * This file comprises the functions to complete
 * Set 2 Functions of Assignment 1
*/

// Standard Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Local Libraries
#include "FuncSet2.h"

void funcSet2Print()
{
  printf("Hello FuncSet2!\n");
}

int outRedirToFile(char* command, char* arg[], char* fileName[])
{
  FILE* fp;
  char cmd[50];
  int status;

  if (fileName != NULL) {
    // Open File for writing from stdout
    // w = if file does not exist create it, if it does exist rewrite file
    fp = freopen(fileName[0], "w", stdout);

    // Command is in PATH=/bin/
    strcpy(cmd, "/bin/");
    strcat(cmd, command);
    status = execvp(cmd, arg);          // Execute in PATH=/bin Dir
    fclose(fp);
    return status;
  } else {
    perror("File Failed to Open\n");
    return -1;
  }
}
