/* A program that will cause a segmentation fault
 *    run-time error to be displayed on the screen
 *    due to accessing a character that is located
 *    outside the created heap array.
 *
 *    Miriam Briskman, 2/19/2023
 *    CISC 3350, Brooklyn College
 *    Licensed under CC BY-NC 4.0
 */

// Library needed for malloc(), free(),
//    and the EXIT_SUCCESS constant:
#include <stdlib.h>
// Library needed for printf():
#include <stdio.h>

int main ()
{
    // Allocating a character array of size 10
    //    on the heap using malloc():
    char * my_str = malloc (10 * sizeof(char));

    // Trying to access and print a character far
    //    outside of the array's boundary:
    printf ("%c", my_str[10000000000]);

    free (my_str); // Freeing allocated memory.

    return EXIT_SUCCESS;
}
