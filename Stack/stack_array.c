#include <stdio.h>
#include <stdlib.h>

struct Stack{
    int size;
    int top;
    int *A; //array storing the elements
};

typedef struct Stack Stack;

void create(Stack *p){
    // printf("Enter size");
    // scanf("%d",&p->size);

    //for input from user, for now we are keeping it at 5

    p->size = 2;

    p->top=-1;
    p->A=(int *)malloc(p->size*sizeof(int));
}

void Display(Stack p){
    int i;
    for(i=p.top;i>=0;i--)
        printf("%d\n",p.A[i]);
    printf("\n");
}

void push(Stack *p,int x){
    if(p->top==p->size-1)
        printf("Stack overflow\n");
    else{
        p->top++;
        p->A[p->top]=x;
    }
}

int pop(Stack *p){
    int x=-1;
    if(p->top==-1)
        printf("Stack underflow\n");
    else{
        x=p->A[p->top--];
    }
    return x;
}

int checkEmpty(Stack p){
    if(p.top==-1)
        return 1;
    else
        return 0;
}

int checkFull(Stack p){
    if(p.top==p.size-1)
        return 1;
    else
        return 0;
}

void Top(Stack p){
    if(checkEmpty(p))
        printf("Stack is empty\n");
    else
        printf("%d", p.A[p.top]);
}


int main(){
    Stack p;
    create(&p);
    printf("Stack of size %d created\n\n", p.size);
    push(&p,3);
    push(&p,35);
    push(&p,76);
    Display(p);

    printf("\nTrying out Top\n");
    Top(p);
    printf("\n\nTrying out Pop\n\n");
    printf("%d deleted\n",pop(&p));
    printf("%d deleted\n",pop(&p));
    printf("%d deleted\n",pop(&p));

    printf("\nTrying out Top\n");
    Top(p);

}