/* A C program that shows how condition
 *    statements (if, if-else, if-else-if,
 *    and switch) work.
 *
 *    Miriam Briskman, 2/8/2023
 *    CISC 3350, Brooklyn College
 *    Licensed under CC BY-NC 4.0
 */

#include <stdio.h>
#include <stdlib.h>

int main ()
{
    unsigned int salary = 58700;
	
    // If statement (if the condition is true,
    //    execute the statement that follows)
    if (salary >= 50000)
        printf ("This is a middle-class person.\n");

    // If-else statement (if the 'if' condition
    //    is false, execute the statement that
    //    follows the 'else':)
    if (salary < 32320)
        printf ("Below NYC's average salary.\n");
    else
        printf ("Above NYC's average salary.\n");

    // If-else-if statement:
    if (salary < 40000)
        printf ("Tax of 20%%.\n");
    else if (salary < 50000)
        printf ("Tax of 25%%.\n");
    else if (salary < 60000)
        printf ("Tax of 30%%.\n");
    else
        printf ("Tax of 35%%.\n");

    // Follow-up question:
    // Which salaries fall into the last
    //    'else' statement above?

    // [Note the double %% above. Since % is used
    //  to denote format specifiers like %d, it
    //  means that % is an escape character. To
    //  print the percentage sign on the screen,
    //  we need to escape %, which we do with
    //  %%.]

    // *~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*

    char letter_grade = 'B';

	
    /* Switch statements are efficient alternatives
          to if statements in the cases that we want
          to check for the equality of a variable to
          some value/number.
       In C, switch statements can work with char
          variables and with integers of all kinds!
    */

    printf ("The letter grade of %c indicates that "
            "the student ", letter_grade);         

    switch (letter_grade)
    {
        case 'F': printf ("Failed!\n"); break;
        case 'A': printf ("Excellently ");
        case 'D':
        case 'C':
        case 'B': printf ("Passed!\n"); break;
        case 'W': printf ("Withdrew!\n"); break;
        case 'P': printf ("Passed!\n"); break;
        case 'U': printf ("Unsatisfactory!\n"); break;
        case 'S': printf ("Satisfactory!\n"); break;
        default:  printf ("Error: this letter doesn't "
                          "correspond to any grade!\n");
    }

    // Follow-up question:
    // In the 'default' case above, why
    //    isn't there a need to use the 'break;'
    //    statement?

    return EXIT_SUCCESS;
}
