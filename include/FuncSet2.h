#ifndef FuncSet2
#define FuncSet2

void funcSet2Print();
int outRedirToFile(char* command, char* arg[], char* fileName[]);
int inRedirFromFile(char* command, char* arg[], char* fileName[]);
int pipeIn(char* command, char* arg[], int pipefd[]);
int pipeOut(char* command, char* arg[], int pipefd[]);
#endif
