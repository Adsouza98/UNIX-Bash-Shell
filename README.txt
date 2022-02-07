Assignment 1
Deadline: 02/02/22
Extension: 02/06/22
Andre D'Souza
0952594

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
