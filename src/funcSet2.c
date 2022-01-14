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
  int status;

  if (fileName[0] != NULL) {
    // Open File for Writing from STDOUT
    // w = if file does not exist create it, if it does exist rewrite file
    fp = freopen(fileName[0], "w", stdout);

    if (fp == NULL){
      perror("File Failed to Open\n");
      return -3;
    }

    status = execvp(command, arg);          // Execute in PATH=/bin Dir
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

  status = execvp(command, arg);          // Execute in PATH=/bin Dir
  fclose(fp);
  return status;
  } else {
    perror("File Name is Unreadable\n");
    return -4;
  }
}

int piping(char* command, char* arg1[], int pipefd[])
{
  char cmd[50];
  int status;
  close(pipefd[0]);                     // Close Read end of Pipe
  strcpy(cmd, "/bin/");
  strcat(cmd, command);
  dup2(pipefd[1], STDOUT_FILENO);       // Replace STDOUT with Write file desciptor of pipe
  close(pipefd[1]);                     // Close Pipe
  status = execvp(cmd, arg1);
  if (status != -1) {
    return 7;
  } else {
    return status;
  }

}
