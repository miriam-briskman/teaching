/* A C program that ignores the SIGINT signal using
 *    the sigaction() function.
 *
 *    Miriam Briskman, 4/30/2023
 *    CISC 3350, Brooklyn College
 *    Licensed under CC BY-NC 4.0
 */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    struct sigaction act;

    // Find the current action of SIGINT:
    if (sigaction (SIGINT, NULL, &act) == -1)
    {
        perror ("Could not obtain old action "
                "of SIGINT");
        exit (EXIT_FAILURE);
    }

    // If the action is the default (termination),
    //    change it to 'ignore':
    if (act.sa_handler == SIG_DFL)
    {
        act.sa_handler = SIG_IGN;
        if (sigaction (SIGINT, &act, NULL) == -1)
        {
            perror ("Could not ignore SIGINT");
            exit (EXIT_FAILURE);
        }
    }

    // Invoke sleep to try and kill the process
    //    with Ctrl+C. You'll see that Ctrl+C
    //    won't kill the program, because we set
    //    the program to ignore a SIGINT signal!
    sleep (10);

    printf ("\nThe result is %d.\n", 10/5);

    return EXIT_SUCCESS;
}
