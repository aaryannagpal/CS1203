#include <stdio.h>
#include<stdlib.h>


struct node
{
    int data;
    struct node *link; //only one link for the next node
};
//function to create linked list

void add_nodes(struct node** next, int n)
{
    struct node* new 
            = (struct node*)malloc(sizeof(struct node)); //initializing new node
    
    new->data = n; //adding data to it
    new->link = (*next); //linking previous node to new node
    (*next) = new; //making new node as head
}

int count_nodes(struct node *head){
    int count = 0; // Initialize count
    struct node* current = head; // Initialize current
    while (current != NULL) {
        count++;
        current = current->link;
    }
    return count;
}

int main(){

    //linked list created
    struct node *head = NULL; //initializing

    add_nodes(&head, 1);
    add_nodes(&head, 2);


    printf("%d",count_nodes(head));
    return 0;
}