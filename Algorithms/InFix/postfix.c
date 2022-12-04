#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node{
    int data;
    struct Node *next;
}*top = NULL; 


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

//________ STACK CREATED __________

//________ ONTO THE POSTFIX ________


int pedmas(char x){//returns precedence of operator
    if(x=='+' || x=='-')
        return 1;
    else if(x=='*' || x=='/')
        return 2;
    return 0;
}

int checkOperand(char x){
    if(x=='+' || x=='-' || x=='*' || x=='/') //if it is an operator
        return 0;
    else
        return 1;
}


void printStack(){
    struct Node *p;
    p=top;
    while(p!=NULL){
        printf("%d ",p->data);
        p=p->next;
    }
    printf("\n");
}

char* PostFix(char *infix){
    int i=0,j=0;
    char *post;
    int len = strlen(infix);
    post = (char *)malloc((len+2)*sizeof(char)); //+2 for null and \n

    while(infix[i]!='\0'){
        if(checkOperand(infix[i]))
            post[j++]=infix[i++]; //if operand, add to postfix
        else{//if operator check precedence
            if(pedmas(infix[i])>pedmas(top->data)) //if operator > precedence than top
                push(infix[i++]);//push to stack
            else{
                post[j++]=pop(); //else pop and add to postfix
            }
        }
    }
    while(top!=NULL) //if stack not empty, pop and add to postfix
        post[j++]=pop();
    post[j]='\0';
    return post;
}


int main(){

    char *expression = "x+y*z-w+u";
    push('\n'); //so the stack is not empty and won't raise error

    char *postfix = PostFix(expression);

    printf("%s", postfix);

    return 0;
}