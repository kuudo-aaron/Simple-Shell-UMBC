#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "task.h"
#include "list.h"
#include "schedulers.h"
#include "cpu.h"

struct node *head = NULL;

void add(char *name, int priority, int burst){
    Task *newTask = malloc(sizeof(Task*));
    newTask -> name = strdup(name);
    newTask -> priority = priority;
    newTask -> burst = burst;
    insert(&head, newTask);
}

void schedule(){
    printf("Scheduling using Round Robin \n");
    printf("For Round Robin, I used 2 while loops\n");
    printf("The outside loop is to ensure we keep looping until the linkedlist is deleted.\n");
    printf("The inside loops through the linkedlist and checks to see if a task's burst is over QUANTUM.\n");
    printf("If a tasks burst is over the QUANTUM, we subtract QUANTUM from the burst, run the task, and 'move it' back to the end of the line by looping through again. \n");
    printf("If a tasks burst is less than the QUANTUM, we just run the task and delete it from our linkedList. \n");
    printf("We keep looping until the linkedlist is deleted. \n");
    while(head != NULL){
        struct node *temp = head; 
        while(temp != NULL){
            if(temp -> task -> burst > 10){
                printf("Task's burst is higher than quantum. Moving it to back of the queue \n");
                run(temp -> task, QUANTUM);
                temp -> task -> burst = temp -> task -> burst - QUANTUM;
            }else{
                printf("Task's burst is lower than or equal to QUANTUM. Running it and deleting it from the linkedlist \n");
                run(temp -> task, temp -> task -> burst);
                delete(&head, temp -> task);
            }
            temp = temp -> next;
        }
    }
}