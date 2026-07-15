// A program that handles SIGINT by printing a
//    message, and then terminating the program.
 
// This program is taken from Linux System Programming:
//    Talking Directly to the Kernel and C Library, 
//    2nd Edition, by Love. ISNB: 978-1-44933953-1,
//    page 342.

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

// Handler function for SIGINT:
static void sigint_handler (int signo)
{
    // We shouldn't use the function printf() 
    //    in a signal handler; we use it here
    //    only for demonstration of how a
    //    handler works. We will see the reason
    //    that printf() shouldn't be used when
    //    we discuss the idea of reentrancy.
    printf ("\nCaught %d, which is SIGINT!\n",
            signo);
    exit (EXIT_SUCCESS);
}

int main (void)
{
    // Register 'sigint_handler' as our signal
    //    handler for SIGINT:
    if (signal (SIGINT, sigint_handler) == SIG_ERR)
    {
        fprintf (stderr, "Cannot handle SIGINT!\n");
        exit (EXIT_FAILURE);
    }

    printf ("To activate the SIGINT signal, "
            "press Ctrl+C.\n");

    for (;;)
        pause ();

    return EXIT_SUCCESS;
}
