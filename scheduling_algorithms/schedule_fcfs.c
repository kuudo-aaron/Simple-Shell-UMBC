#include <stdio.h>
#include "schedulers.h"
#include "list.h"
#include "task.h"
#include <string.h>
#include <stdlib.h>
#include "cpu.h"

struct node *head;
int tid_counter = 1;

void add(char *name, int priority, int burst){
    Task *newTask = malloc(sizeof(Task*));
    newTask -> name = strdup(name);
    newTask -> tid = tid_counter;
    newTask -> priority = priority;
    newTask -> burst = burst;
    insert(&head, newTask);
    tid_counter = tid_counter + 1;
}

void schedule(){
    printf("Scheduling using FCFS: \n");

    printf("For this algorithm, I utilized the tid_counter attribute in the Task struct. Each time a task was added,\n"); 
    printf("they are given a tid that increases as more elements are added. The algorithm will then loop from the beginning to the final tid_counter\n");
    printf("and run the task in the order of FIFO (First in First Out)\n");
    for(int i = 1; i < tid_counter; i++){
        struct node *temp = head;
        while (temp -> task -> tid != i && temp != NULL) {
            temp = temp -> next;
        }
        printf("Task: %s, tid: %d\n", temp -> task -> name, temp -> task -> tid);
        run(temp -> task, temp -> task -> burst);
        printf("Deleting task %s\n\n", temp -> task -> name);
        delete(&head, temp -> task); 
    }
}
