#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    return b;
}       

int inString_Brute(char *a, char *b){
    int size = strlen(a);
    int size2 = strlen(b);
    // int i,j;
    // for (i = 0; i < size; i++) {
    //     for (j = 0; j < size2; j++) {
    //         if (a[i + j] != b[j]) {
    //         break;
    //         }
    //     }
    //     if (j == size2) {
    //     return i;
    //     }
    // }
    //     return -1;

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

struct coordinates{
    int x;
    int y;
};

typedef struct coordinates coord;

struct positions{  
    int index;//for the size of the word 
    coord *coordinates;
};

typedef struct positions positions;

struct Locations{
    int index; //for number of occurances
    positions *positions;
};

typedef struct Locations Locations;

void print_positions(positions *pos, int len){
    printf("[");
    int i = 0;

    for (i; i < len; i++){
        printf("(%d, %d)", pos->coordinates->x, pos->coordinates->y);

        if (i < len - 1){
            printf(", ");
        }
        pos->coordinates++; 
        //pos += len;
    }
    printf("]\n");
}

void print_locations(Locations *locations){
    int len = locations->positions->index;
    
    printf("[\n");
    for (int i = 0; i < locations->index; i++){
        printf("  ");
        print_positions(locations->positions+i, len);
    }
    printf("]\n");
}

int valid_puzzle(char *a[], int len){

    int size = strlen(a[0]); //getting length of the first string

    //if the puzzle is valid, all the lengths of the strings should be the same

    for (int i = 0; i < size; i++){
        if (strlen(a[i]) != size){
            printf("The puzzle is not valid"); //if the lengths are not the same, the puzzle is not valid
            return 0;
        }
    }
    return 1;
}

int valid_wordlist(char *a[], int len){

    for (int i = 0; i < len; i++){
        if (strlen(a[i]) <= 0){
        printf("The wordlist is not valid"); //if the length of the word is less than 1, it is not a string
        return 0;
        }
    }
    return 1;
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

Locations *get_positions_brute_force(char *puzzle[], int puzzle_len, char *word){

    //convert all the letters in the word to uppercase
    int wordsize = strlen(word);
    word = upper_string(word);

    Locations *locations = malloc(sizeof(Locations));
    locations->index = 0;
    locations->positions = malloc(sizeof(positions));
    int size = strlen(puzzle[0]);

    //row-wise search
    for (int j = 0; j < puzzle_len; j++){
        char *row = upper_string(puzzle[j]);

        int i = inString_Brute(row, word); //check if the word is in the row
        if (i >= 0){ //if the word is found in the row

            positions *pos = malloc(sizeof(positions)); //create a new position

            locations->index++; //increase the number of occurances
            locations = realloc(locations, sizeof(Locations) * locations->index); //increase the size of the array of positions

            pos->index = 0; //initialize the index of the position
            pos->coordinates = malloc(sizeof(coord)); //initialize the array of coordinates

            for (int k = 0; k < wordsize; k++){ //add the coordinates of the word to the position
                pos->coordinates->x = i + k;
                pos->coordinates->y = j;
                pos->index++;

                pos->coordinates = realloc(pos->coordinates, sizeof(coord) * pos->index); //increase the size of the array of coordinates
                pos->coordinates[pos->index - 1] = *pos->coordinates; //add the coordinates to the array
                printf("(%d, %d)", pos->coordinates->x, pos->coordinates->y);
            }
            printf("\n");
            locations->positions[locations->index - 1] = *pos; //add the position to the array of positions
        }

        char *reversed_word = reverse_string(word);
        int l = inString_Brute(row, reversed_word) ;
        
        i = inString_Brute(row, word);
        
        if (l>= 0 && strcmp(word, reversed_word) != 0){ //if the word is found in the row

            positions *pos = malloc(sizeof(positions)); //create a new position

            locations->index++; //increase the number of occurances
            locations = realloc(locations, sizeof(Locations) * locations->index); //increase the size of the array of positions

            pos->index = 0; //initialize the index of the position
            pos->coordinates = malloc(sizeof(coord)); //initialize the array of coordinates
            for (int k = wordsize; k > 0; k--){ //add the coordinates of the word to the position
                pos->coordinates->x = l + k - 1;//account for the offset
                pos->coordinates->y = j;
                pos->index++;

                pos->coordinates = realloc(pos->coordinates, sizeof(coord) * pos->index); //increase the size of the array of coordinates
                pos->coordinates[pos->index - 1] = *pos->coordinates; //add the coordinates to the array
                printf("(%d, %d)", pos->coordinates->x, pos->coordinates->y);
            }
            printf("\n");
            locations->positions[locations->index - 1] = *pos; //add the position to the array of positions
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

            positions *pos = malloc(sizeof(positions)); //create a new position

            locations->index++; //increase the number of occurances
            locations = realloc(locations, sizeof(Locations) * locations->index); //increase the size of the array of positions

            pos->index = 0; //initialize the index of the position
            pos->coordinates = malloc(sizeof(coord)); //initialize the array of coordinates

            for (int k = 0; k < wordsize; k++){ //add the coordinates of the word to the position
                pos->coordinates->x = j;
                pos->coordinates->y = i + k;
                pos->index++;

                pos->coordinates = realloc(pos->coordinates, sizeof(coord) * pos->index); //increase the size of the array of coordinates
                pos->coordinates[pos->index - 1] = *pos->coordinates; //add the coordinates to the array
                printf("(%d, %d)", pos->coordinates->x, pos->coordinates->y);
            }
            printf("\n");
            locations->positions[locations->index-1] = *pos; //add the position to the array of positions
            // printf("\n\nCollected column-wise search:\n\n");
            // print_positions(locations->positions, wordsize);        

        }
        char *reversed_word = reverse_string(word);
        int l = inString_Brute(col, reversed_word) ;
        
        i = inString_Brute(col, word);
        
        if (l>= 0 && strcmp(word, reversed_word) != 0){ //if the word is found in the row

            positions *pos = malloc(sizeof(positions)); //create a new position

            locations->index++; //increase the number of occurances
            locations = realloc(locations, sizeof(Locations) * locations->index); //increase the size of the array of positions

            pos->index = 0; //initialize the index of the position
            pos->coordinates = malloc(sizeof(coord)); //initialize the array of coordinates
            for (int k = wordsize; k > 0; k--){ //add the coordinates of the word to the position
                pos->coordinates->x = j;//
                pos->coordinates->y = l + k - 1; //account for the offset
                pos->index++;

                pos->coordinates = realloc(pos->coordinates, sizeof(coord) * pos->index); //increase the size of the array of coordinates
                pos->coordinates[pos->index - 1] = *pos->coordinates; //add the coordinates to the array
                printf("(%d, %d)", pos->coordinates->x, pos->coordinates->y);
            }
            printf("\n");
            locations->positions[locations->index - 1] = *pos; //add the position to the array of positions
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

        diag = upper_string(diag);
        int j = inString_Brute(diag, word);
        if (j >= 0){
            positions *pos = malloc(sizeof(positions)); //create a new position

            locations->index++; //increase the number of occurances
            locations = realloc(locations, sizeof(Locations) * locations->index); //increase the size of the array of positions

            pos->index = 0; //initialize the index of the position
            pos->coordinates = malloc(sizeof(coord)); //initialize the array of coordinates

            for (int k = 0; k < wordsize; k++){ //add the coordinates of the word to the position
                pos->coordinates->x = j + k;
                pos->coordinates->y = i - k;
                pos->index++;

                pos->coordinates = realloc(pos->coordinates, sizeof(coord) * pos->index); //increase the size of the array of coordinates
                pos->coordinates[pos->index - 1] = *pos->coordinates; //add the coordinates to the array
                printf("(%d, %d)", pos->coordinates->x, pos->coordinates->y);
            }
            printf("\n");
            locations->positions[locations->index-1] = *pos; //add the position to the array of positions
            // printf("\n\nCollected diagnoal-wise search (top half of right to left diagonal):\n\n");
            // print_positions(locations->positions, wordsize);

        };
        char *reversed_word = reverse_string(word); //reverse the word
        int l = inString_Brute(diag, reversed_word);

        j = inString_Brute(diag, word)+1; //add one to the index to account for the reversed word
        if (l >= 0 && strcmp(reversed_word, word) != 0){ //if the reversed word is found in the diagonal
            positions *pos = malloc(sizeof(positions)); //create a new position

            locations->index++; //increase the number of occurances
            locations = realloc(locations, sizeof(Locations) * locations->index); //increase the size of the array of positions

            pos->index = 0; //initialize the index of the position
            pos->coordinates = malloc(sizeof(coord)); //initialize the array of coordinates

            for (int k = wordsize; k > 0; k--){ //add the coordinates of the word to the position
                pos->coordinates->x = j + k - 1;
                pos->coordinates->y = i - k + 1;
                pos->index++;

                pos->coordinates = realloc(pos->coordinates, sizeof(coord) * pos->index); //increase the size of the array of coordinates
                pos->coordinates[pos->index - 1] = *pos->coordinates; //add the coordinates to the array
                printf("(%d, %d)", pos->coordinates->x, pos->coordinates->y);
            }
            printf("\n");
            locations->positions[locations->index-1] = *pos; //add the position to the array of positions
            // printf("\n\nCollected diagnoal-wise search (top half of right to left diagonal):\n\n");
            // print_positions(locations->positions, wordsize);
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
            positions *pos = malloc(sizeof(positions)); //create a new position

            locations->index++; //increase the number of occurances
            locations = realloc(locations, sizeof(Locations) * locations->index); //increase the size of the array of positions

            pos->index = 0; //initialize the index of the position
            pos->coordinates = malloc(sizeof(coord)); //initialize the array of coordinates

            for (int k = 0; k < wordsize; k++){ //add the coordinates of the word to the position
                pos->coordinates->x = puzzle_len - 1 - (k+j);
                pos->coordinates->y = i + j + k;
                pos->index++;

                pos->coordinates = realloc(pos->coordinates, sizeof(coord) * pos->index); //increase the size of the array of coordinates
                pos->coordinates[pos->index - 1] = *pos->coordinates; //add the coordinates to the array
                printf("(%d, %d)", pos->coordinates->x, pos->coordinates->y);
            }
            printf("\n");
            locations->positions[locations->index-1] = *pos; //add the position to the array of positions
            // printf("\n\nCollected diagnoal-wise search (top half of right to left diagonal):\n\n");
            // print_positions(locations->positions, wordsize);

        }
        int l;
        char *reversed_word = reverse_string(word); //reverse the word
        j = inString_Brute(diag2, word)+1; //add one to the index to account for the reversed word
        if (l = inString_Brute(diag2, reversed_word)>= 0 && strcmp(reversed_word, word) != 0){ //if the reversed word is found in the diagonal
            positions *pos = malloc(sizeof(positions)); //create a new position

            locations->index++; //increase the number of occurances
            locations = realloc(locations, sizeof(Locations) * locations->index); //increase the size of the array of positions

            pos->index = 0; //initialize the index of the position
            pos->coordinates = malloc(sizeof(coord)); //initialize the array of coordinates

            for (int k = wordsize; k > 0; k--){ //add the coordinates of the word to the position
                pos->coordinates->x = puzzle_len - k + j;
                pos->coordinates->y = i + j + k-1;
                pos->index++;

                pos->coordinates = realloc(pos->coordinates, sizeof(coord) * pos->index); //increase the size of the array of coordinates
                pos->coordinates[pos->index - 1] = *pos->coordinates; //add the coordinates to the array
                printf("(%d, %d)", pos->coordinates->x, pos->coordinates->y);
            }
            printf("\n");
            locations->positions[locations->index-1] = *pos; //add the position to the array of positions
            // printf("\n\nCollected diagnoal-wise search (top half of right to left diagonal):\n\n");
            // print_positions(locations->positions, wordsize);

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
            positions *pos = malloc(sizeof(positions)); //create a new position

            locations->index++; //increase the number of occurances
            locations = realloc(locations, sizeof(Locations) * locations->index); //increase the size of the array of positions

            pos->index = 0; //initialize the index of the position
            pos->coordinates = malloc(sizeof(coord)); //initialize the array of coordinates

            for (int k = 0; k < wordsize; k++){ //add the coordinates of the word to the position
                pos->coordinates->x = k+j+i;
                pos->coordinates->y = j+k;
                pos->index++;

                pos->coordinates = realloc(pos->coordinates, sizeof(coord) * pos->index); //increase the size of the array of coordinates
                pos->coordinates[pos->index - 1] = *pos->coordinates; //add the coordinates to the array
                printf("(%d, %d)", pos->coordinates->x, pos->coordinates->y);
            }
            printf("\n");
            locations->positions[locations->index-1] = *pos; //add the position to the array of positions
            // printf("\n\nCollected diagnoal-wise search (top half of right to left diagonal):\n\n");
            // print_positions(locations->positions, wordsize);

        }
        char *reversed_word = reverse_string(word); //reverse the word
        int l =  inString_Brute(diag3, reversed_word);
        j = inString_Brute(diag3, word); //add one to the index to account for the reversed word
        if (l >= 0 && strcmp(reversed_word, word) != 0){
            positions *pos = malloc(sizeof(positions)); //create a new position

            locations->index++; //increase the number of occurances
            locations = realloc(locations, sizeof(Locations) * locations->index); //increase the size of the array of positions

            pos->index = 0; //initialize the index of the position
            pos->coordinates = malloc(sizeof(coord)); //initialize the array of coordinates

            for (int k = wordsize; k > 0; k--){ //add the coordinates of the word to the position
                pos->coordinates->x = k + j + l + i;
                pos->coordinates->y = j + k + l;
                pos->index++;

                pos->coordinates = realloc(pos->coordinates, sizeof(coord) * pos->index); //increase the size of the array of coordinates
                pos->coordinates[pos->index - 1] = *pos->coordinates; //add the coordinates to the array
                printf("(%d, %d)", pos->coordinates->x, pos->coordinates->y);
            }
            printf("\n");
            locations->positions[locations->index-1] = *pos; //add the position to the array of positions
            // printf("\n\nCollected diagnoal-wise search (top half of right to left diagonal):\n\n");
            // print_positions(locations->positions, wordsize);

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
            positions *pos = malloc(sizeof(positions)); //create a new position

            locations->index++; //increase the number of occurances
            locations = realloc(locations, sizeof(Locations) * locations->index); //increase the size of the array of positions

            pos->index = 0; //initialize the index of the position
            pos->coordinates = malloc(sizeof(coord)); //initialize the array of coordinates

            for (int k = 0; k < wordsize; k++){ //add the coordinates of the word to the position
                pos->coordinates->y = k+j+i;
                pos->coordinates->x = j+k;
                pos->index++;

                pos->coordinates = realloc(pos->coordinates, sizeof(coord) * pos->index); //increase the size of the array of coordinates
                pos->coordinates[pos->index - 1] = *pos->coordinates; //add the coordinates to the array
                printf("(%d, %d)", pos->coordinates->x, pos->coordinates->y);
            }
            printf("\n");
            locations->positions[locations->index-1] = *pos; //add the position to the array of positions
            // printf("\n\nCollected diagnoal-wise search (top half of right to left diagonal):\n\n");
            // print_positions(locations->positions, wordsize);

        }
        char *reversed_word = reverse_string(word); //reverse the word
        int l = inString_Brute(diag4, reversed_word);
        j = inString_Brute(diag4, word); //add one to the index to account for the reversed word
        if (l >= 0 && strcmp(reversed_word, word) != 0){
            positions *pos = malloc(sizeof(positions)); //create a new position

            locations->index++; //increase the number of occurances
            locations = realloc(locations, sizeof(Locations) * locations->index); //increase the size of the array of positions

            pos->index = 0; //initialize the index of the position
            pos->coordinates = malloc(sizeof(coord)); //initialize the array of coordinates

            for (int k = wordsize; k > 0; k--){ //add the coordinates of the word to the position
                pos->coordinates->y = k + j + l + i;
                pos->coordinates->x = j + k + l;
                pos->index++;

                pos->coordinates = realloc(pos->coordinates, sizeof(coord) * pos->index); //increase the size of the array of coordinates
                pos->coordinates[pos->index - 1] = *pos->coordinates; //add the coordinates to the array
                printf("(%d, %d)", pos->coordinates->x, pos->coordinates->y);
            }
            printf("\n");
            locations->positions[locations->index-1] = *pos; //add the position to the array of positions
            // printf("\n\nCollected diagnoal-wise search (top half of right to left diagonal):\n\n");
            // print_positions(locations->positions, wordsize);

        }
        free(diag4);

    }

    return locations;

}

int main(){
    //initialize list of strings
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

    Locations *locations = get_positions_brute_force(A, len,input);
    free(input);
    free(locations->positions);
    free(locations);
    


    return 0;
}