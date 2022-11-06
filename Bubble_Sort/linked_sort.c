#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node* link;
};

struct node* swap(struct node* pointer_1, struct node* pointer_2)
{
	struct node* a = pointer_2->link;
	pointer_2->link = pointer_1;
	pointer_1->link = a;
	return pointer_2;
}

struct node* unsorted_head = NULL;


int bubble(struct node** New, int list_size)
{
	struct node** new;
	int i, j, s;

	for (i = 0; i <= list_size; i++) { //looping through the list

		new = New; //setting new to the head of the list
		s = 0; //setting s to 0

		for (j = 0; j < list_size - i - 1; j++) {

			struct node* pointer_1 = *new; //setting pointer_1 to the head of the list
			struct node* pointer_2 = pointer_1->link; //setting pointer_2 to the next node

			if (pointer_1->data > pointer_2->data) {

				// update the link after swapping
				*new = swap(pointer_1, pointer_2);//swapping the nodes
				s = 1;
			}

			new = &(*new)->link;
		}

		/* break if the loop ended without any swap */
		if (s == 0)
			break; //if no swaps were made, break out of the loop
	}
}


void add_nodes(int n)
{
    struct node* new = (struct node*)malloc(sizeof(struct node)); //initializing new node
    new->data = n; //adding data to it
    new->link = unsorted_head; //linking previous node to new node
    unsorted_head = new; //making new node as head
}

/* Function to print linked list */
void print_data(struct node *head){
    if (head == NULL){
        printf("The list is empty");
    }
    struct node *pointer = NULL;
    pointer = head;
    while (pointer != NULL){
        printf("%d ",pointer->data);
        pointer = pointer->link;
    }
}

// Driver program to test above functions
int main()
{
	add_nodes(1);
    add_nodes(2);
    add_nodes(45);
    add_nodes(22);
    add_nodes(346);
    add_nodes(4);
    add_nodes(5);
	printf("Unsorted List:\n");

	print_data(unsorted_head);
	printf("\n");

	bubble(&unsorted_head, 7);

	printf("Linked List after sorting:\n");
	print_data(unsorted_head);
}


