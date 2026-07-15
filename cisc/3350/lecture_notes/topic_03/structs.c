/* A C program introducing C structs (structures).
 *
 *    Miriam Briskman, 2/8/2023
 *    CISC 3350, Brooklyn College
 *    Licensed under CC BY-NC 4.0
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h> // String library

// C's 'objects':
struct Student
{
    char name [100];
    int age;
    double GPA;
    char GPA_letter;
}; // <--- Don't forget the semi-colon here at
   //      the end of the structure definition!
  

// No methods can be defined within structs!
// You can only include variables, arrays,
//    and other stuctures. These are
//    collectively called 'data fields'.

int main ()
{
    // You may choose to initialize a structure (set
    //    the data fields of a new struct instance)
    //    of) inline using curly braces:
    struct Student std1 = {"Jane Doe", 20, 3.8, 'A'};
    
    // Or instantiate one without initializing it
    //    right away:
    struct Student std2;

    // At some later point in the program, you can
    //    start filling out the stucture's data. You
    //    can access data fields using the dot (.)
    //    notation:
    strcpy (std2.name, "Sean Chen");
    std2.age = 22;
    std2.GPA = 3.8;
    std2.GPA_letter = 'A';

    // Data fields of structs are used wherever
    //    you would use regular variables and
    //    arrays. For example, we can print them
    //    out:
    printf ("The student %s, who is %d years old, "
            "has %.3f GPA, which is %c.\n",
             std1.name, std1.age,
             std1.GPA, std1.GPA_letter);

    // Fact: All the data fields in a struct are
    //    always 'public': data fields can't be
    //    set to 'private' or 'protected' modes.

    // Aside from creating new structures,
    //    programmers in the Linux environment
    //    also frequently use existing structs
    //    that are defined in libraries. We will
    //    encounter more structures in future
    //    chapters and learn how we can use them!
    //
    // For example, when we cover Topic 9, we
    //    will learn that the time limit that
    //    a program is allowed to run on a
    //    Linux computer without being
    //    interrupted is represented by a struct
    //    called 'timespec', whose definition is
    //    already provided by the scheduling
    //    library of Linux (<sched.h>). The
    //    definition of this struct is:
    //
    //    struct timespec
    //    {
    //        time_t tv_sec; // seconds
    //        long tv_nsec; // nanoseconds
    //    };
    //
    // That is, this struct simply stores
    //    the duration of that time limit
    //    in seconds and nanoseconds.
    // Above, 'time_t' is a data type whose
    //    purpose is to store a number
    //    associated with seconds. Whether
    //    'time_t' is internally defined as
    //    an 'int', 'float', or 'double' is
    //    computer-specific (every computer
    //    might choose to define 'time_t' as
    //    it wishes.)

    return EXIT_SUCCESS;
}
