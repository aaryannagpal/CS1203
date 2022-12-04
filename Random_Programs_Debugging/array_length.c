#include <stdio.h>
#include <stdlib.h>


int main(){
    int A[10] = {0,1,2,3,4,5,6,7,8,9};
    int *p = (int*)malloc(10*sizeof(int));
    printf("%d\n", A[10]);
    printf("%d\n", p[13]);
}

//does not give desired value