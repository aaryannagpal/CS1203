#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX 100
#define TABLE_SIZE 10

typedef struct Hash_Node {
    char name[MAX];
    int age;
    struct Hash_Node *next;    
}Hash_Node;

Hash_Node * hash_table[TABLE_SIZE];

unsigned int hash(char *name){
    unsigned int hash = 0;
    int c;
    //char* name = node.name;

    while(c = *name++){
        hash = c + (hash << 6) + (hash << 16) - hash; //change the hash function
    }
    return hash % TABLE_SIZE;
}

void make_hash(){
    for (int i = 0; i < TABLE_SIZE; i++){
        hash_table[i] = NULL; //make an empty table
    }
}

void print_table(){
    for (int i = 0; i < TABLE_SIZE; i++){
        if (hash_table[i] == NULL){
            printf("\t%i\t---\n", i);
        }else {
            printf("\t%i\t", i);
            Hash_Node *temp = hash_table[i];
            while (temp != NULL){
                printf("%s->", temp->name);
                temp = temp->next;
            }
            printf("\n\n");
        }
    }
}

bool insert(Hash_Node *p){
    if (p == NULL){
        return false;
    }
    int index = hash(p->name);
    p->next = hash_table[index];
    hash_table[index] = p;
    return true;
}

void * search(char *name){
    int index = hash(name);
    int pos = 1;
    Hash_Node *temp = hash_table[index];
    for (int i = 0; temp != NULL && i < TABLE_SIZE; i++){
        if (strcmp(temp->name, name) == 0){
            printf("Found %s at index %i of the h, at position %i \n", name, index, pos);
            break;
        }
        else{
            temp = temp->next;
            pos++;
        }
    if (temp == NULL){
        printf("Not found\n");
    }
    // }
  }  // while(temp != NULL && strncmp(temp->name, name, MAX) != 0){
    //     temp = temp->next;
    //     pos++;
    //     }
    // printf("'%s' is at Index %d in the table and %dth position in that index\n\n",name, index,pos);//, temp->next;
}

Hash_Node * delete(char *name){
    int index = hash(name);
    Hash_Node *temp = hash_table[index];
    Hash_Node *prev = NULL;
    while(temp != NULL && strncmp(temp->name, name, MAX) != 0){
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
    Hash_Node X = {.name ="Xzxcvb", .age = 20};
    Hash_Node Y = {.name ="Ydfgdes", .age = 20};
    Hash_Node Z = {.name ="Zvbnbvc", .age = 20};
    Hash_Node A = {.name ="Afgfdsf", .age = 20};
    Hash_Node B = {.name ="Bsdfdgfd", .age = 20};
    Hash_Node C = {.name ="Cfgtrddf", .age = 20};
    Hash_Node D = {.name ="Dfdgfhjhfc", .age = 20};
    Hash_Node E = {.name ="Edgftff", .age = 20};
    Hash_Node F = {.name ="Frt654refg", .age = 20};
    Hash_Node G = {.name ="Gghjkjhgf", .age = 20};
    Hash_Node H = {.name ="Hfghjytfg", .age = 20};
    Hash_Node I = {.name ="Idrhsrxggd", .age = 20};


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
    


    search("X");
    print_table();
    search("Idrhsrxggd");

    //print_table();
    return 0;
}