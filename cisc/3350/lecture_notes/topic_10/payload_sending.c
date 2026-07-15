/* A program that creates a child process and
 *    sends it the SIGUSR2 signal with a payload
 *    that the user types via the terminal.
 *
 *    Miriam Briskman, 4/30/2023
 *    CISC 3350, Brooklyn College
 *    Licensed under CC BY-NC 4.0
 */

#include <unistd.h>   // write().
#include <sys/wait.h> // waitpid().
#include <stdio.h>    // perror(), printf(), fprintf().
#include <stdlib.h>   // EXIT_SUCCESS, EXIT_FAILURE.
#include <string.h>   // strlen().
#include <signal.h>   // sigqueue(), sigval struct.

void signal_handler_child (int signo,
                           siginfo_t *si,
                           void *ucontext)
{
    // Let the compiler know ucontext is unused:
    (void)(ucontext);

    // write() is a reentrant function, so we can
    //    use it safely instead of using printf():
    if (write (STDOUT_FILENO,
               "Child: Received the signal: ",
               strlen("Child: Received the signal: "))
        == -1 ||
        write (STDOUT_FILENO,
               sys_siglist[signo],
               strlen(sys_siglist[signo]))
        == -1 ||
        write (STDOUT_FILENO,
               ".\n",
               strlen(".\n"))
        == -1)
    {
        perror ("write");
        exit (EXIT_FAILURE);
    }

    char buffer[20];
    sprintf (buffer, "%d", si->si_int);

    // Print some siginfo information:
    if (write (STDOUT_FILENO,
               "Child: The recevied payload is: ",
               strlen("Child: The received payload is: "))
        == -1 ||
        write (STDOUT_FILENO,
               buffer,
               strlen(buffer))
        == -1 ||
        write (STDOUT_FILENO,
               ".\n",
               strlen(".\n"))
        == -1)
    {
        perror ("write");
        exit (EXIT_FAILURE);
    }
}

int main ()
{
    printf ("Parent: Started executing now!\n");

    union sigval value; // The sigval union struct.

    // Ask the user to type an integer via
    //    the keyboard:
    printf ("Parent: please enter an integer: >> ");
    scanf ("%d", &(value.sival_int));

    printf ("Parent: I'll send the number you "
            "entered: %d to the child!\n",
            value.sival_int);

    // Fork (create) a child process:
    pid_t childpid = fork();
    if (childpid == -1)
    {
        perror ("fork");
        exit (EXIT_FAILURE);
    }
    // We enter this 'if' only inside the parent
    //    process:
    else if (childpid)
    {
        printf ("Parent: A child with "
                "pid = %d was forked!\n",
                childpid);
        // Check if we have the permission to
        //    send signals to the child:
        int ret = sigqueue (childpid, 0, value);
        if (ret)
        {
            fprintf (stderr,
                     "We can't send signals "
                     "to the child.\n");
        }
        else
        {
            // Wait several seconds for the child
            //    to launch:
            sleep(5);
            // Send SIGINT to the child:
            printf ("Parent: I'll send SIGUSR2 "
                    "to the child now!\n");
            ret = sigqueue (childpid,
                            SIGUSR2,
                            value);
            if (ret)
            {
                perror ("sigqueue");
                exit (EXIT_FAILURE);
            }
        }

        // Wait for the child to return:
        int status;
       
        pid_t temp = waitpid (childpid, &status, 0);
        if (temp == -1)
        {
            perror ("waitpid");
            exit (EXIT_FAILURE);
        }

        printf ("Parent: The child that just "
                "returned has the pid = %d.\n",
                temp);

        // Let's check what happened with the child:
        if (WIFEXITED (status))
            printf ("Parent: It terminated normally "
                    "with the exit status = %d.\n",
                    WEXITSTATUS (status));
        if (WIFSIGNALED (status))
            printf ("Parent: It was killed by "
                    "the signal = %d%s.\n",
                    WTERMSIG (status),
                    WCOREDUMP (status) ? " (dumped core)" : "");
        if (WIFSTOPPED (status))
            printf ("Parent: It was stopped "
                    "by the signal = %d.\n",
                    WSTOPSIG (status));
        if (WIFCONTINUED (status))
            printf ("Parent: Its execution "
                    "continued.\n");
    }
    else // We are inside the child process:
    {
        printf ("Child: Started executing now! "
                "My pid is %d.\n",
                getpid());

        struct sigaction act;
        act.sa_flags = SA_SIGINFO;
        act.sa_sigaction = signal_handler_child;

        // Register signal_handler_child:
        if (sigaction (SIGUSR2, &act, NULL) == -1)
        {
            perror ("Cannot handle SIGUSR2!\n");
            exit (EXIT_FAILURE);
        }
        printf ("Child: I just changed the "
                "action of SIGUSR2.\n");
        // Wait for the signal to be sent
        //    by the parent:
        pause();
        printf ("Child: Returning...\n");
    }

    return EXIT_SUCCESS;
}
