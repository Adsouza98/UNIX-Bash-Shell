/*
 * Andre D'Souza
 * #:0952594
 * Deadline: 02/02/22
 *
 * This file comprises the functions to complete
 * Set 2 Functions of Assignment 1
*/

// Define Statements
// To Allow use of strtok(), without compiler warnings, taken from Man-Page
#define _POSIX_C_SOURCE 200809L

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
#include <errno.h>

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
      perror("File Failed to Open");
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

int pipeIn(char* command, char* arg[], int pipefd[])
{
  close(pipefd[0]);                     // Close Read end of Pipe, Not in use Right now
  dup2(pipefd[1], STDOUT_FILENO);       // Replace STDOUT File Number with Write file desciptor of pipe
  close(pipefd[1]);                     // Close Write end of Pipe
  return execvp(command, arg);          // Execute Command Into Pipe
}

int pipeOut(char* command, char* arg[], int pipefd[])
{
  close(pipefd[1]);                     // Close Write end of Pipe, Not in use Right now
  dup2(pipefd[0], STDIN_FILENO);        // Replace STDIN File Number with Read File desciptor of pipe
  close(pipefd[0]);                     // Close Read end of Pipe
  return execvp(command, arg);
}
