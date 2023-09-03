#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "utils.h"

int shellLoop(void);
char *readInput(void);
char **parseInput(char *);
int executeCmd(char **);
int procCmd(char **);

int main(int argc, char **argv){

    int exitStatus = 0;
    char cmdLineMsg[60] = "This program does not support command line arguments \n";
    // If more than one argument when shell launched, exit.
    if(argc > 1){
      fprintf(stderr, cmdLineMsg);
      return 1;
    }

    exitStatus = shellLoop();

    return exitStatus;
}

int shellLoop(void){
   int continueLoop = 1;
   char *userInput = NULL;
   char **parsedInput = NULL;

   //Main Shell Loop
   while(continueLoop == 1){
       printf("Prompt:");
       //Get raw input from user
       userInput = readInput();
       //If the user does not input anything. Restart loop
       if(userInput == NULL || strlen(userInput) == 0){
           printf("Empty String");
           continue;
       }
       //Send raw input in for parsing.
       parsedInput = parseInput(userInput);
       //If the parsedInput is equal to exit, check to see if there are
       //valid arguements
       if(strcasecmp(parsedInput[0], "Exit") == 0){
           //If user input exit with invalid arguments, restart the loop
           if(parsedInput[1] != NULL && atoi(parsedInput[1]) == 0){
                free(userInput);
                free(parsedInput);
                continue;
           }
           break;
       }
       //If the command is proc, start the proc filesystem command
       if(strcasecmp(parsedInput[0], "proc") == 0)
            procCmd(parsedInput);
       //Otherwise, execute the command.
       else{
            executeCmd(parsedInput);
       }
       free(userInput);
       free(parsedInput);
   }
   if(parsedInput[1] != NULL){
      int exitArg = atoi(parsedInput[1]);
      free(userInput);
      free(parsedInput);
      return exitArg;
   }else{
      free(userInput);
      free(parsedInput);
      return 0;
   }
}

char *readInput(void){
   ssize_t  bufferSize = 0;
   char *buffer = NULL;

   getline(&buffer, &bufferSize, stdin);
   size_t buffLen = strlen(buffer);
   if(buffLen > 0)
     buffer[buffLen-1] = '\0';
   char * output = unescape(buffer, stderr);
   free(buffer);
   return output;
}

char **parseInput(char *rawInput){
   
   int len = 10;
   int start = 0;
   char ** output = malloc(sizeof(char*) * len);
   char * token = strtok(rawInput, " ");

   //Split the rawInput using delimiter " "
   while(token!= NULL){
      output[start] = token;
      token = strtok(NULL, " ");
      start++;
      if(start == len){
          len = len * 5;
          output = realloc(output, sizeof(char*) * len);
      }
      output[start] = NULL;
   }
   return output;
}

int executeCmd(char **cmdString){
   pid_t pid;
   pid = fork();
   int error_status = 0;

   //If Child process, execute the command.
   if (pid == 0){
      printf("Executing %s ...... \n", cmdString[0]);
      error_status = execvp(cmdString[0], cmdString);
      if(error_status == -1){
          fprintf(stderr, "Command was unsuccessful. \n");
      }
   }

   else if(pid < 0){
      printf("Fork Failed");
      return 1;
   }
   //Parent waits
   wait(NULL);
   return 0;
}

int procCmd(char **procArgs){
   //If proc is used without any arguements, print error and return
   if(procArgs[1] == NULL){
      fprintf(stderr, "Not enough arguments. Returning to prompt \n");
      return 1;
   }
   //Concatenate a filename for file opener to use.
   char fileName[] = "/";
   strcat(fileName, procArgs[0]);
   strcat(fileName, "/");
   strcat(fileName, procArgs[1]);

   FILE *parser = fopen(fileName, "r");
   //If the file cannot be found, send an error statement and return 1
   if(!parser){
      fprintf(stderr, "Error opening file %s \n", procArgs[1]);
      return 1;
   }
   char* buffer = NULL;
   ssize_t bufferSize = 0;
   ssize_t readLines;
   readLines = getline(&buffer, &bufferSize, parser);
   //Keep reading lines from the file until the file is empty.
   while(readLines >= 0){
        printf("%s", buffer);
        readLines = getline(&buffer, &bufferSize, parser);
   }
   free(buffer);
   fclose(parser);
   return 0;

}
