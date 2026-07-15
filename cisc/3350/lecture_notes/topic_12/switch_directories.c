// A program switching the current directory D to
//    argv[1] and then back to the previous
//    directory D.

// This program is based on Linux System Programming:
//     Talking Directly to the Kernel and C Library, 
//     2nd Edition, by Love. ISNB: 978-1-44933953-1,
//     page 265.

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

#define BUF_SIZE 65000

int main (int argc, char * argv[])
{
    int swd_fd, ret;
    char cwd [BUF_SIZE];

    if (argc < 2)
    {
        fprintf (stderr,
                 "usage: %s <some directory's path>\n",
                 argv[0]);
        exit (EXIT_FAILURE);
    }

    // Get the current working directory:
    if (!getcwd (cwd, BUF_SIZE))
    {
        perror ("getcwd");
        exit (EXIT_FAILURE);
    }

    printf ("Current working directory: %s\n",
            cwd);

    // Open the current directory file:
    swd_fd = open (".", O_RDONLY);
    if (swd_fd == -1)
    {
        perror ("open");
        exit (EXIT_FAILURE);
    }

    // Change to a different directory:
    ret = chdir (argv[1]);
    if (ret)
    {
        perror ("chdir");
        exit (EXIT_FAILURE);
    }

    // Get the current working directory again:
    if (!getcwd (cwd, BUF_SIZE))
    {
        perror ("getcwd");
        exit (EXIT_FAILURE);
    }

    printf ("Updated current directory: %s\n",
            cwd);

    // Return to the saved directory:
    ret = fchdir (swd_fd);
    if (ret)
    {
        perror ("fchdir");
        exit (EXIT_FAILURE);
    }

    // Get the current working directory
    //    one more time:
    if (!getcwd (cwd, BUF_SIZE))
    {
        perror ("getcwd");
        exit (EXIT_FAILURE);
    }

    printf ("Finally, we are now back at: %s\n",
            cwd);

    // Close the directory's fd:
    ret = close (swd_fd);
    if (ret)
    {
        perror ("close");
        exit (EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
