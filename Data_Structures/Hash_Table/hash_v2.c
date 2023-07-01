#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Hash Table Node
struct Node {
    char key[256];
    char value[256];
    struct Node *next;
};

typedef struct Node Node;

// Hash Table
struct HashTable {
    int size;
    struct Node **table;
};

typedef struct HashTable HashTable;

// Create new hash table node
Node *newNode(char *key, char *value) {
    Node *node = malloc(sizeof(struct Node));
    strcpy(node->key, key);
    strcpy(node->value, value);
    node->next = NULL;
    return node;
}

// Create new hash table
HashTable *newHashTable(int size) {
    HashTable *table = malloc(sizeof(struct HashTable));
    table->size = size;
    table->table = malloc(sizeof(struct Node) * size);
    for (int i = 0; i < size; i++) {
    table->table[i] = NULL;
    }
    return table;
}

// Hash function to calculate index for a given key
int hash(HashTable *table, char *key) {
    int len = strlen(key);
    int sum = 0;
    for (int i = 0; i < len; i++) {
    sum += key[i];
    }
    return sum % table->size;
}

// Search for value associated with given key in hash table
char* search(struct HashTable *table, char *key) {
// Calculate index for key
    int index = hash(table, key);

    // Search linked list at given index for key
    Node *curr = table->table[index];
    while (curr) {
        if (strcmp(curr->key, key) == 0) {
            // Key found, return associated value
            return curr->value;
        }
        curr = curr->next;
    }

    // Key not found
    return NULL;
}

// Insert key and value into hash table
void insert(struct HashTable *table, char *key, char *value) {
    // Calculate index for key
    int index = hash(table, key);

    // Create new node for key and value
    Node *node = newNode(key, value);

    // Insert node at beginning of linked list at given index
    node->next = table->table[index];
    table->table[index] = node;
}

// Delete key and associated value from hash table
void delete(struct HashTable *table, char *key) {
    // Calculate index for key
    int index = hash(table, key);

    // Search linked list at given index for key
    Node *curr = table->table[index];
    Node *prev = NULL;
    while (curr) {
        if (strcmp(curr->key, key) == 0) {
            // Key found, delete node and return
            if (prev == NULL) {
                table->table[index] = curr->next;
            } else {
                prev->next = curr->next;
                }
    printf("Key: %s, Value: %s deleted", curr->key, curr->value);
    free(curr);
    return;
    }
    prev = curr;
    curr = curr->next;
    }

    // Key not found
    return;
}
int main() {
    // Create hash table
    HashTable *table = newHashTable(5);
    // Insert elements into hash table
    insert(table, "apple", "red");
    insert(table, "banana", "yellow");
    insert(table, "grape", "purple");
    insert(table, "strawberry", "red");
    insert(table, "watermelon", "green");

    // Search for element in hash table
    char *value = search(table, "banana");
    if (value) {
        printf("Key: banana, Value: %s\n", value);
    } else {
        printf("Key not found\n");
    }

    // Delete element from hash table
    delete(table, "banana");

    // Search for element in hash table
    value = search(table, "banana");
    if (value) {
        printf("Key: banana, Value: %s\n", value);
    } else {
        printf("\nKey not found\n");
    }

    return 0;
}