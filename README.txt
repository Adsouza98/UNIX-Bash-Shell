Assignment 1
Deadline: 02/02/22
Extension: 02/06/22
Andre D'Souza
0952594
///////////////////////// Folder Structure /////////////////////////////////////

/bin
  <Executables>
/docs
  <.pdf>
/include
  <.h>
/src
  <.c>
Makefile
.gitignore
sortfile.txt
testfile.txt

////////////////////// How to Compile the Program //////////////////////////////
"make"

///////////////////////// How to Run the Program ///////////////////////////////
"make run"

*Note* must enter command "make" before "make run"

/////////////////// How to remove the compiled source executables //////////////
"make clean"

//////////////////////////// About the Shell ///////////////////////////////////
The program will begin with the current user's name printed out in square
brackets along with a semicolon and cwd.
eg. [adsouz03@socs]:/home/undergrad/1/adsouz03/Desktop/CIS_3110/W22/A1>

The program will use the passwd struct to find the current user's home directory
and set the Environment Variables using the setEnvironment() in funcSet3.c


If the program has a problem with obtaining the passwd struct and
getpwuid(uid) == NULL. Then the username will be set to a default called user

eg. [user@socs]:/home/undergrad/1/adsouz03/Desktop/CIS_3110/W22/A1>

In this edge case since the passwd struct which contains the User's home
directory cannot be located. The program will set the current working directory
as the user's Home Directory ($myHOME) and the .CIS_3110_history file will be
stored in this current working directory along with the .CIS_3110_profile.


On termination of the shell the program deletes the .CIS3110_history and
.CIS_3110_profile files from the user's home directory.

////////////////////////// Example Commands ////////////////////////////////////
Function Set 1:
exit --> Will terminate the program immediately
clear
ls
ls -l

Function Set 2:
ls -lt > testfile.txt
sort < sortfile.txt
ping -c 5 google.com | grep rtt

Function Set 3:
export
history
history -c
history # --> which outputs only the last # command lines
cd ~ --> Which changes current directory to home directory
cd * --> Where * is the directory which you want to change to.

///////////////////////////// Git History///////////////////////////////////////
* ad06cae 2022-02-06 | Cleaned up files and added comments (HEAD -> master, tag: v1.0) [Andre D'Souza]
* a39e027 2022-02-06 | Refactored Makefile and main.c to myShell.c to conform to Assignment specifications [Andre D'Souza]
* c08777b 2022-02-06 | Cleaning up last staged files [Andre D'Souza]
* ffbcc7b 2022-01-20 | Added code to handel '&' although not complete [Andre D'Souza]
* 3030ebe 2022-01-19 | Added DEBUG_PRINT to improve readability and debugging [Andre D'Souza]
* c26e1a3 2022-01-19 | Cleaning up files [Andre D'Souza]
* 6ba46ab 2022-01-19 | Refactored historyWrite() to not include '\n' user command inputs to the history (tag: v0.3) [Andre D'Souza]
* 5c515f6 2022-01-19 | Refactored setting the shell environment in main to setEnvironmnet() in funcSet3 [Andre D'Souza]
* a005470 2022-01-19 | Added myHISTFILE and myHOME shell environment variables [Andre D'Souza]
* 14b57fb 2022-01-18 | Added myHISTFILE string to store history file location in /bin [Andre D'Souza]
* a83dcd8 2022-01-18 | Added Change Directory 'cd' functionality and prints current working directory as shell prompt [Andre D'Souza]
* 7b05352 2022-01-18 | Added TA email to README [Andre D'Souza]
* 8bc7a58 2022-01-17 | Added Functionality for history commands [Andre D'Souza]
* e577209 2022-01-17 | Completed Functionality to handel '|' operator. Need to fix edge case where first input into shell is either '\n', '<', '>', '|' which results in segmentation fault [Andre D'Souza]
* 8622a7e 2022-01-17 | Added -Wpedantic and -std=gnu99 flags [Andre D'Souza]
* 1981b83 2022-01-13 | Removed redundant code. Added skeleton for piping() '|' still needs to be refactored [Andre D'Souza]
* c0d2b85 2022-01-13 | Fixed bug where '<' or '>' would display output for previous user input [Andre D'Souza]
* 17c3163 2022-01-13 | Refactored main() to account for the '<' operator [Andre D'Souza]
* 2e4e582 2022-01-13 | Refactored shellInput() to handel '<' operator [Andre D'Souza]
* f48dfaa 2022-01-13 | Added inRedirFromFile() to Redirect command input from a file [Andre D'Souza]
* 701e186 2022-01-13 | Refactored main() to account for '>' operator [Andre D'Souza]
* 62004ae 2022-01-13 | Refactored shellInput() to handel '>' operator and arg2[] to store operands [Andre D'Souza]
* 6e8893f 2022-01-13 | Added outRedirToFile() to Redirect command output to file [Andre D'Souza]
* 602967d 2022-01-12 | Refactored forked execution conditions (tag: v0.2) [Andre D'Souza]
* 560fa6f 2022-01-12 | Added note about /usr/local/bin:/usr/bin:/bin:/usr/local/games:/usr/games directories [Andre D'Souza]
* 49fe866 2022-01-12 | Added functionality to execute local programs with './' prefixes in local bin directory [Andre D'Souza]
* 91b1b79 2022-01-12 | Refactored Makefile to build testfile.c, Refactored gitignore file to not include testfile executable [Andre D'Souza]
* 68f4d45 2022-01-12 | Created testfile.c to test executing local files in shell. Program just prints then sleeps for 10s then prints again on exit [Andre D'Souza]
* 8d4a217 2022-01-12 | Refactored gitignore to exclude adsouz03Shell executable file [Andre D'Souza]
* bebae34 2022-01-12 | Added functionality to execute programs in /bin and /usr/bin dirs. Added check if fork() failed [Andre D'Souza]
* 2f14fac 2022-01-12 | Refactored ShellInput to include arguments [Andre D'Souza]
* 8d85bf7 2022-01-12 | Added README.txt file with notes on exec commands [Andre D'Souza]
* 6171173 2022-01-12 | Fixed fork() infinite loop bug [Andre D'Souza]
* 548e3b5 2022-01-12 | Refactored Makefile to rename executable to adsouz03Shell [Andre D'Souza]
* 8e96182 2022-01-11 | Added exclusion of executable File myShell [Andre D'Souza]
* 52520be 2022-01-11 | Added fork(), wait(), and execve() commands to execute user input. Needs to be refactored as child proceses do not terminate [Andre D'Souza]
* 0287d84 2022-01-11 | Changed arg[] to include the orignal user command, as execve() argv[] parameter needs the original command aswell as arguments [Andre D'Souza]
* 51c8af9 2022-01-11 | Added Valgrind support to Makefile [Andre D'Souza]
* 4490b07 2022-01-11 | Refactored display_Shell() to displayShell() added support for uid_t userName and cleaned up commented out code [Andre D'Souza]
* b40a635 2022-01-11 | Refactored main.c to test struct passwd *p and Confirmed working as expected in main [Andre D'Souza]
* 4629a8f 2022-01-11 | Refactored clearScreen() to clear() to improve readability [Andre D'Souza]
* 269c2ae 2022-01-10 | Refactored Display_Shell() and main.c to include uid and euid but commented them out for now [Andre D'Souza]
* 3bad82c 2022-01-10 | Refactored Shell_input() to ShellInput() and fixed bugs in function, Added clearScreen() to clear the screen on user input 'clear', updated main.c to test functions [Andre D'Souza]
* 1d5e3fb 2022-01-10 | Updated Makefile to be std=c11 compliant [Andre D'Souza]
* 7a16110 2022-01-10 | Temporary Shell_input() [Andre D'Souza]
* fab6e98 2022-01-10 | Added display_Shell() Command to funcSet1 [Andre D'Souza]
* ead76af 2022-01-10 | Created Project Skeleton and Makefile to ensure working as expected (tag: v0.1) [Andre D'Souza]
