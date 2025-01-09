/*
Date:- 4 Jan 2025
Project:-
Purpose:-
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
//---------------------------HASH MAP METHOD--------------------------------//

// THIS METHOD IS WORKS BUT NOT VERY GOOD WITH TIME COMPLEXITY///////////////

//--------------------------------------------------------------------------//
bool hashMap[26][26][26];

void initializeHashMap() {
    memset(hashMap, false, sizeof(hashMap)); // Ensure all elements are set to false
}

// Function to insert into the hash map
int insertHash(char a, char b, char c) {
    int x = a - 'a'; // Map 'a' to 0, 'b' to 1, ..., 'z' to 25
    int y = b - 'a';
    int z = c - 'a';

    if (!hashMap[x][y][z]) {
        hashMap[x][y][z] = true; // Mark this combination as seen
        return 1; // Unique palindrome
    }
    return 0; // Duplicate palindrome
}

int countPalindromicSubsequence(char* s) {
    initializeHashMap(); // Ensure the hash map is correctly initialized

    int n = strlen(s);
    int pallin = 0;

    for (int i = 0; i < n - 2; i++)
    {
        for (int j = n - 1; j > i + 1; j--)
        {
            if (s[i] == s[j])
            {
                for (int k = i + 1; k < j; k++)
                {
                    pallin += insertHash(s[i], s[k], s[j]);
                }
            }
        }
    }
    return pallin;
}

*/

/*-----------------BETTER WAY---------------------------------*/
// \/\/\/\/\more complicated, try to give it some time/\/\/\/\/\/\/\/\/\/

int countPalindromicSubsequence(char *s)
{
    int n = strlen(s);
    int count = 0;
    bool hashMap[26][26] = {false}; // 2D map to store unique (first, middle) pairs

    for (char c = 'a'; c <= 'z'; c++)
    {
        int first = -1, last = -1;
        printf("%c\n", c);

        // Find the first and last occurrence of character `c`
        for (int i = 0; i < n; i++)
        {
            if (s[i] == c)
            {
                if (first == -1)
                    first = i;
                last = i;
                printf("occurence of %c: %d\n", c, i);
            }
        }

        if (first != -1 && last != -1 && first < last)
        {
            // Check characters between first and last occurrences
            for (int i = first + 1; i < last; i++)
            {
                int midChar = s[i] - 'a';
                printf("midChar: %c\n", s[i]);
                if (!hashMap[c - 'a'][midChar])
                {
                    hashMap[c - 'a'][midChar] = true;
                    count++;
                    printf("midChar Found: %c\n", s[i]);
                }
            }
        }
    }

    return count;
}

int main(void)
{
    char s[] = "bbcbabazxzxz"; // Example test case
    printf("Count of unique palindromic subsequences: %d\n", countPalindromicSubsequence(s));
    return 0;
}