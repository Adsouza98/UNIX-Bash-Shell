#ifndef FuncSet1
#define FuncSet1

void displayShell(uid_t uid, uid_t euid, char* userName);
int shellInput(char cmd[], char *arg[], char *arg2[]);
void clear();
#endif
