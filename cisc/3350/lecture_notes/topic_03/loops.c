/* A C program that works with for, while,
 *    and do-while loops.
 *
 *    Miriam Briskman, 2/8/2023
 *    CISC 3350, Brooklyn College
 *    Licensed under CC BY-NC 4.0
 */

#include <stdio.h>
#include <stdlib.h>

int main ()
{
    unsigned int sum = 0,
                 num = 5,
                 moves = 3;

    // Above, we must initialize 'sum' to
    //    zero before starting to use 'sum'
    //    because C doesn't automatically
    //    initialize your variables to zero
    //    when they are created. It will
    //    likely contain some random garbage
    //    value, e.g., 1049472647.
	
    // for loop:

    int i;

    for (i = 1; i <= 10; i++)
    {
        sum = sum + i;
    }

    // We could've also written:
    //    sum += i;
    // instead of
    //    sum = sum + i;

    // Note: writing 'int i = 1'
    //    (i.e., for (int i = 1 ....))
    //    inside the for loop's header
    //    is unsupported in earlier
    //    versions of the C language.
    //    As such, make sure to declare
    //    the i variable outside of the
    //    for loop, just like we did
    //    above: int i;

    printf ("The young Carl Gauss computed "
            "the sum of the 1st 10 positive "
            "integers to be %u in a few "
            "moments of thought!\n", sum);

    // while loop:

    printf ("Upside-down pyramid:\n");

    while (num > 0)
    {
        for (i = num; i > 0; i--)
            printf ("* ");
        printf("\n");
        num--;
    }

    // do-while loop:

    printf("Claw moves remaining: %d,\n", moves);

    do
    {
        moves--;
        printf("Claw moves remaining: %d,\n",
               moves);
    } while (moves > 0);

    printf("Now, send the claw down and "
           "catch a toy!\n");
        
    // *~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*

    /* Follow-up question:

       How will the following while loop behave,
       if we were to uncomment it?

       int true = 1;
       while (true)
       {
           printf ("Till the world ends!\n");
       }
    */

    return EXIT_SUCCESS;
}
