#include <stdio.h>
#include <string.h>

// Function to build the KMP table
void buildKMPTable(int *T, char *pattern)
{
    int i = 0, j = -1;
    T[i] = j;

    while (i < strlen(pattern))
    {
        while (j >= 0 && pattern[i] != pattern[j])
        {
            j = T[j];
        }

        i++;
        j++;

        T[i] = j;
    }
}

// Function to search for a pattern in a given text using KMP algorithm
int KMP(char *str, char *substring)
{
    int i = 0, j = 0;
    int textLen = strlen(str);
    int patLen = strlen(substring);
    int T[patLen];

    // build the KMP table
    buildKMPTable(T, substring);

    // search for pattern in the text
    while (i < textLen)
    {
        while (j >= 0 && str[i] != substring[j])
        {
            j = T[j];
        }

        i++;
        j++;

        if (j == patLen)
        {
            int k = i - j;
            j = T[j];
            return k;
        }
    }
    return -1;
}
// int main(){
//     char text[] = "Hello World! This is a sample text for testing the Rabin-Karp Algorithm.";
//     char pattern[] = "Rabin-Kar";
//     printf("%d",KMP(text, pattern));
//     return 0;
// }