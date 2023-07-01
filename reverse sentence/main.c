#include <stdio.h>

void reverse();

void main()
{
    printf("Please enter a sentence: ");
    reverse();
}

void reverse()
{
    char c;
    scanf("%c", &c);
    if (c != '\n') {
        reverse();
        printf("%c", c);
    }
}
