// Standard Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <unistd.h>
#include <sys/types.h>

//Local Libraries
#include "FuncSet1.h"
#include "FuncSet2.h"
#include "FuncSet3.h"

int main ()
{
  char cmd[50], command[50], *arguments[50];
  int j = 0;


  uid_t uid=getuid(), euid=geteuid(); // User Information Variables
  struct passwd *p;                   // User Infromation Struct

  //char *envp[] = {(char *) "PATH=/bin", 0}; //Environment Variables Commands /bin

  while(1) { //Repeat Forever
    j=0;
    //Display User Shell Prompt for Command
    display_Shell();
    //Read Input from Terminal
    shellInput(command, arguments);
    //Fork
      //Parent
        //Wait for Child
    //Execute Command

    //Exit Command
    printf("Command = %s\n", command);
    while (arguments[j] != NULL) {
      printf("Argument[%d] = %s\n", j, arguments[j]);
      j++;
    }
    if (strcmp(command, "clear") == 0) {
      clearScreen();
    }
    if (strcmp(command, "exit") == 0) {
      exit(0);
    }
  }

  return 0;
}
