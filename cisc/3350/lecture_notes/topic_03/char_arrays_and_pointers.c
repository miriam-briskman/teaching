/* A C program demonstrating the use of arrays
 *    of characters, a.k.a. C-strings!
 *
 *    Miriam Briskman, 2/15/2023
 *    CISC 3350, Brooklyn College
 *    Licensed under CC BY-NC 4.0
 */

#include <stdio.h>
#include <stdlib.h>
// A string library: strlen(), strcmp() ...
#include <string.h>

int main ()
{
    // *~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*   
 
    /* String literals + <string.h> Functions */

    /* In C, we can create a variable that holds a
          single char, such as by writing:
          char c = 'A';
   
       However, C doesn't have a String 'variable'
          (object) like Java does. Instead, we use
          char arrays, which are also called
          C-strings:
    */
    char arr [6] = "Hello";

    /* The reason we wrote:
          char arr [6]
       and not
          char arr [5]
       is that, despite "Hello" having only 5 letters,
       we must avail one more memory slot for the
       null terminator '\0' at the end:
       +---+---+---+---+---+----+
       | 0 | 1 | 2 | 3 | 4 | 5  |
       +---+---+---+---+---+----+
       | H | e | l | l | o | \0 |
       +---+---+---+---+---+----+
       Thus, we need 5 + 1 = 6 items in the array.

       C automatically appends the '\0' character
       at the end of a string literal (but not at
       the end of non-literal arrays, as we shall
       see below.) We, therefore, don't need to
       write:
          arr [5] = '\0';
       since in this case, it is done automatically.
    */

    // Let's print the array's content:
    printf ("The string is: %s\n", arr);

    // To access a specific char within the C
    //    string, use brackets []:
    char fourth_char = arr[4];

    // Follow-up question:
    // What character will 'fourth_char' contain,
    //    given that 'arr' contains the string
    //    "Hello"?
    // Hint:
    // +---+---+---+---+---+----+
    // | 0 | 1 | 2 | 3 | 4 | 5  |
    // +---+---+---+---+---+----+
    // | H | e | l | l | o | \0 |
    // +---+---+---+---+---+----+

    // Let's print the character out:
    printf ("The 4th character of \"%s\" is: %c\n", 
            arr, fourth_char);

    // Note that " (double quotes) is another
    //    escape character that we must escape
    //    for it to be properly printed on the
    //    screen, so we write: \" each time we
    //    need to include " inside a printout.

    // We can find the length of 'arr' by using
    //    <string.h>'s strlen() function:
    int length = strlen (arr); 

    // Fact: the null character '\0' isn't counted
    //    as part of a string's length. As such,
    //    the variable 'length' above will contain
    //    the number 5, not 6.

    // Let's print the length out:
    printf ("The length of \"%s\" is: "
            "%d characters\n", arr, length);

    // Here is another C string:
    char arr2 [3] = "Hi";

    // To check if two strings are equal (that is,
    //    to check if both strings contain the same
    //    characters,) use the strcmp() function 
    //    of <string.h>:
    int result = strcmp (arr, arr2);
    // strcmp() returns 0 if the strings are equal,
    //    a negative integer if arr < arr2, and a
    //    positive integer if arr > arr2.
    //
    // When we say "arr < arr2", we mean that 'arr'
    //    would appear before 'arr2' in a dictionary.
    //
    // Examples: (1) strcmp ("No", "No") = 0
    //           (2) strcmp ("cat", "dog") < 0

    // Let's print the result!
    if (result < 0)
       printf ("\"%s\" appears before \"%s\" in "
               "the dictionary.\n", arr, arr2);
    else if (result > 0)
       printf ("\"%s\" appears before \"%s\" in "
               "the dictionary.\n", arr2, arr);
    else
       printf ("Both \"%s\" and \"%s\" are "
               "the same!\n", arr, arr2);

    // Follow-up question:
    // Given that arr = "Hello" and arr2 = "Hi",
    //    which one of the above 3 statements
    //    will be printed out? Why?
    
    // If you just want to check for equality/inequality
    //    (and you don't care about their alphabetical 
    //    order:)
    if (result != 0)
       printf ("Both \"%s\" and \"%s\" are "
               "different strings!\n", arr, arr2);
    else
       printf ("Both \"%s\" and \"%s\" are "
               "the same strings!\n", arr, arr2);

    // A list of <string.h> functions + examples
    //    can be found at:
    //        https://cplusplus.com/reference/cstring/
    // [Click on the name of any individual function
    //  to read about it.]
    
    // *~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*

    /* Char Arrays on the Stack and on the Heap */

    // Let's first quickly explain what the stack
    //    and the heap memory sections are. Let's
    //    read slides 4-5 at the following link:
    // https://www.sci.brooklyn.cuny.edu/~briskman/cisc/3320/lecture_notes/topic_04/04.html

    // We create an array on the Stack in memory.
    //    This is the simplest type of a non-literal
    //    array of variables:
    char stack_array [27];

    // and then we fill it up:
    int i;
    for (i = 0; i < 27 - 1; i++)
       stack_array[i] = 'A' + i; // "ABCDEFG...."
    
    // When creating an array of characters, we
    //    must put the '\0' character at the end
    //    of the string, since C automatically
    //    puts the '\0' character only when
    //    string literals are created, not string
    //    variables (such as 'stack_array'.)
    stack_array[27 - 1] = '\0';

    // Print this array:
    printf ("Stack array: %s\n", stack_array);
    
    // Create an array on the Heap in memory:
    char * heap_array = malloc (27 * sizeof(char));

    /* Note:
       'sizeof' is an operator in C. It tells how
       many bytes in memory are needed to store a
       data type. For example, on most Linux
       computers, 'char' takes up 1 byte. Because
       the sizes of data types is computer-
       dependent, it is advised to use 'sizeof'
       when allocating arrays on the heap.

       sizeof (array) finds how many bytes
       were allocated for the array 'array'.
       Note that, to find the length of a
       string inside a char array (in case the
       string occupies less than the entire
       array's memory) you should use strlen()
       and not sizeof. Example: If you create
       the array
                 char name[100] = "Anna";
       then sizeof (name) will return 100
       while strlen (name) will return 4.
    */

    // Check that memory for the heap array was
    //    successfully allocated (i.e., check
    //    that no error happened in the execution
    //    of malloc():)
    if (heap_array == NULL)
    {
        printf ("Error: malloc() failed.\n");
        exit (EXIT_FAILURE);
    }

    /* Notes:
       (1) After asking the computer to allocate
           memory on the heap for an array or a
           variable with malloc(), there is no
           guarantee that memory would be allocated
           due to various possible errors (e.g.,
           insufficient memory space left.) In such
           a case, malloc() would set the array or
           pointer to NULL, which is a macro whose
           value  is a null pointer (that is, a
           pointer to the 0th address in memory.)

                   +---+---+---+---+---+-----+
                   | 0 | 1 | 2 | 3 | 4 | ... |
                   +---+---+---+---+---+-----+
           NULL -> |   |   |   |   |   | ... |
                   +---+---+---+---+---+-----+

           That is, NULL is defined in <stdlib.h>
           as:

           #define NULL ( (void *) 0)

           (i.e., a conversion of 0 to a pointer.)

           This special value is the way of C to
           tell us that no memory was allocated for
           the array/variable that we requested to
           create, and that we should issue this
           request again (perhaps, after first
           resolving the underlying issue or error.)
       (2) The difference between '\0' (the null
           terminator) and NULL (the null pointer)
           is that '\0' is of the 'char' type,
           while NULL is of a void pointer type.
           We use them for different purposes: '\0'
           tells when a string ends, and NULL tells
           that an array couldn't be created (or
           that some array-returning function
           failed.)
       (3) The exit() function exits the entire
           program. The only argument it accepts
           is the "exit code", which tells the mode
           in which we exit the program. For
           example, 0 (or 'EXIT_SUCCESS') represents
           a successful exit (no errors occurred,)
           and 1 (or 'EXIT_FAILURE') represents a
           failing program execution that lead to
           an abrupt exit. For portability, we use:
           
           exit (EXIT_FAILURE);

           instead of:

           exit (1);

           just as we do with return EXIT_SUCCESS;
    */

    // Fill the array up with the alphabet:
    for (i = 0; i < 27 - 1; i++)
       heap_array[i] = 'A' + i; // "ABCDEFG...."

    // We put the '\0' character at the end of
    //    the 'heap_array' string, too:
    heap_array[27 - 1] = '\0';

    /* A pointer variable is a variable that
          stores the memory address where the
          value of the variable is located.

       Example:
       When we write:
          int n = 5;
       we create an integer variable whose
       value is 5.

       When we write:
          int * addr = &n;
       we create a pointer variable to an
       integer (shortly called "integer
       pointer",) and set 'addr' to contain
       the address of the variable 'n'.

       Here's how main memory looks:

             addr
               |
               V
       +-----+---+-----+
       | ... | 5 | ... |
       +-----+---+-----+

       Summary so far:
       (1) To create a pointer to an int,
           char, double, etc., we need to
           place a * sign right after the
           data type.
       (2) To find the address of a variable,
           say 'var', write: '&var'.

       Fact: An 'address' is an integer whose
             size depends on the architecture
             (features) of the operating system:
             in a 32-bit OS, an address is an
             integer of size 4 bytes (= 32 bits)
             and in a 64-bit OS, an address is
             of size 8 bytes (= 64 bits).

       Fact: The name of an array, say 'arr',
             is an address variable itself.
             For example, to store the address
             to the start of an integer array
             'arr', we can do:
                int * addr = arr;
             [That is, we don't include the '&'
              character to the left of 'arr'.]

             arr addr
              |   |
              V   V
             +-----+----+-----+----+-----+
             | 101 | 83 | -13 | 2  | 121 |
             +-----+----+-----+----+-----+

       Now, let's create some char pointers and
       see what we can do with pointers!
    */

    // Create a pointer to the stack array:
    char * ptr_stack_array = stack_array;
    // 'ptr_stack_array' above points at the
    //    beginning of the array, specifically 
    //    at the letter 'A'. In other words,
    //    'ptr_stack_array' contains the address
    //    of the spot in memory where the letter
    //    'A' is stored:
    //
    //  stack_array
    //    |
    //    V
    //  +---+---+---+---+---+---+---+---+-----+
    //  | A | B | C | D | E | F | G | H | ... |
    //  +---+---+---+---+---+---+---+---+-----+
    //    ^
    //    |
    //  ptr_stack_array
     

    // We can move the pointer to other places!
    ptr_stack_array += 3;
    // Now 'ptr_stack_array' points at the letter 'D':
    //
    //  stack_array
    //    |
    //    V
    //  +---+---+---+---+---+---+---+---+-----+
    //  | A | B | C | D | E | F | G | H | ... |
    //  +---+---+---+---+---+---+---+---+-----+
    //                ^
    //                |
    //         ptr_stack_array

    // Print the string beginning at the pointer:
    printf ("String beginning at ptr_stack_array: %s\n",
            ptr_stack_array);

    // Follow-up question:
    // What string will be printed to the screen
    //    as a result of the above printf()?

    // Create a pointer to the heap array:
    char * ptr_heap_array = heap_array;
    // Here is how a pasrt of the heap section
    //    of memory would look:
    //
    //  heap_array
    //    |
    //    V
    //  +---+---+---+---+---+---+---+---+-----+
    //  | A | B | C | D | E | F | G | H | ... |
    //  +---+---+---+---+---+---+---+---+-----+
    //    ^
    //    |
    //  ptr_heap_array

    // Move the pointer forward:
    ptr_heap_array += 4;

    // Follow-up question:
    // What letter does the pointer 'ptr_heap_array'
    //    above point at after the instruction:
    //       ptr_heap_array += 4;
    //    finished executing?
    //
    //  heap_array
    //    |
    //    V
    //  +---+---+---+---+---+---+---+---+-----+
    //  | A | B | C | D | E | F | G | H | ... |
    //  +---+---+---+---+---+---+---+---+-----+
    //    
    //           ?
    //     ptr_heap_array

    // Replace the character at which 'ptr_heap_array'
    //    currently points by the letter 'Z':
    ptr_heap_array[0] = 'Z';
    // The above change affects the 'heap_array'
    //    itself! That is, one of the letters in
    //    'heap_array' will change to 'Z'.

    // Print the entire updated heap array:
    printf ("Heap array: %s\n", heap_array);

    // Functions in <string.h> can be used not
    //    only on string literals, but also on
    //    stack and heap char arrays!
    if (strcmp (stack_array, heap_array) != 0)
       printf ("The strings %s and %s are NOT the same!\n",
               stack_array, heap_array);
    else
       printf ("The strings %s and %s are the same!\n",
               stack_array, heap_array);

    // Moving our pointers a bit forward: 
    ptr_heap_array++;
    ptr_stack_array += 2;

    // Inside the stack:
    //
    //  stack_array
    //    |
    //    V
    //  +---+---+---+---+---+---+---+---+-----+
    //  | A | B | C | D | E | F | G | H | ... |
    //  +---+---+---+---+---+---+---+---+-----+
    //                        ^
    //                        |
    //                 ptr_stack_array
    //
    // Inside the heap:
    //
    //  heap_array
    //    |
    //    V
    //  +---+---+---+---+---+---+---+---+-----+
    //  | A | B | C | D | Z | F | G | H | ... |
    //  +---+---+---+---+---+---+---+---+-----+
    //                        ^
    //                        |
    //                 ptr_heap_array

    // We will now compare the substrings that
    //    begin with 'ptr_stack_array' and
    //    with 'ptr_heap_array':
    if (strcmp (ptr_stack_array, ptr_heap_array) != 0)
       printf ("The strings %s and %s are NOT the same!\n",
               ptr_stack_array, ptr_heap_array);
    else
       printf ("The strings %s and %s are the same!\n",
               ptr_stack_array, ptr_heap_array);

    // Follow-up question:
    // Which printf() statement will be executed:
    //    does the string that starts at 'ptr_stack_array'
    //    have the same characters as the string that
    //    starts at 'ptr_heap_array'?
    // Hint: use the above picture of the stack and
    //    heap sections of main memory.

    // Finally, we need to free the memory for the heap
    //    array because there is NO garbage collector in
    //    the C language. (Stack arrays are discarded
    //    when the program exits the function where the
    //    array was created, such as the main() function
    //    in our case.)
    free (heap_array);
    // Make sure to keep at least 1 pointer to the 
    //    beginning of the array to be able to free it
    //    later. This is why we didn't do things like:
    //       heap_array += 10;
    //    to keep 'heap_array' pointing at the start.

    // You must free a heap array only once, even if
    //    several pointers to it were created! It's like
    //    having several doors in a house: when you
    //    decide to demolish the house, you demolish
    //    it only once, not as many times as the number
    //    of the doors it has :)
     
    return EXIT_SUCCESS;
}
