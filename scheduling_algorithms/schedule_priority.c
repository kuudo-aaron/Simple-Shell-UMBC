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

    printf("For this algorithm, I made a for loop using i that checks each task in the linkedlist for priorities from the MAX_PRIORITY to the MIN_PRIORITY (10 -> 1)\n"); 
    printf("Within the for loop, I made a while loop that traverses through the linkedlist. If the current task priority is equal to the current i priority, it runs the task. \n");

    struct task * del = NULL;
    struct node * temp = head;
    for(int i = MAX_PRIORITY; i >= MIN_PRIORITY; i--){
        printf("Priority loop i is equal to %d: \n", i);
        while(temp != NULL){
            if(temp -> task -> priority == i){
                 run(temp -> task, temp -> task -> burst);
                 del = temp -> task;
            }
            if (del != NULL){
                delete(&head, del);
                del = NULL;
            }
            temp = temp -> next;
        }
        temp = head;
    }
}
