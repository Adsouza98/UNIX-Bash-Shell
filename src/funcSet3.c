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

// Standard Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Local Libraries
#include "FuncSet3.h"

void funcSet3Print()
{
  printf("Hello FuncSet3!\n");
}

int historyWrite(char* userInput)
{
  FILE* fp;
  fp = fopen("history.txt", "a");
  commandCount++;

  if (fp == NULL) {
    perror("File Failed to Open\n");
    return -1;
  }
  //(space) number (2 spaces) command line
  fprintf(fp, " %d  %s", commandCount, userInput);
  fclose(fp);

  return 0;
}

int historyRead(int index)
{
  FILE* fp;
  char c;
  int count = 0;

  fp = fopen("history.txt", "r");

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
  if (remove("history.txt") == 0) {
    printf("The History File Deleted Successfully\n");
    commandCount = 0;
    return 0;
  } else {
    printf("The history File Was Not Deleted\n");
    return -1;
  }
  return 1;
}
