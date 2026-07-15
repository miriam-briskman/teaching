/* C program that reads from and writes to files.
 *
 *    Miriam Briskman, 2/8/2023
 *    CISC 3350, Brooklyn College
 *    Licensed under CC BY-NC 4.0
 */

#include <stdio.h>
#include <stdlib.h>

// Constant storing array size:
const int ARR_SIZE = 400;

int main ()
{
    // Declare a pointer to a file structure: (A
    //    'structure', or shortly 'struct', is
    //    like an 'object' in C. That is, it
    //    is a data type that consists of a
    //    mixture of variables. We will learn
    //    more about structs later.)
    FILE * my_file;

    /////////////////////////
    // Writing into a file //
    /////////////////////////

    // Open text.txt in a writing mode:
    my_file = fopen ("text.txt", "w");
    // The option 'w' creates an empty file for
    //    writing. If a file with this name
    //    already exists, its content is erased
    //    and the file is considered as a new
    //    empty file.

    // If the file didn't open successfully,
    //    the pointer will be NULL. We use
    //    this if statement to check that no
    //    file-opening errors happened.
    if (my_file == NULL)
    {
        printf ("Error occured while opening text.txt");
        exit (EXIT_FAILURE);
    }
    else // The file opened successfully.
    {
        // Let's add content into the file:
        fprintf (my_file, "Bla!\nBlu!");

        // Close the file:
        fclose (my_file);
    }
        
    ///////////////////////////////////////////
    // Reading a file character-by-character //
    ///////////////////////////////////////////

    // Open text.txt in a reading mode:
    my_file = fopen ("text.txt", "r");
    // Note that we attempt to open the
    //    same file that we used above
    //    for writing content!
    // The option "r" allows us to only
    //    read from the file.
    // We will learn what other file
    //    access options exist in Topic 5
    //    when we cover fopen() more
    //    closely.

    // Check for errors in opening the file:
    if (my_file == NULL) 
    {
        printf ("Error occured while opening text.txt");
        exit (EXIT_FAILURE);
    }
    else // The file opened successfully.
    {
        // Create an integer variable:
        int character;

        // Read a single character from the file:
        while ((character = getc (my_file)) != EOF)
        {
            printf ("The character we read-in was: "
                    "%c, with the ASCII code of %d.\n",
                    (char) character, character);
        }

        printf ("We reached the bottom of the file!\n");

        // Close the file:   
        fclose (my_file);
    }

    /* Notes:
       (1) The 'while' statement asks whether:
              (character = getc (my_file))
           is not equal to EOF. Let's explain
           this: The function getc() returns
           the numeric (ASCII) value of the
           next character in the file 'my_file'
           and puts this value into 'character'.
           Then, the while loop checks whether
           'character' is anything other than the
           end-of-file flag, which is represented
           by the EOF constant (this constant is 
           defined in the <stdio.h> library.)

           Bottom line: the 'while' loop reads one
           character at a time from the file until
           the end of the file is reached.

       (2) In most Linux computers, the constant
           EOF is equal to -1. However, since
           this value depends on how the library
           <stdio.h> is implemented on every
           Linux computer type, we should avoid
           comparing characters with -1 and
           instead should use EOF (to be on the
           safe side in case some computer
           internally defines EOF to be a value
           other than -1.)

       (3) In the printf() function inside the
           'while' loop, we print both the
           ASCII value of the character and the
           character itself. To convert the
           numeric (int) value into a char value,
           we use 'type casting':
              (char) character
           which performs an inline conversion of
           an integer into its respective
           character.
           Examples:
           (a) 32 -> [SPACE]
           (b) 46 -> '.'
           (c) 48 -> '0'
           (d) 65 -> 'A'
           (e) 97 -> 'a'

           Here is a quick link to the full
           ASCII table (256 entries) for your
           reference:
           https://www.asciitable.com/
    */

    /////////////////////////////////
    // Reading a file line-by-line //
    /////////////////////////////////
        
    // Re-open the same file:
    my_file = fopen ("text.txt", "r");

    if (my_file == NULL)
    {
        printf ("Error occured while opening text.txt");
        exit (EXIT_FAILURE);
    }                                              
    else
    {
        // Allocate a char array on the heap with
        //    (hopefully) enough space to store
        //    a file's contents:
        char * my_arr = malloc (ARR_SIZE * sizeof(char));

        // Follow-up question:
        // What is the size of the array 'my_arr'?
        // (I.e., how many chars can 'my_arr'
        // contain?)
        // Hint: check what 'ARR_SIZE' equals to.


        /* Note that we could've also used a stack
           array instead:
              char my_arr [ARR_SIZE];
           The reasons many C programmers prefer to
           store arrays on the heap are:
           (1) The stack is smaller than the heap,
               so larger arrays are advised to be
               created on the heap.
           (2) You can change the size of a heap
               array to a larger (or smaller) size
               just by calling one function:
               realloc() [The sizes of stack arrays
               remain fixed and can't be changed;
               if you want a larger stack array,
               a new one must be created.]
           (3) Sometimes, you want to create a new
               array inside a function (e.g., as
               part of some algorithm,) and then
               pass it to other functions to be used
               after the function exits. This can
               be done only with heap arrays because
               a stack array that was created inside
               a function will be erased once the
               function exits (because a stack array
               is a 'local' variable that is bound
               only to the scope of the function.)
               We'll see how to 'return' heap arrays
               from functions when we review the
                   functions.c
               program right after we finish talking
               about files now.
        */

        int line_counter = 1;

        // The following loop reads entire lines from
        //    the file and then prints them out.
        // fgets() takes 3 arguments: the array where
        //    the line should be copied to, the size
        //    of this array, and the file variable.
        //    This function reads up to (ARR_SIZE - 1)
        //    characters into 'my_arr' (or until a
        //    newline character is encountered,) and
        //    puts a null character '\0' at the end
        //    of the copied line inside 'my_arr'.
        // fgets() equals NULL when we reach the end
        //    of the file or if some other error in
        //    happens during the reading.
        while (fgets (my_arr, ARR_SIZE, my_file) != NULL)
        {
            printf("Line %d: %s", line_counter, my_arr);
            line_counter++;
        }

        printf ("\n");

        // Free the heap memory (remember there is
        //    no garbage collection in C!)
        free (my_arr);

        // Close the file to release all its resources:
        fclose (my_file);
    }

    return EXIT_SUCCESS;
}
