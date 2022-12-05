//program to make Binary Search Tree

#include<stdio.h>
#include<stdlib.h>

struct node
{
    int data;
    struct node *left;
    struct node *right;
};

typedef struct node * Node;

Node root = NULL; //defining here else will have to update in every function

Node newNode(int data)
{
    Node temp = (Node)malloc(sizeof(struct node));
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

Node insert (Node root, int data)
{
    if (root == NULL)
        return newNode(data);
    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);
    return root;
}

void inorder(Node root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

Node arrayToBST(int *a, int n) {
    Node root = NULL;
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
    inorder(arrayToBST(arr, n));
}