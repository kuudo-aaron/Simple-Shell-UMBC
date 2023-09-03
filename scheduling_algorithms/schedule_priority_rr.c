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

    printf("Scheduling using Priority Round Robin: \n");

    printf("For this algorithm, I made a for loop using i that checks the linkedlist for priorities from the MAX_PRIORITY to the MIN_PRIORITY (10 -> 1)\n"); 
    printf("For each priority number, I made a linkedlist with head = prioHead and I added to the linkedlist whenever a task had the same priority \n");
    printf("If there were no tasks with i priority, we move on and check the next priority\n");
    printf("If there is only 1 task with i priority, we just run the task and move on");
    printf("However, if there are more than 1 task with i priority, use the round robin system and use 2 loops.\n");
    printf("The outside loop is to ensure we keep looping until the linkedlist is deleted.\n");
    printf("The inside loops through the linkedlist and checks to see if a task's burst is over QUANTUM.\n");
    printf("If a tasks burst is over the QUANTUM, we subtract QUANTUM from the burst, run the task, and 'move it' back to the end of the line by looping through again. \n");
    printf("If a tasks burst is less than the QUANTUM, we just run the task and delete it from our linkedList. \n");
    printf("We keep looping until the linkedlist is deleted. \n");

    struct node * temp = head;
    struct node * prioHead = NULL;  
    for( int i = MAX_PRIORITY; i >= MIN_PRIORITY; i--){
        printf("Looping through priorities, Priority is currently at: %d\n", i);
        temp = head;
        while(temp!= NULL){
            if(temp -> task -> priority == i){
                printf("Inserting into the new linkedList: %s with Priority %d. \n", temp -> task -> name, temp -> task -> priority);
                insert(&prioHead, temp -> task);
            }
        temp = temp -> next;
        }
        if(prioHead == NULL){
            //do nothing
            printf("No tasks with priority %d, Moving on... \n", i );
        }
        else if(prioHead -> next == NULL){
            printf("Only 1 task with priority %d. Running the task \n", i);
            run(prioHead -> task, prioHead -> task -> burst);
            delete(&prioHead, prioHead -> task);
        }else{
            while(prioHead != NULL){
                struct node* traversePrio = prioHead;
                while(traversePrio != NULL){
                    if(traversePrio -> task -> burst > QUANTUM){
                        printf("Task's burst is higher than quantum. Moving it to back of the queue \n");
                        run(traversePrio -> task, QUANTUM);
                        traversePrio -> task -> burst = traversePrio -> task -> burst - QUANTUM;
                    }else{
                        printf("Task's burst is lower than or equal to QUANTUM. Running it and deleting it from the linkedlist \n");
                        run(traversePrio -> task, traversePrio -> task -> burst);
                        delete(&prioHead, traversePrio -> task);
                    }
                    traversePrio = traversePrio -> next;
                }
            }
        }
       prioHead = NULL;
    }
}
