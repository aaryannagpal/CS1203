#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Knuth-Morris-Pratt.c"
#include "Rabin-KarpV2.c"

#define WORDSIZE 15

char *reverse_string(char a[]){
    int size = strlen(a);
    char *b = malloc(sizeof(char) * size);
    for (int i = 0; i < size; i++){
        b[i] = a[size - i - 1];
    }
    return b;
}

int upper(char c){
    if (c >= 'a' && c <= 'z'){
        return c - 'a' + 'A';
    }
    return c;
}

// make all the letters in a string uppercase
char *upper_string(char a[]){
    int len = strlen(a);
    char *b = malloc(sizeof(char) * len);

    for (int i = 0; i < len; i++){
        b[i] = upper(a[i]);
    }
    //return only till the length of the string
    return b;
}       

int inString_Brute(char *a, char *b){
    int size = strlen(a);
    int size2 = strlen(b);

    for (int i = 0; i < size; i++){
        if (a[i] == b[0]){
            int j = 0;
            while (j < size2){
                if (a[i+j] != b[j]){
                    break;
                }
                j++;
            }
            if (j == size2){
                return i; //return the index of the first letter of the substring
            }
        }
    }
    return -1;
}


void grid_display(char *puzzle[], int len){ //function to display the puzzle in a grid
    int size = strlen(puzzle[0]);
    for (int i = 0; i < len; i++){
        for (int j = 0; j < size; j++){
            printf("%c\t", upper(puzzle[i][j]));
        }
        printf("\n\n");
    }
}



double measure_time(void (*func)) {
  clock_t start, end;
  double elapsed;

  start = clock();
  
  end = clock();

  elapsed = (double)(end - start) / CLOCKS_PER_SEC;
  return elapsed;
}


void *get_positions_brute_force(char *puzzle[], int puzzle_len, char *word){

    int x, y;

    //convert all the letters in the word to uppercase
    int wordsize = strlen(word);
    word = upper_string(word);
    int size = strlen(puzzle[0]);

    //row-wise search
    for (int j = 0; j < puzzle_len; j++){
        char *row = upper_string(puzzle[j]);

        int i = inString_Brute(row, word); //check if the word is in the row
        if (i >= 0){ //if the word is found in the row
            for (int k = 0; k < wordsize; k++){ //add the coordinates of the word to the position
                x = i + k;
                y = j;
                printf("(%d, %d)", x, y);
            }
            printf("\n");
        }

        char *reversed_word = reverse_string(word);
        int l = inString_Brute(row, reversed_word) ;
        
        i = inString_Brute(row, word);
        
        if (l>= 0 && strcmp(word, reversed_word) != 0){ //if the word is found in the row

            for (int k = wordsize; k > 0; k--){ //add the coordinates of the word to the position
                x = l + k - 1;//account for the offset
                y = j;

                printf("(%d, %d)", x, y);
            }
            printf("\n");
        }
        free (row);
        
    }


    //column-wise search
    for (int j = 0; j < puzzle_len; j++){
        char *col = malloc(sizeof(char) * puzzle_len);
        for (int i = 0; i < puzzle_len; i++){
            col[i] = puzzle[i][j];
        }
        col = upper_string(col);

        int i = inString_Brute(col, word);
        if (i >= 0){ //if the word is found in the column
            for (int k = 0; k < wordsize; k++){ //add the coordinates of the word to the position
                x = j;
                y = i + k;
                printf("(%d, %d)", x, y);
            }
            printf("\n");   
        }
        char *reversed_word = reverse_string(word);
        int l = inString_Brute(col, reversed_word) ;
        
        i = inString_Brute(col, word);
        
        if (l>= 0 && strcmp(word, reversed_word) != 0){ //if the word is found in the row

            for (int k = wordsize; k > 0; k--){ //add the coordinates of the word to the position
                x = j;//
                y = l + k - 1; //account for the offset
                
                printf("(%d, %d)", x, y);
            }
            printf("\n");
        }
        free (col);
    }

    //diagnoal-wise search (top half of right to left diagonal)

    //======BUGGY REGION=========

    //========SOMETIMES RETURNS SOMETIMES DOES NOT================
    for (int i = 0; i < puzzle_len-1; i++){
        char *diag = malloc(sizeof(char) * puzzle_len);
        int pointer_y = i;
        int pointer_x = 0;

        while (pointer_y >= 0){
            diag[pointer_y] = puzzle[pointer_x][pointer_y];
            pointer_y--;
            pointer_x++;
        }
        diag = reverse_string(diag); //something wrong here

        diag = upper_string(diag); // or here
        int j = inString_Brute(diag, word); // that is causing no results here
        if (j >= 0){
            for (int k = 0; k < wordsize; k++){ //add the coordinates of the word to the position
                y = j + k;
                x = i - k - j;
                printf("(%d, %d)", x, y);
            }
            printf("\n");
            printf("%s\n", diag);
        };
        char *reversed_word = reverse_string(word); //reverse the word
        int l = inString_Brute(diag, reversed_word);

        j = inString_Brute(diag, word)+1; //add one to the index to account for the reversed word
        if (l >= 0 && strcmp(reversed_word, word) != 0){ //if the reversed word is found in the diagonal

            for (int k = wordsize; k > 0; k--){ //add the coordinates of the word to the position
                y = j + k + 1;
                x = i - k + j - 1;
                printf("(%d, %d)", x, y);
            }
            printf("\n");
        }
        free(diag);
    }

    //diagnoal-wise search (bottom half of right to left diagonal)
    
    for (int i = 0; i < puzzle_len; i++){
        char *diag2 = malloc(sizeof(char) * puzzle_len);
        int pointer_y = puzzle_len - 1;
        int pointer_x = i;
        int diag_pointer = 0;
        while (pointer_y >= 0 && pointer_x < puzzle_len){
            diag2[diag_pointer] = puzzle[pointer_x][pointer_y];
            pointer_y--;
            pointer_x++;
            diag_pointer++;
        }

        diag2 = upper_string(diag2);
        int j = inString_Brute(diag2, word);
        if (j >= 0){
            for (int k = 0; k < wordsize; k++){ //add the coordinates of the word to the position
                x = puzzle_len - 1 - (k+j);
                y = i + j + k;
                printf("(%d, %d)", x, y);
            }
            printf("\n");
        }
        char *reversed_word = reverse_string(word); //reverse the word
        int l = inString_Brute(diag2, reversed_word);
        j = inString_Brute(diag2, word); //add one to the index to account for the reversed word
        if (l >= 0 && strcmp(reversed_word, word) != 0){ //if the reversed word is found in the diagonal

            for (int k = wordsize; k > 0; k--){ //add the coordinates of the word to the position
                x = puzzle_len - 1 - (k+l-1);
                y = i + l - 1 + k ;
                printf("(%d, %d)", x, y);
            }
            printf("\n");
        }
        free(diag2);

    }

    //diagnoal-wise search (top half of left to right diagonal)
    
    for (int i = 0; i < puzzle_len; i++){
        char *diag3 = malloc(sizeof(char) * puzzle_len);
        int pointer_y = i;
        int pointer_x = 0;
        int diag_pointer = 0;
        while (pointer_y < puzzle_len){
            diag3[diag_pointer] = puzzle[pointer_x][pointer_y];
            pointer_y++;
            pointer_x++;
            diag_pointer++;
        }

        diag3 = upper_string(diag3);
        int j = inString_Brute(diag3, word);
        if (j >= 0){
            for (int k = 0; k < wordsize; k++){ //add the coordinates of the word to the position
                y = j + k;
                x = i + k + j;
                printf("(%d, %d)", x, y);
            }
            printf("\n");
        }
        char *reversed_word = reverse_string(word); //reverse the word
        int l =  inString_Brute(diag3, reversed_word);
        j = inString_Brute(diag3, word); //add one to the index to account for the reversed word
        if (l >= 0 && strcmp(reversed_word, word) != 0){
            for (int k = wordsize; k > 0; k--){ //add the coordinates of the word to the position
                x = k + j + l + i;
                y = j + k + l;
                printf("(%d, %d)", x, y);
            }
            printf("\n");
            
        }
        free(diag3);

    }

    //diagnoal-wise search (bottom half of left to right diagonal)
    
    for (int i = 1; i < puzzle_len; i++){
        char *diag4 = malloc(sizeof(char) * puzzle_len);
        int pointer_y = 0;
        int pointer_x = i;
        int diag_pointer = 0;
        while (pointer_y < puzzle_len && pointer_x < puzzle_len){
            diag4[diag_pointer] = puzzle[pointer_x][pointer_y];
            pointer_y++;
            pointer_x++;
            diag_pointer++;
        }

        diag4 = upper_string(diag4);
        int j = inString_Brute(diag4, word);
        if (j >= 0){
            for (int k = 0; k < wordsize; k++){ //add the coordinates of the word to the position
                x = j + k;
                y = i + j + k;
                printf("(%d, %d)", x, y);
            }
            
            printf("\n");
        }
        char *reversed_word = reverse_string(word); //reverse the word
        int l = inString_Brute(diag4, reversed_word);
        j = inString_Brute(diag4, word); //add one to the index to account for the reversed word
        if (l >= 0 && strcmp(reversed_word, word) != 0){
            for (int k = wordsize; k > 0; k--){ //add the coordinates of the word to the position
                y = k + j + l + i;
                x = j + k + l;
                printf("(%d, %d)", x, y);
            }
            printf("\n");
        }
        free(diag4);

    }
}

void *get_positions_kmp(char *puzzle[], int puzzle_len, char *word){

    int x, y;

    //convert all the letters in the word to uppercase
    int wordsize = strlen(word);
    int size = strlen(puzzle[0]);

    //row-wise search
    for (int j = 0; j < puzzle_len; j++){
        char *row = upper_string(puzzle[j]);

        int i = KMP(row, word); //check if the word is in the row
        if (i >= 0){ //if the word is found in the row
            for (int k = 0; k < wordsize; k++){ //add the coordinates of the word to the position
                x = i + k;
                y = j;
                printf("(%d, %d)", x, y);
            }
            printf("\n");
        }

        char *reversed_word = reverse_string(word);
        int l = KMP(row, reversed_word) ;
        
        i = KMP(row, word);
        
        if (l>= 0 && strcmp(word, reversed_word) != 0){ //if the word is found in the row

            for (int k = wordsize; k > 0; k--){ //add the coordinates of the word to the position
                x = l + k - 1;//account for the offset
                y = j;

                printf("(%d, %d)", x, y);
            }
            printf("\n");
        }
        free (row);
        
    }


    //column-wise search
    for (int j = 0; j < puzzle_len; j++){
        char *col = malloc(sizeof(char) * puzzle_len);
        for (int i = 0; i < puzzle_len; i++){
            col[i] = puzzle[i][j];
        }
        col = upper_string(col);

        int i = KMP(col, word);
        if (i >= 0){ //if the word is found in the column
            for (int k = 0; k < wordsize; k++){ //add the coordinates of the word to the position
                x = j;
                y = i + k;
                printf("(%d, %d)", x, y);
            }
            printf("\n");   
        }
        char *reversed_word = reverse_string(word);
        int l = KMP(col, reversed_word) ;
        
        i = KMP(col, word);
        
        if (l>= 0 && strcmp(word, reversed_word) != 0){ //if the word is found in the row

            for (int k = wordsize; k > 0; k--){ //add the coordinates of the word to the position
                x = j;//
                y = l + k - 1; //account for the offset
                
                printf("(%d, %d)", x, y);
            }
            printf("\n");
        }
        free (col);
    }

    //diagnoal-wise search (top half of right to left diagonal)
    for (int i = 0; i < puzzle_len-1; i++){
        char *diag = malloc(sizeof(char) * puzzle_len);
        int pointer_y = i;
        int pointer_x = 0;

        while (pointer_y >= 0){
            diag[pointer_y] = puzzle[pointer_x][pointer_y];
            pointer_y--;
            pointer_x++;
        }

        diag = reverse_string(diag);

        diag = upper_string(diag);
        int j = KMP(diag, word);
        if (j >= 0){
            for (int k = 0; k < wordsize; k++){ //add the coordinates of the word to the position
                y = j + k;
                x = i - k - j;
                printf("(%d, %d)", x, y);
            }
            printf("\n");
        };
        char *reversed_word = reverse_string(word); //reverse the word
        int l = KMP(diag, reversed_word);

        j = KMP(diag, word)+1; //add one to the index to account for the reversed word
        if (l >= 0 && strcmp(reversed_word, word) != 0){ //if the reversed word is found in the diagonal

            for (int k = wordsize; k > 0; k--){ //add the coordinates of the word to the position
                y = j + k + 1;
                x = i - k + j - 1;
                printf("(%d, %d)", x, y);
            }
            printf("\n");
        }
        free(diag);
    }

    //diagnoal-wise search (bottom half of right to left diagonal)
    
    for (int i = 0; i < puzzle_len; i++){
        char *diag2 = malloc(sizeof(char) * puzzle_len);
        int pointer_y = puzzle_len - 1;
        int pointer_x = i;
        int diag_pointer = 0;
        while (pointer_y >= 0 && pointer_x < puzzle_len){
            diag2[diag_pointer] = puzzle[pointer_x][pointer_y];
            pointer_y--;
            pointer_x++;
            diag_pointer++;
        }

        diag2 = upper_string(diag2);
        int j = KMP(diag2, word);
        if (j >= 0){
            for (int k = 0; k < wordsize; k++){ //add the coordinates of the word to the position
                x = puzzle_len - 1 - (k+j);
                y = i + j + k;
                printf("(%d, %d)", x, y);
            }
            printf("\n");
        }
        char *reversed_word = reverse_string(word); //reverse the word
        int l = KMP(diag2, reversed_word);
        j = KMP(diag2, word); //add one to the index to account for the reversed word
        if (l >= 0 && strcmp(reversed_word, word) != 0){ //if the reversed word is found in the diagonal

            for (int k = wordsize; k > 0; k--){ //add the coordinates of the word to the position
                x = puzzle_len - 1 - (k+l-1);
                y = i + l - 1 + k ;
                printf("(%d, %d)", x, y);
            }
            printf("\n");
        }
        free(diag2);

    }

    //diagnoal-wise search (top half of left to right diagonal)
    
    for (int i = 0; i < puzzle_len; i++){
        char *diag3 = malloc(sizeof(char) * puzzle_len);
        int pointer_y = i;
        int pointer_x = 0;
        int diag_pointer = 0;
        while (pointer_y < puzzle_len){
            diag3[diag_pointer] = puzzle[pointer_x][pointer_y];
            pointer_y++;
            pointer_x++;
            diag_pointer++;
        }

        diag3 = upper_string(diag3);
        int j = KMP(diag3, word);
        if (j >= 0){
            for (int k = 0; k < wordsize; k++){ //add the coordinates of the word to the position
                y = j + k;
                x = i + k + j;
                printf("(%d, %d)", x, y);
            }
            printf("\n");
        }
        char *reversed_word = reverse_string(word); //reverse the word
        int l =  KMP(diag3, reversed_word);
        j = KMP(diag3, word); //add one to the index to account for the reversed word
        if (l >= 0 && strcmp(reversed_word, word) != 0){
            for (int k = wordsize; k > 0; k--){ //add the coordinates of the word to the position
                x = k + j + l + i;
                y = j + k + l;
                printf("(%d, %d)", x, y);
            }
            printf("\n");
            
        }
        free(diag3);

    }

    //diagnoal-wise search (bottom half of left to right diagonal)
    
    for (int i = 1; i < puzzle_len; i++){
        char *diag4 = malloc(sizeof(char) * puzzle_len);
        int pointer_y = 0;
        int pointer_x = i;
        int diag_pointer = 0;
        while (pointer_y < puzzle_len && pointer_x < puzzle_len){
            diag4[diag_pointer] = puzzle[pointer_x][pointer_y];
            pointer_y++;
            pointer_x++;
            diag_pointer++;
        }

        diag4 = upper_string(diag4);
        int j = KMP(diag4, word);
        if (j >= 0){
            for (int k = 0; k < wordsize; k++){ //add the coordinates of the word to the position
                x = j + k;
                y = i + j + k;
                printf("(%d, %d)", x, y);
            }
            
            printf("\n");
        }
        char *reversed_word = reverse_string(word); //reverse the word
        int l = KMP(diag4, reversed_word);
        j = KMP(diag4, word); //add one to the index to account for the reversed word
        if (l >= 0 && strcmp(reversed_word, word) != 0){
            for (int k = wordsize; k > 0; k--){ //add the coordinates of the word to the position
                y = k + j + l + i;
                x = j + k + l;
                printf("(%d, %d)", x, y);
            }
            printf("\n");
        }
        free(diag4);

    }
}


void *get_positions_RabinKarp(char *puzzle[], int puzzle_len, char *word){

    int x, y;

    //convert all the letters in the word to uppercase
    int wordsize = strlen(word);
    int size = strlen(puzzle[0]);

    //row-wise search
    for (int j = 0; j < puzzle_len; j++){
        char *row = upper_string(puzzle[j]);

        int i = RabinKarp(row, word); //check if the word is in the row
        if (i >= 0){ //if the word is found in the row
            for (int k = 0; k < wordsize; k++){ //add the coordinates of the word to the position
                x = i + k;
                y = j;
                printf("(%d, %d)", x, y);
            }
            printf("\n");
        }

        char *reversed_word = reverse_string(word);
        int l = RabinKarp(row, reversed_word) ;
        
        i = RabinKarp(row, word);
        
        if (l>= 0 && strcmp(word, reversed_word) != 0){ //if the word is found in the row

            for (int k = wordsize; k > 0; k--){ //add the coordinates of the word to the position
                x = l + k - 1;//account for the offset
                y = j;

                printf("(%d, %d)", x, y);
            }
            printf("\n");
        }
        free (row);
        
    }


    //column-wise search
    for (int j = 0; j < puzzle_len; j++){
        char *col = malloc(sizeof(char) * puzzle_len);
        for (int i = 0; i < puzzle_len; i++){
            col[i] = puzzle[i][j];
        }
        col = upper_string(col);

        int i = RabinKarp(col, word);
        if (i >= 0){ //if the word is found in the column
            for (int k = 0; k < wordsize; k++){ //add the coordinates of the word to the position
                x = j;
                y = i + k;
                printf("(%d, %d)", x, y);
            }
            printf("\n");   
        }
        char *reversed_word = reverse_string(word);
        int l = RabinKarp(col, reversed_word) ;
        
        i = RabinKarp(col, word);
        
        if (l>= 0 && strcmp(word, reversed_word) != 0){ //if the word is found in the row

            for (int k = wordsize; k > 0; k--){ //add the coordinates of the word to the position
                x = j;//
                y = l + k - 1; //account for the offset
                
                printf("(%d, %d)", x, y);
            }
            printf("\n");
        }
        free (col);
    }

    //diagnoal-wise search (top half of right to left diagonal)
    for (int i = 0; i < puzzle_len-1; i++){
        char *diag = malloc(sizeof(char) * puzzle_len);
        int pointer_y = i;
        int pointer_x = 0;

        while (pointer_y >= 0){
            diag[pointer_y] = puzzle[pointer_x][pointer_y];
            pointer_y--;
            pointer_x++;
        }

        diag = reverse_string(diag);

        diag = upper_string(diag);
        int j = RabinKarp(diag, word);
        if (j >= 0){
            for (int k = 0; k < wordsize; k++){ //add the coordinates of the word to the position
                y = j + k;
                x = i - k - j;
                printf("(%d, %d)", x, y);
            }
            printf("\n");
        };
        char *reversed_word = reverse_string(word); //reverse the word
        int l = RabinKarp(diag, reversed_word);

        j = RabinKarp(diag, word)+1; //add one to the index to account for the reversed word
        if (l >= 0 && strcmp(reversed_word, word) != 0){ //if the reversed word is found in the diagonal

            for (int k = wordsize; k > 0; k--){ //add the coordinates of the word to the position
                y = j + k + 1;
                x = i - k + j - 1;
                printf("(%d, %d)", x, y);
            }
            printf("\n");
        }
        free(diag);
    }

    //diagnoal-wise search (bottom half of right to left diagonal)
    
    for (int i = 0; i < puzzle_len; i++){
        char *diag2 = malloc(sizeof(char) * puzzle_len);
        int pointer_y = puzzle_len - 1;
        int pointer_x = i;
        int diag_pointer = 0;
        while (pointer_y >= 0 && pointer_x < puzzle_len){
            diag2[diag_pointer] = puzzle[pointer_x][pointer_y];
            pointer_y--;
            pointer_x++;
            diag_pointer++;
        }

        diag2 = upper_string(diag2);
        int j = RabinKarp(diag2, word);
        if (j >= 0){
            for (int k = 0; k < wordsize; k++){ //add the coordinates of the word to the position
                x = puzzle_len - 1 - (k+j);
                y = i + j + k;
                printf("(%d, %d)", x, y);
            }
            printf("\n");
        }
        char *reversed_word = reverse_string(word); //reverse the word
        int l = RabinKarp(diag2, reversed_word);
        j = RabinKarp(diag2, word); //add one to the index to account for the reversed word
        if (l >= 0 && strcmp(reversed_word, word) != 0){ //if the reversed word is found in the diagonal

            for (int k = wordsize; k > 0; k--){ //add the coordinates of the word to the position
                x = puzzle_len - 1 - (k+l-1);
                y = i + l - 1 + k ;
                printf("(%d, %d)", x, y);
            }
            printf("\n");
        }
        free(diag2);

    }

    //diagnoal-wise search (top half of left to right diagonal)
    
    for (int i = 0; i < puzzle_len; i++){
        char *diag3 = malloc(sizeof(char) * puzzle_len);
        int pointer_y = i;
        int pointer_x = 0;
        int diag_pointer = 0;
        while (pointer_y < puzzle_len){
            diag3[diag_pointer] = puzzle[pointer_x][pointer_y];
            pointer_y++;
            pointer_x++;
            diag_pointer++;
        }

        diag3 = upper_string(diag3);
        int j = RabinKarp(diag3, word);
        if (j >= 0){
            for (int k = 0; k < wordsize; k++){ //add the coordinates of the word to the position
                y = j + k;
                x = i + k + j;
                printf("(%d, %d)", x, y);
            }
            printf("\n");
        }
        char *reversed_word = reverse_string(word); //reverse the word
        int l =  RabinKarp(diag3, reversed_word);
        j = RabinKarp(diag3, word); //add one to the index to account for the reversed word
        if (l >= 0 && strcmp(reversed_word, word) != 0){
            for (int k = wordsize; k > 0; k--){ //add the coordinates of the word to the position
                x = k + j + l + i;
                y = j + k + l;
                printf("(%d, %d)", x, y);
            }
            printf("\n");
            
        }
        free(diag3);

    }

    //diagnoal-wise search (bottom half of left to right diagonal)
    
    for (int i = 1; i < puzzle_len; i++){
        char *diag4 = malloc(sizeof(char) * puzzle_len);
        int pointer_y = 0;
        int pointer_x = i;
        int diag_pointer = 0;
        while (pointer_y < puzzle_len && pointer_x < puzzle_len){
            diag4[diag_pointer] = puzzle[pointer_x][pointer_y];
            pointer_y++;
            pointer_x++;
            diag_pointer++;
        }

        diag4 = upper_string(diag4);
        int j = RabinKarp(diag4, word);
        if (j >= 0){
            for (int k = 0; k < wordsize; k++){ //add the coordinates of the word to the position
                x = j + k;
                y = i + j + k;
                printf("(%d, %d)", x, y);
            }
            
            printf("\n");
        }
        char *reversed_word = reverse_string(word); //reverse the word
        int l = RabinKarp(diag4, reversed_word);
        j = RabinKarp(diag4, word); //add one to the index to account for the reversed word
        if (l >= 0 && strcmp(reversed_word, word) != 0){
            for (int k = wordsize; k > 0; k--){ //add the coordinates of the word to the position
                y = k + j + l + i;
                x = j + k + l;
                printf("(%d, %d)", x, y);
            }
            printf("\n");
        }
        free(diag4);

    }
}




void Ready_Game(){
    char *A[] = {"RUNAROUNDDL", "EDCITOAHCYV", "ZYUWSWEDZYA", "AKOTCONVOYV",
               "LSBOSEVRUCI", "BOBLLCGLPBD", "LKTEENAGEDL", "ISTREWZLCGY",
               "AURAPLEBAYG", "RDATYTBIWRA", "TEYEMROFINU"};
    int len = sizeof(A)/sizeof(A[0]);
    grid_display(A, len);
    //printf("%d\n",valid_puzzle(A, len));
    //printf("%d\n",valid_wordlist(A, len));
    

    // char *word[] = {"scalar", "tray", "blew", "sevruc"};
    // int wordsize = sizeof(word)/sizeof(word[0]);

    char *input = malloc(sizeof(char) * 100);
    printf("Enter a word: ");
    scanf("%s", input);
    printf("\n");
    input = upper_string(input);

    //get_positions_brute_force(A, len,input);


    printf("Brute Force:\n");
    double elapsed_brute = measure_time(get_positions_brute_force(A, len, input));
    printf("KMP:\n");
    double elapsed_kmp = measure_time(get_positions_kmp(A, len, input));
    printf("Rabin Karp:\n");
    double elapsed_rabin = measure_time(get_positions_RabinKarp(A, len, input));
    printf("\nTime taken by Brute Force: %.15f seconds\n", elapsed_brute);
    printf("Time taken by KMP: %.15f seconds\n", elapsed_kmp);
    printf("Time taken by Rabin Karp: %.15f seconds\n", elapsed_rabin);

    free(input);
    


}


int main(){
    printf("Welcome to Word Search!\n");
    while(1){
        printf("Press 1 to play the game and 0 to exit!:");
        int choice;
        scanf("%d", &choice);
        if (choice == 1){
            Ready_Game();
        }
        else if (choice == 0){
            printf("Thank you. Goodbye!\n");
            break;
        }
        else{
            printf("Invalid choice!\n");
        }
    }

    return 0;
}