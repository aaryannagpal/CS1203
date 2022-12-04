// AVL tree

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;
    int height;
    struct node *left;
    struct node *right;
} node;

int max(int a, int b) {
    return a > b ? a : b;
}

int height(node *n) {
    if (n == NULL) {
        return 0;
    }
    return n->height;
}

node *new_node(int key) {
    node *n = malloc(sizeof(node));
    n->key = key;
    n->height = 1;
    n->left = NULL;
    n->right = NULL;
    return n;
}

node *right_rotate(node *y) {
    node *x = y->left;
    node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

node *left_rotate(node *x) {
    node *y = x->right;
    node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int get_balance(node *n) {
    if (n == NULL) {
        return 0;
    }
    return height(n->left) - height(n->right);
}

node *insert(node *n, int key) {
    if (n == NULL) {
        return new_node(key);
    }

    if (key < n->key) {
        n->left = insert(n->left, key);
    } else if (key > n->key) {
        n->right = insert(n->right, key);
    } else {
        return n;
    }

    n->height = 1 + max(height(n->left), height(n->right));

    int balance = get_balance(n);

    if (balance > 1 && key < n->left->key) {
        return right_rotate(n);
    }

    if (balance < -1 && key > n->right->key) {
        return left_rotate(n);
    }

    if (balance > 1 && key > n->left->key) {
        n->left = left_rotate(n->left);
        return right_rotate(n);
    }

    if (balance < -1 && key < n->right->key) {
        n->right = right_rotate(n->right);
        return left_rotate(n);
    }

    return n;
}

node *min_value_node(node *n) {
    node *current = n;

    while (current->left != NULL) {
        current = current->left;
    }

    return current;
}

node *delete(node *root, int key) {
    if (root == NULL) {
        return root;
    }

    if (key < root->key) {
        root->left = delete(root->left, key);
    } else if (key > root->key) {
        root->right = delete(root->right, key);
    } else {
        if ((root->left == NULL) || (root->right == NULL)) {
            node *temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else *root = *temp;
            free(temp);
        } else { node *temp = min_value_node(root->right);

            root->key = temp->key;

            root->right = delete(root->right, temp->key);
        }
    }
    
    if (root == NULL) {
        return root;
    }  

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = get_balance(root);
    if (balance > 1 && get_balance(root->left) >= 0) {
        return right_rotate(root);
    }

    if (balance > 1 && get_balance(root->left) < 0) {
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }

    if (balance < -1 && get_balance(root->right) <= 0) {
        return left_rotate(root);
    }

    if (balance < -1 && get_balance(root->right) > 0) {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }

    return root;
}

void print_tree(node *n) {
    if (n == NULL) {
        return;
    }

    printf("%d", n->key);
    print_tree(n->left);
    print_tree(n->right);
}


int main() {
    node *root = NULL;
    int a, i;
    for (i = 0, a = 1; i < 5; i++) {
        root = insert(root, a);
        a *= 2;
    }

  print_tree(root);

  root = delete(root, 4);

  printf("\n \nAfter deletion: ");
  print_tree(root);
  printf("\n");

  return 0;
}