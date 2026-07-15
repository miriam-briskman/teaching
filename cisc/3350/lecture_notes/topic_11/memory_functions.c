/* A program demonstrating uses of some C memory
 *    functions: malloc(), calloc(), realloc(),
 *    free(), memset(), memcpy(), and memcmp().
 *
 *    Miriam Briskman, 5/14/2023
 *    CISC 3350, Brooklyn College
 *    Licensed under CC BY-NC 4.0
 */

// For perror() and printf():
#include <stdio.h>
// For malloc(), calloc(), realloc(), and free():
#include <stdlib.h>
// For memset(), memcpy(), memcmp(), strcmp(),
//    and strncmp():
#include <string.h>

#define INI_SIZE 10
#define NEW_SIZE 20

int main ()
{
    // Allocate memory for a char array:
    char * small_A = malloc (INI_SIZE * sizeof(char));

    if (!small_A) // Same as (small_A == NULL)
    {
        perror ("malloc");
        exit (EXIT_FAILURE);
    }

    // Set small_A to contain "AAAAAAAAA":
    memset (small_A, 'A', 9);
    // Note that none of the mem functions,
    //    including memset(), returns errors.

    // Set small_A[9] to '\0':
    small_A[9] = '\0';

    // At this point, small_A will contain:
    //    AAAAAAAAA\0

    // Let's resize small_A to 20 spots:
    char * A = realloc (small_A, NEW_SIZE);
    if (!A)
    {
        perror ("realloc");
        exit (EXIT_FAILURE);
    }

    // From this point on, we'll use 'A' rather
    //    than 'small_A' since the OS might
    //    have allocated memory at a location
    //    different from the location of small_A.

    // Set A[10] to A[19] to 'A':
    memset (A + 10, 'A', 10);

    // At this point, A should contain:
    //    AAAAAAAAA\0AAAAAAAAAA
    //    without any \0 at the end.

    // calloc() an array B:
    char * B = calloc (NEW_SIZE, sizeof(char));
    if (!B)
    {
        perror ("calloc");
        return EXIT_FAILURE;
    }

    // calloc() not only allocates memory, but
    //    also sets every spot in it to \0.

    // Copy 9 'A' characters from A to B:
    memcpy (B, A, 9);

    // B should contain the following now:
    //    AAAAAAAAA\0\0\0\0\0\0\0\0\0\0\0

    // Set the last 10 spots of B to "BBBBBBBBBB":
    memset (B + 10, 'B', 10); 

    // B should contain the following now:
    //    AAAAAAAAA\0BBBBBBBBBB

    // Printing the two strings using loops:
    int i;

    printf ("A contains: ");

    for (i = 0; i < NEW_SIZE; i++)
    {
        if (A[i] == '\0')
           printf ("\\0");
        else
           printf ("%c", A[i]);
    }

    printf ("\nB contains: ");

    for (i = 0; i < NEW_SIZE; i++)
    {
        if (B[i] == '\0')
           printf ("\\0");
        else
           printf ("%c", B[i]);
    }

    // Compare A and B using strcmp():
    int result = strcmp (A, B);
    // strcmp() will stop the character
    //    comparison when it sees '\0'.

    printf ("\nAccording to strcmp(), ");

    if (result < 0)
       printf ("A appears before B "
               "in the dictionary.\n");
    else if (result > 0)
       printf ("A appears after B "
               "in the dictionary.\n");
    else
       printf ("Both A and B contain "
               "the same characters.\n");

    // Follow-up question #1:
    // Which one of the 3 statements above
    //    will be printed to the screen?
    // Hint:
    //    A contains: AAAAAAAAA\0AAAAAAAAAA
    //    B contains: AAAAAAAAA\0BBBBBBBBBB
    //    and strcmp() stops the comparison
    //    at '\0'.

    // Compare A and B using strncmp():
    result = strncmp (A, B, NEW_SIZE);
    // strncmp() is asked to compare
    //    the first 20 characters, but
    //    it stops the comparison at '\0'.

    printf ("According to strncmp(), ");

    if (result < 0)
       printf ("A appears before B "
               "in the dictionary.\n");
    else if (result > 0)
       printf ("A appears after B "
               "in the dictionary.\n");
    else
       printf ("Both A and B contain "
               "the same characters.\n");

    // Follow-up question #2:
    // Which one of the 3 statements above
    //    will be printed to the screen?
    // Hint:
    //    A contains: AAAAAAAAA\0AAAAAAAAAA
    //    B contains: AAAAAAAAA\0BBBBBBBBBB
    //    and strncmp(), too, stops at '\0'. 

    // Compare A and B using memcmp():
    result = memcmp (A, B, NEW_SIZE);
    // memcmp() will compare exactly
    //    the first 20 characters (it
    //    won't stop at '\0'.)

    printf ("According to memcmp(), ");

    if (result < 0)
       printf ("A appears before B "
               "in the dictionary.\n");
    else if (result > 0)
       printf ("A appears after B "
               "in the dictionary.\n");
    else
       printf ("both A and B contain "
               "the same characters.\n");

    // Follow-up question #3:
    // Which one of the 3 statements above
    //    will be printed to the screen?
    // Hint:
    //    A contains: AAAAAAAAA\0AAAAAAAAAA
    //    B contains: AAAAAAAAA\0BBBBBBBBBB
    //    and memcmp() WON'T stop at '\0'.

    printf ("The reason for the difference "
            "is that strcmp() and strcmp() stop "
            "comparing \nwhen they encounter the "
            "null character, \\0, but memcmp() "
            "keeps comparing \n"
            "until all NEW_SIZE characters "
            "are compared.\n");

    // Freeing memory:
    free (A);
    free (B);

    return EXIT_SUCCESS;
}
