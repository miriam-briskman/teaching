// The following program exemplifies a call to the
//     select() system call. We wait (block) only
//     on one file: the keyboard (fd = 0 = STDIN_FILENO)
//     for 5 seconds. If the user types some content and
//     presses ENTER before the 5 seconds end, the 
//     content will be output to the terminal. Otherwise,
//     the 5 seconds will elapse, so the system call will
//     return without gathering input from the user.
//
// This program is taken from Linux System Programming:
//     Talking Directly to the Kernel and C Library, 
//     2nd Edition, by Love. ISNB: 978-1-44933953-1,
//     pages 55-56.

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#define TIMEOUT 5 /* select timeout in seconds */
#define BUF_LEN 1024 /* read buffer in bytes */

int main (void)
{
    struct timeval tv;
    fd_set readfds;
    int ret;
    
    /* Wait on stdin for input. */
    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);
    
    /* Wait up to five seconds. */
    tv.tv_sec = TIMEOUT;
    tv.tv_usec = 0;

    /* All right, now block! */
    ret = select (STDIN_FILENO + 1,
                  &readfds,
                  NULL,
                  NULL,
                  &tv);

    if (ret == -1)
    {
        perror ("select");
        exit (EXIT_FAILURE);
    }
    else if (!ret)
    {
        printf ("%d seconds elapsed.\n", TIMEOUT);
        return EXIT_SUCCESS;
    }

   /*
    * Is our file descriptor ready to read?
    * (It must be, as it was the only fd that
    * we provided and the call returned
    * nonzero, but we will humor ourselves.)
    */
    if (FD_ISSET(STDIN_FILENO, &readfds)) {
        char buf[BUF_LEN+1];
        int len;

        /* guaranteed to not block */
        len = read (STDIN_FILENO, buf, BUF_LEN);
        if (len == -1)
	{
            perror ("read");
            exit (EXIT_FAILURE);
        }

        if (len) // Same as if (len != 0)
	{
            buf[len] = '\0';
            printf ("read: %s\n", buf);
        }

        return EXIT_SUCCESS;
    }

    fprintf (stderr, "This should not happen!\n");
    return EXIT_FAILURE;
}
