// Iterative C program to reverse a linked list
#include <stdio.h>
#include <stdlib.h>

/* Link list node */
struct node {
	int data;
	struct node* link;
};

/* Function to reverse the linked list */
void reverse(struct node** start)
{
	struct node* prev = NULL;
	struct node* current = *start;
	struct node* next = NULL;

	while (current != NULL) {
		// Store next
		next = current->link;

		// Reverse current node's pointer
		current->link = prev;

		// Move pointers one position ahead.
		prev = current;
		current = next;
	}
	*start = prev;
}

// Function to add nodes
void add_nodes(struct node** next, int new)
{
	struct node* proxy  = (struct node*)malloc(sizeof(struct node));
	proxy->data = new;
	proxy->link = (*next);
	(*next) = proxy;
}

/* Function to print linked list */
void printArray(struct node* head)
{
	struct node* temp = head;
	while (temp != NULL) {
		printf("%d ", temp->data);
		temp = temp->link;
	}
}

int main()
{
	struct node* head = NULL;

	add_nodes(&head, 20);
    add_nodes(&head, 21);
    add_nodes(&head, 22);
    add_nodes(&head, 23);
    add_nodes(&head, 24);


	printf("Given linked list\n");
	printArray(head);
	reverse(&head);
	printf("\nReversed linked list \n");
	printArray(head);
	getchar();
}
