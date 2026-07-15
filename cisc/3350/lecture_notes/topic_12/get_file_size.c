// A program outputing the size of a file whose name is
//     passed as the 1st argument (argv[1]) to the
//     program.

// This program is taken from Linux System Programming:
//     Talking Directly to the Kernel and C Library, 
//     2nd Edition, by Love. ISNB: 978-1-44933953-1,
//     page 244.

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main (int argc, char *argv[])
{
    struct stat sb; // The 'statistics' stucture.
    int ret;

    if (argc < 2)
    {
        fprintf (stderr,
                 "usage: %s <file>\n",
                 argv[0]);
        exit (EXIT_FAILURE);
    }

    // Calling stat():
    ret = stat (argv[1], &sb);
    if (ret)
    {
        perror ("stat");
        exit (EXIT_FAILURE);
    }

    // The st_size field carries the size of the
    //     file in bytes.
    printf ("File size of %s: %ld bytes.\n",
            argv[1],
            sb.st_size);

    return EXIT_SUCCESS;
}
