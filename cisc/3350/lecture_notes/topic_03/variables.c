/* C program showing how to work with variables,
 *    constants, assignments and basic math,
 *    and printf statements.
 *
 *    Miriam Briskman, 2/15/2023
 *    CISC 3350, Brooklyn College
 *    Licensed under CC BY-NC 4.0
 */


// Include a reference to C's standard input and
//    output library:
#include <stdio.h> 
// Library defining some frequently used macros
//    and functions. We include this library in
//    this program because we will be using one
//    of its macros, 'EXIT_SUCCESS', in this
//    program's code:
#include <stdlib.h>
// Library with string-manipulating functions:
#include <string.h> 

/* Let's talk about constants in C:
   1. A constant value is set only once and
      CANNOT be changed throughout the program.
   2. A constant definition in C begins with
      the keyword "const". 
   3. The type of the constant must be specified
      as well: int, double, char, etc.
   4. The name of a constant should contain all
      capital letters, digits, and/or underscores,
      like PI or THIS_CONST_2.
   5. As with non-constant variables, the value of
      the constant is assigned using the = symbol. 
   6. A good programming practice is to place
      constants after the #include statements and
      before the main function.
      --> This way, any piece of code defined
          below the constant's definition has
          access to the constant!  
*/

// First, we create a constant storing the ratio
//    of a circle's circumference to its diameter (pi).
// --> Since pi is a floating point number,
//     we store it as a 'double' constant:
const double PI = 3.1415926;
// Now, let's have a constant storing the number
//    of months in year.
// --> A 'short int' constant can store a value
//     between 0 to 65,535, so it does not consume
//     as much memory as a regular 'int'.
const unsigned short int MONTHS_PER_YEAR = 12;
// How about string constants? Let's store the name
//    of the 1st month of the year.
// --> char[] is an array of characters, also called
//     a string literal.
// --> Usually, the size of the char array should be
//     specified. However, since we define the
//     constant to be "January", a string literal,
//     the compiler is able to find the size needed
//     to store all the characters of "January".
// --> C does not have string objects, which is why
//     we use char arrays instead.
// --> Any array in C is stored with a '\0' null
//     character at its end to let the computer know
//     where the array ends.
// --> In our case, MONTH_1 appears in memory as:
//     +---+---+---+---+---+---+---+----+
//     | J | a | n | u | a | r | y | \0 |
//     +---+---+---+---+---+---+---+----+
//     in bytes (each char in C contains 8-bits.)
const char MONTH_1 [] = "January";

// Unlike const, which requires extra execution
//    time since it needs to access main memory,
//    a define statement makes the compiler
//    replace each instance of a constant,
//    MAX_CHARS in the example below, by 1024
//    before the program is compiled. The #define
//    statement, therefore, executes much faster
//    than a constant definition with 'const'.
//    A 'constant' that is defined with #define
//    is called a "macro".
#define MAX_CHARS 1024

// main function
int main() 
{ 
    /* Phew! We covered constants. Now about
       variables in C:
       1. Unlike constants, variables can have
          their values changed throughout the
          program.
       2. Variables are declared very similarly
          to constants: just omit the 'const'
          keyword from the declaration.
       3. Variables have scopes: the regions in
          the program where the variable is
          visible and accessible.
          --> If a variable is defined inside
              main(), it is accessible inside
              main() and inside other functions
              that main calls and passes the
              variable as an argument to those
              functions.
    */
    char   newline_character = '\n',
           tab_character = '\t',
           firstEnglishLetter = 'A';
    unsigned short grade = 100;
    short  NYC_boroughs = 5;
    int    whoWantsToBeAMillionaire = 1000000;
    long   billion = 1000000000;
    long long trillion = 1000000000000;
    double my_circle_diameter = 2.5;
    long double one_ninth = 0.11111111111;
    // C does not have a boolean data type!
    // Use:
    int true = 1,
        false = 0;
    // instead.

    // What would the following printing
    //    statements print to the screen?
    double circumference = my_circle_diameter * PI;
    printf ("The circumference of my "
            "circle is: %f\n", circumference);

    // When the strings that we print are long,
    //    we can 'chop' them into smaller pieces
    //    and include them on separate lines,
    //    just as we did in the printf()
    //    statement above. The C compiler will
    //    then implicitly concatenate these
    //    strings.

    printf ("I%cLove%cNew%cYork%c", newline_character,
            newline_character, newline_character,
            newline_character);

    printf ("I%cLove%cNew%cYork%c", tab_character,
            tab_character, tab_character,
            newline_character);

    printf ("This fancy restaurant, which has "
            "locations in all %hd boroughs, received "
            "the grade of %c.\n",
            NYC_boroughs, firstEnglishLetter);

    printf ("The 1st of the %d months, %s, "
            "has %zu letters!\n",
            MONTHS_PER_YEAR, MONTH_1, strlen(MONTH_1));

    printf ("1/9, rounded to 2 decimal places, "
            "is: %.2Lf\n", one_ninth);

    printf ("Musk once had a %d, then a %ld, and soon "
            "he'll have a %lld!\n",
            whoWantsToBeAMillionaire, billion, trillion);

    printf ("Since a numerical grade is non-negative "
            "and is a small number, we use an unsigned "
            "short variable, as with the grade: %hu.\n"
            "An unsigned int can only store a zero or "
            "a positive number.\n",
            grade);

    // Above, character sequences like:
    //    %f, %c, %d, %s, %u, ... 
    //    are called format specifiers and tell
    //    printf() what kind of a variable is being
    //    printed and at what location within the
    //    printout the variable should show up. This
    //    is the way C prints messages to the
    //    terminal similar to Java's concatenation
    //    using the plus (+) sign.
    // You can view the full list of specifiers of
    //    printf() at:
    // https://www.tutorialspoint.com/format-specifiers-in-c
    //
    // P.S., our course ain't about memorization.
    //    Whenever you do your homework assignments
    //    or work on exams, please feel free to
    //    simply consult the link above to find
    //    what specifier should be used if, for
    //    example, you want to print the value of,
    //    say, an unsigned long integer.

    return EXIT_SUCCESS;

    // The macro 'EXIT_SUCCESS', on most Linux
    //    computers, is defined as 0. That is,
    //    somewhere in the library <stdlib.h>,
    //    we will find the following #define
    //    statement (or something similar:)
    //
    // #define EXIT_SUCCESS 0
    //
    // Because there is no guarantee that '0',
    //    (as in 'return 0;') will keep
    //    signifying a successful termination
    //    of a program (e.g., '0' might be
    //    replaced by '1' in some future Linux
    //    devices as representing a successful
    //    termination,) we should, from now on,
    //    exit programs with:
    //
    // return EXIT_SUCCESS;
    //
    //    instead of:
    //
    // return 0;
    //
    //    because 'EXIT_SUCCESS' is a more
    //    portable (reliable) way of exiting
    //    the program.
}
