/*Testing the precision limit in C*/

#include <stdio.h>

int main(){
    float i;
    float a;

    /* printf("\n\nRound 1 \n");
    for (i = 0.0; i < 10.0; i+=1.0){
        printf("%.0f\n", i);
    }
    printf("\n\nRound 2 \n");
    for (i = 0.0; i < 1.0; i+=0.1){
        printf("%.1f\n", i);
    }
    printf("\n\nRound 3 \n");
    for (i = 0.0; i < 0.1; i+=0.01){
        printf("%.2f\n", i);
    }
    printf("\n\nRound 4 \n");
    for (i = 0.0; i < 0.01; i+=0.001){
        printf("%.3f\n", i);
    }
    printf("\n\nRound 5 \n");
    for (i = 0.0; i < 0.001; i+=0.0001){
        printf("%.4f\n", i);
    }
    printf("\n\nRound 6 \n");
    for (i = 0.0; i < 0.0001; i+=0.00001){
        printf("%.5f\n", i);
    }
    printf("\n\nRound 7 \n");
    for (i = 0.0; i < 0.00001; i+=0.000001){
        printf("%f\n", i);
    }
    printf("\n\nRound 8 \n");
    for (i = 0.0; i < 0.000001; i+=0.0000001){
        printf("%2f\n", i);
    }
    printf("\n\nRound 9 \n");
    for (i = 0.0; i < 0.0000001; i+=0.00000001){
        printf("%.8f\n", i);
    }
    printf("\n\nRound 10 \n");
    for (i = 0.0; i < 0.00000001; i+=0.000000001){
        printf("%.9f\n", i);
    }
    printf("\n\nMoving to Round 16 \n");
    for (i = 0.0; i < 0.00000000000001; i+=0.000000000000001){
        printf("%.15f\n", i);
    }
    printf("\n\nMoving to Round 25 \n");
    for (i = 0.0; i < 0.00000000000000000000001; i+=0.000000000000000000000001){
        printf("%.24f\n", i);
    }*/
    printf("\n\nMoving to Round 35 \n");
    for (i = 0.0; i < 0.000000000000000000000000000000001; i+=0.0000000000000000000000000000000001){
        printf("%.34f\n", i);
    }
    printf("\n\nMoving to Round 46 \n");
    for (i = 0.0; i < 10e-44; i+=10e-45){
        printf("%.45f\n", i);
    }
    printf("Our limit is till 45th decimal place.");
    return 0;
}