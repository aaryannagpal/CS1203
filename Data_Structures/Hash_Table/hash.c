#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX 100
#define TABLE_SIZE 5

typedef struct Hash_Node {
    char data_char[MAX];
    int data;
    struct Hash_Node *next;    
}Hash_Node;

Hash_Node * hash_table[TABLE_SIZE];

// unsigned int hash(char *data_char){
//     unsigned int hash = 0;

//     int c;
//     while(c = *data_char++){
//         hash = c + (hash << 6) + (hash << 16) - hash; //change the hash function
//     }
//     return hash % TABLE_SIZE;
// }

void make_hash(){
    for (int i = 0; i < TABLE_SIZE; i++){
        hash_table[i] = NULL; //make an empty table
    }
}

unsigned int hash(char *data_char) {
    int length = strnlen(data_char, MAX); //getting the length of the string till MAX
    unsigned int hash_value = 0;
    for (int i = 0; i < length; i++) {
        hash_value += data_char[i];
        hash_value *= data_char[i];
    }
    return hash_value % TABLE_SIZE;
}

void print_table(){
    for (int i = 0; i < TABLE_SIZE; i++){
        if (hash_table[i] == NULL){
            printf("\t%i\t---\n", i);
        }else {
            printf("\t%i\t", i);
            Hash_Node *temp = hash_table[i];
            while (temp != NULL){
                printf("%s->", temp->data_char);
                temp = temp->next;
            }
            printf("\n");
        }
    }
}

bool insert(Hash_Node *p){
    if (p == NULL){
        return false;
    }
    int index = hash(p->data_char);
    p->next = hash_table[index];
    hash_table[index] = p;
    return true;
}

Hash_Node * search(char *data_char){
    int index = hash(data_char);
    Hash_Node *temp = hash_table[index];
    while(temp != NULL && strncmp(temp->data_char, data_char, MAX) != 0){
        temp = temp->next;
        }
    return index;//, temp->next;

}

Hash_Node * delete(char *data_char){
    int index = hash(data_char);
    Hash_Node *temp = hash_table[index];
    Hash_Node *prev = NULL;
    while(temp != NULL && strncmp(temp->data_char, data_char, MAX) != 0){
        prev = temp;
        temp = temp->next;
        }
    if (temp == NULL){
        return NULL;
    }
    if (prev == NULL){
        hash_table[index] = temp->next;
    }
    else {
        prev->next = temp->next;
    }
    return temp;
}

int main(){
    make_hash();
    Hash_Node X = {.data_char ="X", .data = 20};
    Hash_Node Y = {.data_char ="Y", .data = 20};
    Hash_Node Z = {.data_char ="Z", .data = 20};
    Hash_Node A = {.data_char ="A", .data = 20};
    Hash_Node B = {.data_char ="B", .data = 20};
    Hash_Node C = {.data_char ="C", .data = 20};
    Hash_Node D = {.data_char ="D", .data = 20};
    Hash_Node E = {.data_char ="E", .data = 20};
    Hash_Node F = {.data_char ="F", .data = 20};
    Hash_Node G = {.data_char ="G", .data = 20};
    Hash_Node H = {.data_char ="H", .data = 20};
    Hash_Node I = {.data_char ="I", .data = 20};
    Hash_Node J = {.data_char ="J", .data = 20};
    Hash_Node K = {.data_char ="K", .data = 20};
    Hash_Node L = {.data_char ="L", .data = 20};
    Hash_Node M = {.data_char ="M", .data = 20};
    Hash_Node N = {.data_char ="N", .data = 20};
    Hash_Node O = {.data_char ="O", .data = 20};
    Hash_Node P = {.data_char ="P", .data = 20};
    Hash_Node Q = {.data_char ="Q", .data = 20};
    Hash_Node R = {.data_char ="R", .data = 20};
    Hash_Node S = {.data_char ="S", .data = 20};
    Hash_Node T = {.data_char ="T", .data = 20};
    Hash_Node U = {.data_char ="U", .data = 20};
    Hash_Node V = {.data_char ="V", .data = 20};
    Hash_Node W = {.data_char ="W", .data = 20};


    insert(&X);
    insert(&Y);
    insert(&Z);
    insert(&A);
    insert(&B);
    insert(&C);
    insert(&D);
    insert(&E);
    insert(&F);
    insert(&G);
    insert(&H);
    insert(&I);
    insert(&J);
    insert(&K);
    insert(&L);
    insert(&M);
    insert(&N);
    insert(&O);
    insert(&P);
    insert(&Q);
    insert(&R);
    insert(&S);
    insert(&T);
    insert(&U);
    insert(&V);
    insert(&W);
    search("X");
    print_table();

    //print_table();
    return 0;
}