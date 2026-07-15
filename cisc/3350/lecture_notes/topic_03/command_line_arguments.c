/* This program shows how to work with command-line
 *    arguments. So far, we haven't touched this
 *    aspect of C-programming, but, as we will
 *    learn later in this course, command-line
 *    arguments turn out to be super useful and
 *    convenient to use!
 *
 *    Miriam Briskman, 2/8/2023
 *    CISC 3350, Brooklyn College
 *    Licensed under CC BY-NC 4.0
 */

#include <stdio.h>
#include <stdlib.h>

/* In the header of the main() function:
   (1) 'argc' has the amount of command-line
       arguments that were passed to the
       program.
   (2) 'argv' is an array of strings carrying
       the arguments themselves.
*/
int main (int argc, char * argv[]) 
{
    /* FAQ:
       Q: Why do we need to have 'int argc',
          and cannot have 'char * argv[]' alone?
       A: Because in C, we need to maintain a
          counter for the number of elements in
          an array, since arrays/strings in C are
          not objects, unlike their Java counterparts.
          In Java, the String object has an accessible
          size data type, which C doesn't have, so
          we must keep track of the number of items
          in this array.

       Q: How do you run a program with command
          line arguments?
       A: Suppose that you compile a certain C
          file called 'prog.c' as:
                  gcc -o prog prog.c
          You would then run it as:
                  ./prog
          In this case, you'd have a single
          command-line argument provided to
          the program:
          argv[0] ---> "./prog"

          If you want to add more command-line
          arguments, you would run it like:
                  ./prog hello hi 2 -18.5
          You now have 5 command-line
          arguments:
          argv[0] ---> "./prog"
          argv[1] ---> "hello"
          argv[2] ---> "hi"
          argv[3] ---> "2"
          argv[4] ---> "-18.5"

          All of the command-line arguments are
          provided as char arrays (strings).
          For instance, if you want to assign
          argv[3] to an int variable, you first
          need to convert the string to an int.
          One such C function that converts a
          string to an integer is atoi(), which
          is defined in the library <stdlib.h>.
          More on atoi() here:
          https://cplusplus.com/reference/cstdlib/atoi/

          Fun fact: You've been calling C
          programs with arguments all along!

          When you type:
                ls -a
          in the Linux terminal, you run a
          program called "ls" and provide
          the argument "-a" to it, which
          instructs "ls" to print the contents
          of the directory, including hidden
          files (files whose names start with
          a dot (.))
          Isn't it cool?
    */

    // Let's print how many arguments are provided:
    printf ("The amount of command line arguments "
            "is: %d\n", argc);
    // The 1st command line argument is ALWAYS the
    //    name of the executable (= C program:)
    printf ("The name of this program is: %s\n",
            argv[0]);

    // Therefore, there is ALWAYS going to be at
    //    least one argument provided to the
    //    program! We simply ignored it so far.
    // This also means that 'argc' is going to be
    //    equal to 1 or greater.
    
    // Note that, just as in Java, array indices
    //    begin with 0, so argv[0] is the first
    //    argument, argv[1] is the 2nd argument,
    //    etc.

    // Finally, let's print the rest of the command
    //    -line arguments (if such exist):
    if (argc == 1)
        printf ("No command line arguments passed "
                "besides the program's name.\n");
    else
    {
        int i;
        for (i = 1; i < argc; i++)
            printf ("Argument number %d is: "
                    "%s\n", i + 1, argv[i]);
    }

    // After compiling this source code, we will 
    //    run this program with a few command-line
    //    arguments.

    // Follow-up question:
    // What do you think will happen when we provide
    //    2 or more of our space-separated arguments
    //    in quotes, like: "wow yummy"?
    //    For instance:
    //        ./command_line_arguments "wow yummy"
    //
    //    How many arguments will such a quoted
    //    string result in: will they still be
    //    considered as two separate arguments?

    return EXIT_SUCCESS;
}
