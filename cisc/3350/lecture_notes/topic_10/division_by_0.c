/* A program that raises SIGFPE when we divide a
 *    number by 0.
 *
 *    Miriam Briskman, 4/26/2023
 *    CISC 3350, Brooklyn College
 *    Licensed under CC BY-NC 4.0
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

// Handler for the SIGFPE signal::
static void sigint_handler (int signo)
{
    // We shouldn't use the function printf() 
    //    in a signal handler; we use it here
    //    only for demonstration of how a
    //    handler works. We will see the reason
    //    that printf() shouldn't be used when
    //    we discuss the idea of reentrancy.
    printf ("Caught %d, which is SIGFPE!\n", signo);
    exit (EXIT_SUCCESS);
}

int main (void)
{
    // Register 'sigint_handler' as our signal
    //    handler for SIGFPE:
    if (signal (SIGFPE, sigint_handler) == SIG_ERR)
    {
        fprintf (stderr, "Cannot handle SIGFPE!\n");
        exit (EXIT_FAILURE);
    }

    printf ("Our favorite number in Math "
            "is: %d.\n", 1/0);

    pause ();

    return EXIT_SUCCESS;
}
