/* A program that creates a child process and
 *    sends it the SIGINT signal via kill().
 *    The child handles the SIGINT signal by
 *    calling the write() system call, which is
 *    reentrant. Finally, the parent sends a
 *    signal to itself using raise().
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

static void signal_handler_child (int signo)
{
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
}

static void signal_handler_parent (int signo)
{
    if (write (STDOUT_FILENO,
               "Parent: Received the signal: ",
               strlen("Parent: Received the signal: "))
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
}

int main ()
{
    printf ("Parent: Started executing now!\n");

    // Register signal_handler_parent as for
    //    SIGUSR1:
    if (signal (SIGUSR1, signal_handler_parent)
        == SIG_ERR)
    {
        fprintf (stderr, "Cannot handle SIGUSR1!\n");
        exit (EXIT_FAILURE);
    }

    // Fork (create) a child process:
    pid_t childpid = fork();
    if (childpid == -1)
    {
        perror ("fork");
        exit (EXIT_FAILURE);
    }
    // We enter this 'if' only inside the parent process:
    else if (childpid)
    {
        printf ("Parent: A child with "
                "pid = %d was forked!\n",
                childpid);
        // Check if we have the permission to send
        //    signals to the child:
        int ret = kill (childpid, 0);
        if (ret)
        {
            fprintf (stderr,
                     "We can't send signals "
                     "to the child.\n");
        }
        else
        {
            // Wait several seconds for the child to
            //    launch:
            sleep(5);
            // Send SIGINT to the child:
            printf ("Parent: I'll send SIGINT to "
                    "the child now!\n");
            ret = kill (childpid, SIGINT);
            if (ret)
            {
                perror ("kill");
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
            printf ("Parent: It was killed by the "
                    "signal = %d%s.\n",
                    WTERMSIG (status),
                    WCOREDUMP (status) ? " (dumped core)" : "");
        if (WIFSTOPPED (status))
            printf ("Parent: It was stopped by the "
                    "signal = %d.\n",
                    WSTOPSIG (status));
        if (WIFCONTINUED (status))
            printf ("Parent: Its execution "
                    "continued.\n");

        printf ("Parent: I'll send SIGUSR1 "
                "to myself now!\n");
        // Send SIGUSR1 to itself (the parent):
        ret = raise (SIGUSR1);
        if (ret)
        {
            fprintf (stderr,"raise() failed.\n");
            exit (EXIT_FAILURE);
        }
    }
    else // We are inside the child process:
    {
        printf ("Child: Started executing now! "
                "My pid is %d.\n",
                getpid());

        // Register signal_handler_child for SIGINT:
        if (signal (SIGINT, signal_handler_child)
            == SIG_ERR)
        {
            fprintf (stderr, "Cannot handle SIGINT!\n");
            exit (EXIT_FAILURE);
        }
        printf ("Child: I just changed "
                "the action of SIGINT.\n");
        // Wait for the signal to be sent
        //    by the parent:
        pause();
        printf ("Child: Returning...\n");
    }

    return EXIT_SUCCESS;
}
