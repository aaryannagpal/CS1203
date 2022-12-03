//Psuedocode from https://www.youtube.com/watch?v=iaKu6jaKPFw&ab_channel=UHMICSAlgorithms

#include <stdio.h>
#include <stdlib.h>

#define MAX_LEVEL 6

typedef struct Node {
    int key;
    int value;
    struct Node **forward;
} Node;

typedef struct SkipList {
    int level;
    int size;
    struct Node *header;
} SkipList;

/* Create a new node with a given key and value and specified level */
Node *newNode(int key, int value, int level) {
    Node *n = malloc(sizeof(Node));
    n->key = key;
    n->value = value;
    n->forward = malloc(sizeof(Node*) * (level+1));

    for (int i = 0; i < level+1; i++) {
        n->forward[i] = NULL;
    }
    return n;
}

/* Create a new skip list with a given maximum level */
SkipList *initialize(int level) {
    SkipList *list = malloc(sizeof(SkipList));
    list->level = 0;
    list->size = 0;
    list->header = newNode(0, 0, level);
    return list;
}

/* Generate a random level for a new node */
int randomLevel() {
    int level = 0;
    while (rand() < RAND_MAX/2 && level < MAX_LEVEL) {
        level++;
    }
    return level;
}

/* Insert a new key/value pair into the skip list */
void insert(SkipList *list, int key, int value) {
    Node *update[MAX_LEVEL+1];
    Node *x = list->header;
    int i, level;

    /* Find the place to insert the new node */
    for (i = list->level; i >= 0; i--) {
        while (x->forward[i] && x->forward[i]->key < key) {
            x = x->forward[i];
        }
        update[i] = x;
    }
    x = x->forward[0];

    /* If the key already exists, just update the value */
    if (x && x->key == key) {
        x->value = value;
    } else {
        /* Generate a random level for the new node */
        level = randomLevel();
        if (level > list->level) {
            for (i = list->level+1; i <= level; i++) {
                update[i] = list->header;
            }
            list->level = level;
        }

        /* Insert the new node at the generated level */
        x = newNode(key, value, level);
        for (i = 0; i <= level; i++) {
            x->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = x;
        }
        list->size++;
    }
}

/* Search for a node with a given key */
Node *search(SkipList *list, int key) {
    Node *x = list->header;
    int i;

    for (i = list->level; i >= 0; i--) {
        while (x->forward[i] && x->forward[i]->key < key) {
            x = x->forward[i];
        }
    }
    x = x->forward[0];

    if (x && x->key == key) {
        return x;
    } else {
        return NULL;
    }
}

/* Delete a node with a given key */

void delete(SkipList *list, int key) {
    Node *update[MAX_LEVEL+1];
    Node *x = list->header;
    int i;

    /* Find the node to delete */
    for (i = list->level; i >= 0; i--) {
        while (x->forward[i] && x->forward[i]->key < key) {
            x = x->forward[i];
        }
        update[i] = x;
    }
    x = x->forward[0];

    /* If the node was found, delete it */
    if (x && x->key == key) {
        for (i = 0; i <= list->level; i++) {
            if (update[i]->forward[i] != x) {
                break;
            }
            update[i]->forward[i] = x->forward[i];
        }
        printf("Deleted %d\n", x->key);
        free(x->forward);
        free(x);

        /* Update the list level */
        while (list->level > 0 && list->header->forward[list->level] == NULL) {
            list->level--;
        }
        list->size--;
    }
    else{
        printf("Key not found\n");
    }
}

/* Print the skip list */

void print(SkipList *list) {
    Node *x = list->header->forward[0];
    int i;

    printf("Skip list (level=%d, size=%d): ", list->level, list->size);
    while (x) {
        printf("%d ", x->key);
        x = x->forward[0];
    }
    printf("\n");

    for (i = list->level; i >= 0; i--) {
        x = list->header;
        printf("Level %d: ", i);
        while (x) {
            if (x->forward[i]) {
                printf("%d ", x->forward[i]->key);
            } else {
                printf("X ");
            }
            x = x->forward[i];
        }
        printf("\n");
    }
}

int main() {
    int i;
    SkipList *list = initialize(MAX_LEVEL);

    //srand(time(NULL));

    for (i = 0; i < 10; i++) {
        insert(list, i, i);
    }
    print(list);

    delete(list, 5);

    print(list);

    delete(list, 1);

    print(list);
    return 0;
}
