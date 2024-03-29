#include<stdio.h>
#include<string.h>

//Function to calculate the hash value of a string
int calculateHash(char* str, int len){
    int hash = 0;
    for(int i=0; i<len; i++)
    hash += str[i]*(i+1);
    return hash;
}

//Function to search for a given string in the main text using Rabin-Karp Algorithm
int search(char* text, char* pattern){
    int textLen = strlen(text);
    int patLen = strlen(pattern);
    //Flag to check for exact match
    int match = 0;

    //Calculate the hash value of the pattern
    int patHash = calculateHash(pattern, patLen);

    //Iterate through the main text and compare the hash values of the pattern and the substrings of the same length as the pattern
    for(int i=0; i<=textLen-patLen; i++){
        
        //Calculate the hash value of the current substring of the main text
        int subHash = calculateHash(text+i, patLen);

        //If the hash value matches, check for the exact string match
        if(subHash == patHash){

            //Check for exact string match
            for(int j=0; j<patLen; j++){
                if(text[i+j] != pattern[j])
                {
                    match = 0;
                    //printf("Pattern not found\n");
                    //return match;
                }
                else{
                    match = 1;
                }
            }

            //If exact match found, print the index of the starting position of the pattern in the main text
            // if(match){
            //     //printf("Pattern found at index %d\n", i);
            //     return match;
            // }
            // else{
            //     printf("Pattern Not found");
            //     return;
            // }
        }
        // else{
        //     printf("Pattern not found\n");
        // }
    }
    return match;
}

int main()
{
//Sample main text and pattern
char text[] = "Hello World! This is a sample text for testing the Rabin-Karp Algorithm.";
char pattern[] = "Rabin-Kar";

printf("%d\n",search(text, pattern));
return 0;
}