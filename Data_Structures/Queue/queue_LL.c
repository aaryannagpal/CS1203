#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node *next;
};

struct Node *start = NULL;
struct Node *end = NULL;

typedef struct Node N;

void enqueue(int x){
    N *t;
    t=(N *)malloc(sizeof(N));
    if(t==NULL)
        printf("Queue is full\n");
    else{
        t->data=x;
        t->next=NULL;
        if(start==NULL)
            start=end=t;
        else{
            end->next=t;
            end=t;
        }
    }
}

int dequeue(){
    int x=-1;
    N *t;
    if(start==NULL)
        printf("Queue is empty\n");
    else{
        t=start;
        start=start->next;
        x=t->data;
        free(t);
    }
    return x;
}

void show(){
    N *p;
    p=start;
    while(p){
        printf("%d ", p->data);
        p=p->next;
    }
    printf("\n");
}

int main(){
    enqueue(14);
    enqueue(55);
    enqueue(6);
    enqueue(12);
    enqueue(53);
    //push(0);

    show();

    dequeue();
    dequeue();

    show();

    return 0;
}
