#include <stdio.h>
#include<stdlib.h>


struct node
{
    int data;
    struct node *link; //only one link for the next node
};

void print_data(struct node *head){
    if (head == NULL){
        printf("The list is empty");
    }
    struct node *pointer = NULL;
    pointer = head;
    while (pointer != NULL){
        printf("%d\n",pointer->data);
        pointer = pointer->link;
    }
}

int main(){
    //creating the first node
    struct node *head = NULL; //initializing
    head = (struct node*)malloc(sizeof(struct node)); //typecasting the pointer

    head->data = 100;
    head->link = NULL;

    struct node *new = malloc(sizeof(struct node)); //creating new pointer
    for (int i = 0; i <10;++i){
        new->data = i;
        new->link = NULL;
        head->link = new;
        head = new;
        //printf("%d\n",new->data);
    }
    return 0;
}