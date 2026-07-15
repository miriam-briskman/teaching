/* Program writing a message to
 *    the console (screen).
 *
 *    Created for CISC 3350,
 *    Brooklyn College, 1/30/2023
 *    Licensed under CC0 1.0
 */

// Library defining perror() and other i/o actions:
#include <stdio.h>
// Library defining EXIT_FAILURE, EXIT_SUCCESS:
#include <stdlib.h>
// Library defining the 'write' system call:
#include <unistd.h>
// Library defining strlen():
#include <string.h>

int main (void) 
{ 
    const char *str = "Finished summoning the daemon!\n"
                      "Let it quietly die now.\n";
    if (write (STDOUT_FILENO, str, strlen (str)) == -1)
    {
        perror ("error with the \'write\' system call.\n");
        exit (EXIT_FAILURE); // Same as return 1;
    }

    return EXIT_SUCCESS; // Same as return 0; 
}
