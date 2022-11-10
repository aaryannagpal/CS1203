#include <stdio.h>
#include <stdlib.h>

struct node {
	int value;
	struct node *left, *right;
};

typedef struct node * NodeAddress;


NodeAddress new(int val)
{
	NodeAddress temp = (NodeAddress)malloc(sizeof(struct node));
	temp->value = val;
	temp->left = temp->right = NULL;
	return temp;
}

void PrintOrder(NodeAddress root)
{
	if (root != NULL) {
        PrintOrder(root->right);
        printf("%d \n", root->value);
		PrintOrder(root->left);
	}
}


NodeAddress insert(NodeAddress node, int key)
{
	if (node == NULL)
		return new(key);

	if (key > node->value)
		node->left = insert(node->left, key);
	else if (key < node->value)
		node->right = insert(node->right, key);

	return node;
}

NodeAddress arrayToReverseBST(int *a, int n) {
    NodeAddress root = NULL;
    for(int i=0; i<n; i++) {
        root = insert(root, *a);
        a++;
    }
    return root;
}
int main(){
    printf("Enter the number of elements in the array: \n");
    int n;
    scanf("%d", &n);

    int arr[n];
    printf("Enter the elements of the array: \n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    
    printf("\nThe elements of the BST are: \n");
    PrintOrder(arrayToReverseBST(arr, n));
}