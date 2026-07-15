// A program that shows how a daemon process is
//    created in Linux.
//
// This program is taken from Linux System Programming:
//     Talking Directly to the Kernel and C Library, 
//     2nd Edition, by Love. ISNB: 978-1-44933953-1,
//     pages 173-174.

#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main (void)
{
    pid_t pid;
    int i;

    // Create new process:
    pid = fork ();
    if (pid == -1)
        return -1;
    else if (pid != 0)
        exit (EXIT_SUCCESS);

    // Create a new session and
    //    a process group:
    if (setsid () == -1)
        return -1;

    // Set the working directory to the
    //    root directory:
    if (chdir ("/") == -1)
        return -1;

    // OPEN_MAX contains the maximum possible
    //    number of files that are allowed to
    //    be opened by a single program in
    //    Linux:
    int OPEN_MAX = sysconf(_SC_OPEN_MAX);

    // Close all open files:
    for (i = 0; i < OPEN_MAX; i++)
        close (i);

    // Redirect fd's 0,1,2 (for stdin, stdout,
    //    and stderror) to /dev/null. This
    //    action disconnects the daemon from
    //    terminal i/o:
    open ("/dev/null", O_RDWR); /* stdin */
    dup (0); /* stdout */
    dup (0); /* stderror */

    /* do its daemon thing... */

    // Let's make the daemon sleep (exists without
    //    doing anything) for 30 seconds before it
    //    terminates:
    sleep(30);

    return EXIT_SUCCESS;
}
