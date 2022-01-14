#ifndef FuncSet2
#define FuncSet2

void funcSet2Print();
int outRedirToFile(char* command, char* arg[], char* fileName[]);
int inRedirFromFile(char* command, char* arg[], char* fileName[]);
int piping(char* command, char* arg1[], int pipefd[]);

#endif
