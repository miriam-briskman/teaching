// The following program exemplifies a call to the
//     poll() system call. We wait (block) on 2 files:
//     the keyboard (fd = 0 = STDIN_FILENO) and the
//     screen (fd = 1 = STDOUT_FILENO) for 5 seconds.
//     We expect the screen to be responsive right
//     away, so we'll see the message: "stdout is
//     writable". Since poll() will return right
//     away, the program will soon thereafter end.
//     As such, to check also for the keyboard,
//     create some file (say, a .txt file) and
//     call the poll_syscall_example program this
//     way: ./poll_syscall_example < text.txt
//     where text.txt is the file you created. Then,
//     the following additional message will be
//     output: "stdin is readable" besides "stdout
//     is writable".
//
// This program is taken from Linux System Programming:
//     Talking Directly to the Kernel and C Library, 
//     2nd Edition, by Love. ISNB: 978-1-44933953-1,
//     pages 60-61.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <poll.h>

#define TIMEOUT 5 /* poll timeout, in seconds */

int main (void)
{
    struct pollfd fds[2];
    int ret;

    /* watch stdin for input */
    fds[0].fd = STDIN_FILENO;
    fds[0].events = POLLIN;

    /* watch stdout for ability to write (almost always true) */
    fds[1].fd = STDOUT_FILENO;
    fds[1].events = POLLOUT;

    /* All set, block! */
    ret = poll (fds, 2, TIMEOUT * 1000);

    if (ret == -1)
    {
        perror ("poll");
        exit (EXIT_FAILURE);
    }

    if (!ret) // Same as saying: if (ret == 0)
    {
        printf ("%d seconds elapsed.\n", TIMEOUT);
        return EXIT_SUCCESS;
    }

    if (fds[0].revents & POLLIN)
        printf ("stdin is readable\n");

    if (fds[1].revents & POLLOUT)
        printf ("stdout is writable\n");

    return EXIT_SUCCESS;
}
