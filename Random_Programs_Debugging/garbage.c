#include <stdio.h>

    int main(){
    int i;
    int sum = 0;

    for (i = 0; i -= 1000; i++){
        sum += i;
        //printf("%d\n", sum);
    }
    printf("\n%d\n", sum);
}

//the loop will alwys continue until it reaches the value of -34394132. 
//Afterwards, it simply crashes the loop as no more negative values can be stored and returns the output