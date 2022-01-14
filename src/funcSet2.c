/*
 * Andre D'Souza
 * #:0952594
 * Deadline: 02/02/22
 *
 * This file comprises the functions to complete
 * Set 2 Functions of Assignment 1
*/

//Define Statements
//To Allow use of strtok(), without compiler warnings, taken from Man-Page
#define _POSIX_C_SOURCE 200809L

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

  if (fileName[0] != NULL) {
    // Open File for Writing from STDOUT
    // w = if file does not exist create it, if it does exist rewrite file
    fp = freopen(fileName[0], "w", stdout);

    if (fp == NULL){
      perror("File Failed to Open\n");
      return -3;
    }

    // Command is in PATH=/bin/
    strcpy(cmd, "/bin/");
    strcat(cmd, command);
    status = execvp(cmd, arg);          // Execute in PATH=/bin Dir
    fclose(fp);
    return status;
  } else {
    perror("File Name is Unreadable\n");
    return -4;
  }
}

int inRedirFromFile(char* command, char* arg[], char* fileName[])
{
  FILE* fp;
  char cmd[50];
  int status, i = -1;

  if (fileName[0] != NULL) {
    // Open File for Reading from STDIN
    // r = Opens file for reading. The file must exist
    fp = fopen(fileName[0], "r");

    if (fp == NULL){
      perror("File Failed to Open\n");
      return -3;
    }

    do {
      i++;

      if (arg[i] == NULL) {
        arg[i] = strdup(fileName[0]);
        i++;
        arg[i] = NULL;
      }

    } while (arg[i] != NULL);

    strcpy(cmd, "/bin/");
    strcat(cmd, command);
    status = execvp(cmd, arg);          // Execute in PATH=/bin Dir
    fclose(fp);
    return status;
  } else {
    perror("File Name is Unreadable\n");
    return -4;
  }
}
