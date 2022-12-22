# Final Project
<b>Project Name:</b> Word Search Game <br>
<b>Course:</b> Data Structures CS-1203<br>
<b>Course Instructor:</b> Debayan Gupta<br>
<b>Made By: </b> Aaryan Nagpal

## Idea
A word search game is implemented using C language here. There are 3 algorithms that are involved in searching the word in the grid. The algorithms are:
1. Brute Force String Search
2. Knuth Morris Pratt String Matching Algorithm
3. Rabbin Karp Algorithm

## Functioning
The program has a ready-made puzzle form of a grid and the word to be searched. The grid is a 2D array of characters and the word is a string. <br> The program first converts every row, column and diagonal iteratively into a string and then searches the word in that particular string using the 3 algorithms mentioned above. The program then prints the location of the word for each instance of the word found in the grid and the time taken by each algorithm to search the word.

## Algorithms
### Brute Force String Search
The brute force string search algorithm is the simplest algorithm to search a word in a string. It compares the first character of the word with the first character of the string. If they match, it compares the next character of the word with the next character of the string and so on. If the word is found, the index of the first character of the word in the string is returned. If the word is not found, -1 is returned. <br>

### Knuth Morris Pratt String Matching Algorithm
The Knuth Morris Pratt string matching algorithm is a linear time algorithm to search a word in a string. It uses a partial match table to search the word in the string. The partial match table is an array of integers that stores the length of the longest proper prefix of the word that is also a suffix of the word. The algorithm first compares the first character of the word with the first character of the string. If they match, it compares the next character of the word with the next character of the string and so on. If the word is found, the index of the first character of the word in the string is returned. If the word is not found, -1 is returned. <br>

### Rabbin Karp Algorithm
The Rabbin Karp algorithm is a linear time algorithm to search a word in a string. It uses a hash function to search the word in the string. The hash function is a function that maps a string to a number. The algorithm first calculates the hash value of the word and the first substring of the string of the same length as the word. If the hash values match, it compares the word with the substring. If they match, the index of the first character of the word in the string is returned. If the word is not found, -1 is returned. <br>

## How to Run
1. Run the program in any C compiler and enter the word to be searched.
2. The program will print the locations of the word in the grid for each instance of the word found in the grid and the time taken by each algorithm to search the word.
The grid looks like this:
```
                    R       U       N       A       R       O       U       N       D       D       L

                    E       D       C       I       T       O       A       H       C       Y       V

                    Z       Y       U       W       S       W       E       D       Z       Y       A

                    A       K       O       T       C       O       N       V       O       Y       V

                    L       S       B       O       S       E       V       R       U       C       I

                    B       O       B       L       L       C       G       L       P       B       D

                    L       K       T       E       E       N       A       G       E       D       L

                    I       S       T       R       E       W       Z       L       C       G       Y

                    A       U       R       A       P       L       E       B       A       Y       G

                    R       D       A       T       Y       T       B       I       W       R       A

                    T       E       Y       E       M       R       O       F       I       N       U
```
Some sample inputs: 
- Run
- Scalar
- Runaround
- Curves
- Tolerate
- Tray

## Output
Sample Output for the word 'Scalar':  
```
Enter a word: Scalar

(4, 4)(5, 5)(6, 6)(7, 7)(8, 8)(9, 9)
KMP:
(4, 4)(5, 5)(6, 6)(7, 7)(8, 8)(9, 9)
Rabin Karp:
(4, 4)(5, 5)(6, 6)(7, 7)(8, 8)(9, 9)

Time taken by Brute Force: 0.000001000000000 seconds
Time taken by KMP: 0.000001000000000 seconds
Time taken by Rabin Karp: 0.000000000000000 seconds
```
If the word is not found in the grid, the output will be:
```
Enter a word: Hello

Brute Force:
KMP:
Rabin Karp:

Time taken by Brute Force: 0.000001000000000 seconds
Time taken by KMP: 0.000001000000000 seconds
Time taken by Rabin Karp: 0.000001000000000 seconds
```
## Constraints
1. The word to be searched must be a string.
2. The word to be searched must be of length 3 or more. (The program will work for any length size, but there might be some instabilities in the program for such strings.)
3. The word to be searched must be in the grid in a straight line (either horizontally, vertically or diagonally).

## Additional Information
1. The program is NOT case sensitive.
2. The program is space sensitive.
3. The program is punctuation sensitive.
4. The program is NOT word sensitive. (For example, if the word to be searched is 'run', the program will not find the word 'running' in the grid.)
5. The program is NOT character sensitive. (For example, if the word to be searched is 'run', the program will not find the word 'runn' in the grid.)