#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node* link;
};

struct node* sorted_head = NULL;
struct node* unsorted_head = NULL;

void add_nodes(int n)
{
    struct node* new = (struct node*)malloc(sizeof(struct node)); //initializing new node
    new->data = n; //adding data to it
    new->link = unsorted_head; //linking previous node to new node
    unsorted_head = new; //making new node as head
}


void insert(struct node* new)
{

	if (sorted_head == NULL || sorted_head->data >= new->data) { //for the head end
		new->link = sorted_head;
		sorted_head = new;
	}
	else {
		struct node* current = sorted_head;
		// locating the node before the point of insertion
		while (current->link != NULL && current->link->data < new->data) {
			current = current->link;
		}

		new->link = current->link;
		current->link = new;
	}
}
//sorting the linked list
void insertionsort()
{

	struct node* current = unsorted_head;

	while (current != NULL) {

		// Store next for next iteration
		struct node* next = current->link;

		// insert current in sorted linked list
		insert(current);

		// Update current
		current = next;
	}
	// Update head to point to sorted linked list
	unsorted_head = sorted_head;
}

/* Function to print linked list */
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

	insertionsort(sorted_head);

	printf("Linked List after sorting:\n");
	print_data(sorted_head);
}

// This code is contributed by Sornodeep Chandra
