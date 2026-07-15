/* This program reminds us that errors must be 
 *    checked after a user entered some input:
 *    we shouldn't depend on the user's
 *    attention to detail and integrity when
 *    requesting data from the user. Whether
 *    the user makes a mistake and enters an
 *    incorrect datum, or if they do so
 *    intentionally, our program must be
 *    capable of detecting it and, possibly,
 *    asking the user to re-enter data.
 *
 *    Miriam Briskman, 2/8/2023
 *    CISC 3350, Brooklyn College
 *    Licensed under CC BY-NC 4.0
 */

#include <stdio.h>
#include <stdlib.h>

int main ()
{
    printf ("Please enter an integer "
            "larger than 5: >> ");

    int input; // Will store the user's input.

    scanf ("%d", &input); // Read keyboard input.

    // "The additional arguments should point
    // to already allocated objects of the type
    // specified by their corresponding format
    // specifier within the format string."
    // (Taken from:
    // http://www.cplusplus.com/reference/cstdio/scanf/)
    //
    // The above quote means that, we you decide
    //    to read in input from the user, ensure
    //    that you are reading it into an existing
    //    variable or array, and that the data
    //    type of the variable or array matches the
    //    format that you are trying to read in.
    //    For example, in the above scanf()
    //    statement, we wish to read in "%d", which
    //    is the format specifier of an integer,
    //    and, indeed, 'input' is a variable of the
    //    type 'integer'.


    // Checking whether the correct input has been
    //    entered:
    if (input > 5)
        printf ("The integer you entered "
                "is: %d.\n", input);
    else
    {
        printf ("Error: you entered %d, "
                "which is less than 5!\n", input);
        exit(EXIT_FAILURE);
    }
	
    return EXIT_SUCCESS;
}
