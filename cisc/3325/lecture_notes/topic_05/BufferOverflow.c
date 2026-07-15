// A C program that creates an array of characters
//     of size 10 elements, but proceeds to access
//     40 bytes.

#include <stdio.h> // For the printf() function.

int main (void)
{
    // Creating the array of unsigned characters
    //    (The numeric value of each of the
    //    characters is in the range 0-255):
    unsigned char my_characters[10];

    int i;
    // Populating the array with "ABCDEFGHIJ":
    for (i = 0; i <= 9; i++)
    {
         my_characters[i] = 'A' + i;
    }

    // Printing 40 memory locations starting at
    //    my_characters[0] to the screen:
    for (i = 0; i <= 39; i++)
    {
         printf("%c (Numeric value of character: %d)\n",
                my_characters[i], my_characters[i]);
    }

    printf("Done!\n");

    return 0;
}
