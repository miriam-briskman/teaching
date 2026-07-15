// A program demonstrating the call to wait().
//
// This program is taken from Linux System Programming:
//     Talking Directly to the Kernel and C Library, 
//     2nd Edition, by Love. ISNB: 978-1-44933953-1,
//     page 153.

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main (void)
{
    int status;
    pid_t pid;

    // The statement below (1) forks a child process,
    //    (2) terminates it right away, and (3) makes
    //    the child return with the return value of 1.
    // The reason that the child (and not the parent) is
    //    terminated is that the 'if' statement asks
    //    whether the returned value from fork() is 0,
    //    which is only true inside the child's process
    //    (since, inside the parent, fork() returns the
    //    pid of the child which is never 0,) so only
    //    the child enters this 'if' statement, which
    //    causes it execute 'exit (EXIT_FAILURE)'.
    if (!fork ())
        exit (EXIT_FAILURE);

    // The wait() system call waits for any of this
    //    process's children to return. Since this
    //    process created only 1 child, we will
    //    necessaily wait for this one child.
    if ((pid = wait (&status)) == -1)
    {
        perror ("wait");
        exit (EXIT_FAILURE);
    }

    printf ("pid = %d\n", pid);

    // The following 'if' statements are commonly used
    //    to check the status of the returned child.
    //    Each of the functions WEXITSTATUS(),
    //    WTERMSIG(), etc., will look into the 'status'
    //    integer to find whether the bits of 'status'
    //    indicate that the child returned in some
    //    either nominal or abnormal way.
    // It is advised that you include these statements
    //    after any instance of calling wait(),
    //    waitpid(), etc., to find the details about
    //    the return of every child.
    if (WIFEXITED (status))
        printf ("Normal termination with the exit "
                "status = %d.\n",
                WEXITSTATUS (status));
    if (WIFSIGNALED (status))
        printf ("Killed by the signal = %d%s.\n",
                WTERMSIG (status),
                WCOREDUMP (status) ? " (dumped core)" : "");
    if (WIFSTOPPED (status))
        printf ("Stopped by the signal = %d.\n",
                WSTOPSIG (status));
    if (WIFCONTINUED (status))
        printf ("Continued.\n");

    return EXIT_SUCCESS;
}
