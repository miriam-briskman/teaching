/* Simple C program to display "Hello, World!" 
 *    
 *    Miriam Briskman, 1/6/2024
 *    CISC 3350, Brooklyn College
 *    Licensed under CC BY-NC 4.0
 */

// A one-line C comment starts with: //
// Just like this line and the line above!

// A multiline C comment starts with /*
//    and ends with */ like:
/*
   This
   comment!
*/
// Comments are skipped by the compiler, 
//    so only non-comment code is executed.
 
// Include a reference to C's standard
//    input & output library without which no
//    messages can be printed to the screen.
#include <stdio.h> 

// main function: the execution of program
//    begins here:
int main() 
{ 
    // Print "Hello, World!" followed by
    //    a newline character:
    printf ("Hello, World!\n"); 

    // Exit the program with 0 as a message,
    //    showing that the execution was
    //    successful:
    return 0; 
}
