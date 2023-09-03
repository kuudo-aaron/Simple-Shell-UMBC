Name: Aaron Ku
Section: CMSC 421 Tompkins 2:30 pm -> 3:45 pm 

Approach to CMSC 421 Homework 2 - simple_shell.c 

To ensure the user launched the shell program without additonal arguements, I checked if the arguments (argc) was higher than the minimal amount needed (1). 

When reading in input from stdin, I ensured that the shell would be able to accept any arbitrary length by using the getline() function that takes the address of a buffer for the input and the address of a buffersize. getline reads everything from stdin. 

After reading in the input, the input is sent to my parseInput function. The parseInput function parses through and separates the arguments delimited by spaces and returns an array of pointers to each argument including the command at parsedInput[0].

After the input is parsed, the input is sent to my executeCmd function that forks into a parent and a child process. The child process will attempt to execute the command using execvp() and the parent will wait. If unsucessful, an error string will be sent to stderr. If sucessful, the command will run.

When the user inputs exit, the program will check to see if there is another argument with exit and if it is a number. If not, the program will continue running. If the extra argument is a number, it will exit returning that number. If there is no extra argument, the program will simply exit return 0. 
