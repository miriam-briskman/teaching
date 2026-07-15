// A program that registers the same handler for
//    SIGTERM and SIGINT. It also resets the
//    behavior for SIGPROF to the default (which
//    is to terminate the process) and ignores
//    SIGHUP (which would otherwise terminate
//    the process.)

// This program is taken from Linux System Programming:
//    Talking Directly to the Kernel and C Library, 
//    2nd Edition, by Love. ISNB: 978-1-44933953-1,
//    pages 343-344.

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

// Handler function for SIGINT and SIGTERM:
static void signal_handler (int signo)
{
    if (signo == SIGINT)
    {
        printf ("\nCaught SIGINT!\n");
        exit (EXIT_FAILURE);
    }
    else if (signo == SIGTERM)
        printf ("Caught SIGTERM!\n");
    else
    {
        /* This shouldn't happen. */
        fprintf (stderr,
                 "\nUnexpected signal: number #%d\n",
                 signo);
        exit (EXIT_FAILURE);
    }
}

int main (void)
{
    // Register 'sigint_handler' as our signal
    //    handler for SIGINT:
    if (signal (SIGINT, signal_handler) == SIG_ERR)
    {
        fprintf (stderr, "Cannot handle SIGINT!\n");
        exit (EXIT_FAILURE);
    }

    // Register 'sigint_handler' as our signal
    //    handler for SIGTERM:
    if (signal (SIGTERM, signal_handler) == SIG_ERR)
    {
        fprintf (stderr, "Cannot handle SIGTERM!\n");
        exit (EXIT_FAILURE);
    }

    // Reset SIGPROF's behavior to the default:
    if (signal (SIGPROF, SIG_DFL) == SIG_ERR)
    {
        fprintf (stderr, "Cannot reset SIGPROF!\n");
        exit (EXIT_FAILURE);
    }

    // Ignore SIGHUP:
    if (signal (SIGHUP, SIG_IGN) == SIG_ERR)
    {
        fprintf (stderr, "Cannot ignore SIGHUP!\n");
        exit (EXIT_FAILURE);
    }

    for (;;)
        pause ();

    return EXIT_SUCCESS;
}
