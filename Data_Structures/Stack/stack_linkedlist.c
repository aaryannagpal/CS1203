#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node *next;
};//*top = NULL; //inefficient if using more than one stacks

//Alternative: declare globally and all functions must have stack as parameter

struct Node *top = NULL;

void push(int x){
    struct Node *t;
    t=(struct Node *)malloc(sizeof(struct Node));
    if(t==NULL)
        printf("Stack is full\n");
    else{
        t->data=x;
        t->next=top;
        top=t;
    }
}

int pop(){
    struct Node *t;
    int x=-1;
    if(top==NULL)
        printf("Stack is empty\n");
    else{
        t=top;
        top=top->next;
        x=t->data;
        free(t);
    }
    return x;
}

void Display(){
    struct Node *p;
    p=top;
    while(p!=NULL){
        printf("%d ",p->data);
        p=p->next;
    }
    printf("\n");
}

int main(){

    push(10);
    push(20);
    push(30);

    Display();

    printf("Popped: %d\n",pop());

    Display();
    return 0;
}