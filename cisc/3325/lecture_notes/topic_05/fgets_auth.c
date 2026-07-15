// A C program that reads a name (string) from
//     the keyboard. If the name begins with 'A'
//     the program will authenticate the user.
// This program doesn't feature a buffer overflow
//     because the fgets() function accepts a
//     string of only up to 30 characters long.

#include <stdio.h> // For printf() & fgets().

// Constant storing the size of the char array:
const unsigned short SIZE = 30;

int main (void)
{
    // Character array (string) that will
    //    store the user's name.
    unsigned char name[SIZE];
    // Flag telling if the user is authenticated:
    int flag = 0;

    printf("Please enter your name here: >> ");

    // Reading the user's input with fgets():
    fgets(name, SIZE, stdin);

    // Checking if the user's name starts with 'A',
    //    or if the flag is non-zero:
    if (name[0] == 'A' || name[0] == 'a' || flag)
    {
        printf("Congrats! You are authenticated!\n");
    }
    else
    {
        printf("Sorry, we couldn't authenticate you.\n");
    }

    return 0;
}
