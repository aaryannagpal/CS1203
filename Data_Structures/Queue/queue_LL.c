#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node *next;
};

struct Node *start = NULL;
struct Node *end = NULL;

typedef struct Node N;

void push(int x){
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

int pop(){
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
    push(14);
    push(55);
    push(6);
    push(12);
    push(53);
    //push(0);

    show();

    pop();
    pop();

    show();

    return 0;
}
