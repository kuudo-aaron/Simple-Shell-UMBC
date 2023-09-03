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
    printf("Scheduling using SJF \n");
    printf("For SJF, I used bubblesort to sort through my linkedlist from smallest and largest burst values.\n");
    printf("Using bubblesort, I reorganized the linkedlist from smallest to greatest burst values and then I ran the task linkedlist after bubblesort was complete \n");
    if(head -> next == NULL)
         run(head -> task, head -> task -> burst);

    struct node * current = head;
    struct node * current_next;
    for(current = head; current != NULL; current = current -> next){
        for(current_next = current -> next; current_next != NULL; current_next = current_next -> next){
            if(current -> task -> burst > current_next -> task -> burst){
                printf("%s burst is smaller than %s. Swapping..\n", current_next -> task -> name, current -> task -> name);
                struct task *temp = current_next -> task;
                current_next -> task = current -> task;
                current -> task = temp;

            }
        }
    }

    struct node * temp = head;

    while(temp != NULL){
        run(temp -> task, temp -> task -> burst);
        printf("Deleting %s with burst %d\n",temp->task->name,temp->task->burst);
        delete(&head, temp -> task);
        temp = temp -> next;
    }
}

