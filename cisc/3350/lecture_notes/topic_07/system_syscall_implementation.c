/* A C program that implements the system() system
 *    call and attempts to use it to run the
 *    command whose name is passed as the
 *    command-line argument to the program.
 *
 *
 *    Miriam Briskman, 3/15/2023
 *    CISC 3350, Brooklyn College
 *    Licensed under CC BY-NC 4.0
 */

#include <sys/types.h> // pid_t, gid_t, etc.
#include <unistd.h>    // Defines some system calls.
#include <sys/wait.h>  // wait(), waitpid(), etc.
#include <stdio.h>     // perror(), printf(), fprintf().
#include <stdlib.h>    // EXIT_SUCCESS, EXIT_FAILURE.

/*
 *  my_system - synchronously spawns and waits for
 *  the command "/bin/sh -c <cmd>".
 *
 *  Returns −1 on error of any sort, or the exit
 *  code from the launched process. Does not block
 *  or ignore any signals.
 *
 *  This function is taken from Linux System Programming:
 *  Talking Directly to the Kernel and C Library, 
 *  2nd Edition, by Love. ISNB: 978-1-44933953-1,
 *  pages 55-56.
 */
int my_system (char * const cmd)
{
    int status;
    pid_t pid;

    pid = fork ();
    if (pid == -1)
        return -1;

    else if (pid == 0)
    {
        char * argv[4];
        argv[0] = "sh";
        argv[1] = "-c";
        argv[2] = cmd;
        argv[3] = NULL;
        execv ("/bin/sh", argv);
        exit (-1);
    }

    if (waitpid (pid, &status, 0) == -1)
        return -1;
    else if (WIFEXITED (status))
        return WEXITSTATUS (status);

    return -1;
}

int main (int argc, char * argv[])
{
    if (argc == 1)
    {
        fprintf (stderr,
                 "Usage:\n\t%s someCommand\n"
                 "where someCommand is replaced by "
                 "some Linux command.\n",
                 argv[0]);
        return EXIT_FAILURE;
    }

    // Executing the command that was passed as
    //    the command-line argument argv[1]:
    int ret = my_system (argv[1]);

    printf ("The command returned the "
            "status: %d.\n",
            ret);

    return EXIT_SUCCESS;
}
