#include <stdio.h>
#include <stdlib.h>

int main(){
    int *p = (int *)malloc(sizeof(int)); p = NULL;
    printf("%d", *p);
    return 0;
}


//code will not compile as p is not freed and causes a memory leak 

