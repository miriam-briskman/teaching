/* A program that will cause a segmentation fault
 *    run-time error to be displayed on the screen
 *    due to over-populating an array of characters
 *    that was created on the stack.
 *
 *    Miriam Briskman, 1/6/2024
 *    CISC 3350, Brooklyn College
 *    Licensed under CC BY-NC 4.0
 */

// Library needed for the EXIT_SUCCESS constant:
#include <stdlib.h>
// Library needed for strcpy():
#include <string.h>

int main ()
{
    // Create a char array of the size of 10:
    char my_str [10];

    // The following copying of a string of more than
    //    10 characters will cause a segmentation error.
    strcpy (my_str, "This is a very very very very very "
                    "very very very very very very very "
                    "very very very very very very very "
                    "very very very long sentence.");
    return EXIT_SUCCESS;
}
