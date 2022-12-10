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
void KMP(char *text, char *pattern)
{
    int i = 0, j = 0;
    int textLen = strlen(text);
    int patLen = strlen(pattern);
    int T[patLen];

    // build the KMP table
    buildKMPTable(T, pattern);

    // search for pattern in the text
    while (i < textLen)
    {
        while (j >= 0 && text[i] != pattern[j])
        {
            j = T[j];
        }

        i++;
        j++;

        if (j == patLen)
        {
            printf("Found pattern at index %d\n", i - j);
            j = T[j];
        }
    }
}

// main function
int main()
{
    char text[] = "AARYAN IS AARYAN";
    char pattern[] = "AARYAN";

    KMP(text, pattern);

    return 0;
}
