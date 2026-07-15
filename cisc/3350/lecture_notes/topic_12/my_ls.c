// A program listing the contents of a directory.

// This program is based on Linux System Programming:
//     Talking Directly to the Kernel and C Library, 
//     2nd Edition, by Love. ISNB: 978-1-44933953-1,
//     page 270.

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

int main (int argc, char *argv[])
{
    struct dirent *entry;
    DIR *dir;

    if (argc == 1)
       dir = opendir (".");
    else
       dir = opendir (argv[1]);

    if (dir == NULL)
    {
        perror ("opendir");
        exit (EXIT_FAILURE);
    }
 
    errno = 0;

    while ((entry = readdir (dir)) != NULL)
    {
       printf ("%s\n", entry->d_name);
    }

    if (errno && !entry)
    {
        perror ("readdir");
        exit (EXIT_FAILURE);
    }

    if (closedir (dir) == -1)
    {
        perror ("closedir");
        exit (EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
