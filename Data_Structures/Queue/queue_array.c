#include <stdio.h>
#include <stdlib.h>

struct Queue{
    int size;
    int start;
    int end;
    int *A; //array to store the queue
};

typedef struct Queue Q;


void initialize(Q *q, int size){
    q->size = size;
    q->start = q->end = -1;
    q->A = (int *)malloc(q->size * sizeof(int));
}

void enqueue(Q *q, int x){
    if(q->end == q->size-1)
        printf("\n**Queue is full, elements not added**\n");
    else{
        q->end++;
        q->A[q->end] = x;
    }
}

int dequeue(Q *q){
    int x = -1;
    if(q->start == q->end)
        printf("Queue is empty\n");
    else{
        q->start++;
        x = q->A[q->start];
    }
    return x;
}

void show(Q q){
    int i;
    for(i=q.start+1; i<=q.end; i++)
        printf("%d ", q.A[i]);
    printf("\n");
}

int main(){
    Q q;
    initialize(&q, 5);
    enqueue(&q, 14);
    enqueue(&q, 55);
    enqueue(&q, 6);
    enqueue(&q, 12);
    enqueue(&q, 53);
    //push(&q, 0);

    show(q);

    dequeue(&q);
    dequeue(&q);
    show(q);

    return 0;
}