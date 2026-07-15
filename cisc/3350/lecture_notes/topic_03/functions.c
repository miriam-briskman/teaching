/* A C program that declares and defines functions
 *    of various types and calls them inside main().
 *
 *
 *    Miriam Briskman, 2/22/2023
 *    CISC 3350, Brooklyn College
 *    Licensed under CC BY-NC 4.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // The string library of C

/* Declarations of functions

   In C and C++, the headers of functions that
      are defined below the main function must
      must be repeated above the main function.
      These headers are called 'declarations'.
      Otherwise, the compiler won't find them,
      which will result in a compilation error.
      Here are the declarations of the four
      functions that we create in this program:
*/
short sign (double num);
void increment (int * num);
void increment2 (int num);
char * allocate_and_populate (int length, char content);

int main ()
{
    // Output separator (just for the beauty of the
    //    printout:)
    printf ("---------------------------\n");

    double x = -15.2;
    // Here is our call to the sign() function
    //     that we created:
    short the_sign_of_x = sign(x);

    printf ("The number %.3f is ", x);

    if (the_sign_of_x < 0)
        printf ("negative!\n");
    else if (the_sign_of_x > 0)
        printf ("positive!\n");
    else
        printf ("a zero!\n");

    printf ("---------------------------\n");

    int age = 20;

    // Happy Birthday! Let's increment the age
    //    via a call to the increment()
    //    function that we created:
    increment (&age);

    // [Recall that the symbol & retrieves the
    //    address of the variable 'age'. That is,
    //    &age is a pointer to the variable 'age'.]

    printf ("Inside main(), after increment(): "
            "The number is now %d.\n", age);

    // Let's do it again, but this time
    //    using the increment2 function
    //    that we created:
    age = 20;
    increment2 (age);
    printf ("Inside main(), after increment2(): "
            "The number is now %d.\n", age);

    /* Passing by Value vs. Passing by Reference

       When we compile and run this program, we
       will notice that the result of increment()
       is different from the result of
       increment2(). Specifically, only one of them
       will increment the value in the variable
       'age'.

       The reason has to do in the way that we
       pass variables to functions:
       (1) 'Pass-by-value' means that we write
           the name of a variable as an argument
           to the function. The compiler replaces
           the name of the variable with the
           underlying value (e.g., 20), and the
           function uses this value. Once the
           function exits, no change will be
           made to the actual variable that we
           passed to the function.
       (2) 'Pass-by-reference' means that we
           provide the address of a variable as
           an argument to the function. Then,
           inside the function, we can access
           the memory location at that address
           and make any changes to the variable
           itself. That means that change WILL
           affect variables outside the function.

       Follow-up question:
       Based on the above, which one of
          increment() and increment2() will
          change the number inside the 'age'
          variable?
    */ 

    printf ("---------------------------\n");
       
    // Let's create an array containing 40 'A'
    //    characters!
    char * heap_arr = allocate_and_populate (40, 'A');

    // !heap_arr is the same as checking that:
    //    heap_arr == NULL
    if (!heap_arr)
    {
        printf ("Error occured while creating "
                "the heap array.\n");
        exit (EXIT_FAILURE);
    }

    printf ("The C string on the heap contains: %s.\n"
            "These are %zu letters in total!\n",
            heap_arr, strlen(heap_arr));

    // Don't forget to free arrays that were
    //    created by other functions!
    free (heap_arr);

    printf ("---------------------------\n");

    return EXIT_SUCCESS;
}

// Function returning the sign of a
//    floating-point number: -1 if negative,
//    0 if zero, or 1 if positive.
short sign (double num)
{
    if (num < 0)
        return -1;
    if (num > 0)
        return 1;
    return 0;
}

// Function incrementing the variable whose
//    pointer is given as an argument and
//    prints the incremented value, as measured
//    inside the function.
void increment (int * num)
{
    *num += 1;
    // Alternative to the above line of code:
    //    num[0] += 1;
    // When we put a * to the left of a pointer,
    //    we access the memory location to which
    //    the pointer points. This is called
    //    'de-referencing'.
    // Summary:
    // (1) &var - returns the address of a value
    // (2) *var - return the value at address 'var'
    // In other words, & and * are opposite
    //    operations.

    printf ("Inside increment(): The number "
            "is now %d.\n", *num);

    // Since the return type of the function is
    //    'void', we don't return any value.
    //     You may, however, type:
    return;
}

// Function incrementing the variable that is
//    given as an argument and prints the
//    incremented value, as measured inside
//    the function.
void increment2 (int num)
{
    num += 1;
    printf ("Inside increment2(): The number "
            "is now %d.\n", num);
    return;
}

// Function allocating a heap array of size
//    'length' and populating it with the
//    character 'content'. A pointer to this new
//    array is returned. That is, the created
//    array will be accessible even after we
//    return from the function. It is the
//    programmer's responsibility to free() the
//    array later in the program.
char * allocate_and_populate (int length, char content)
{
    // Allocate an array on the heap:
    char * heap_array
        = malloc ((length + 1) * sizeof(char));
    if (heap_array == NULL)
        return NULL;
    // Populate the entire array with the 
    //    character inside 'content':
    int i;
    for (i = 0; i < length; i++)
        heap_array[i] = content;
    // Place the null character at the end:
    heap_array[length] = '\0';

    // Return a pointer (address) to the
    //    beginning of the array:
    return heap_array;
}
