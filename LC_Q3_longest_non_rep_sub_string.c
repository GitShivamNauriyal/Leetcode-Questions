#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int repChar(char *a, char *b)
{
    char *u, *s, *t;
    s = a;
    t = b;
    while (s < t)
    {
        u = s;
        while (u < t)
        {
            if (*u == *t)
            {
                // printf("rep = %c\n", *u);
                return 1;
            }
            u++;
        }
        s++;
    }
    return 0;
}

int lengthOfLongestSubstring(char *s)
{
    int max = 0, cnt = 1;
    char *t;
    if (*s == '\0')
        return 0;
    t = s;
    while (*s != '\0')
    {
        while (*t != '\0')
        {
            // printf("==%c - %c\n", *s, *t);
            if (repChar(s, t))
            {
                // printf("br: %c\n", *s);
                break;
            }
            // printf("(%d) - (%d)\n", s, t);
            cnt = t - s + 1;
            // printf("--%d\n", cnt);
            t++;
            if (cnt > max)
                max = cnt;
        }
        s++;
    }

    return max;
}

int main(void)
{
    char s[100];
    int i = 0;
    printf("Enter string: ");
    scanf("%[^\n]s", s);
    printf("%d\n", strlen(s));
    // while (s[i] != '\0')
    // {
    //     printf("%c", s[i]);
    //     i++;
    // }
    // printf("\n");
    int max = lengthOfLongestSubstring(s);
    printf("\nMax length = %d", max);
}