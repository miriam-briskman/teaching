// A C program that reads a name (string) from
//     the keyboard. If the name begins with 'A'
//     the program will authenticate the user.
// This program, however, has a buffer overflow
//     bug: if the user enters a string longer
//     than 30 characters, the authentication
//     flag variable, which is initialized to
//     0, may be overflown with a number other
//     than 0, thus authenticating the user,
//     even when the name doesn't begin with 'A'.

#include <stdio.h> // For printf() & gets().

int main (void)
{
    // Character array (string) that will
    //    store the user's name.
    unsigned char name[30];
    // Flag telling if the user is authenticated:
    int flag = 0;

    printf("Please enter your name here: >> ");

    // Reading the user's input with gets():
    gets(name);

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
