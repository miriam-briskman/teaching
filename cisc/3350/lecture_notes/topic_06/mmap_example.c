// The following program exemplifies the usage of
//     mmap(), which is used to memory-map a file
//     into main memory to use it as a variable
//     and munmap() which cancels this mapping.

// This program is taken from Linux System Programming:
//     Talking Directly to the Kernel and C Library, 
//     2nd Edition, by Love. ISNB: 978-1-44933953-1,
//     pages 109-110.

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

int main (int argc, char *argv[])
{
    struct stat file_info;
    off_t len;
    char *p;
    int file;

    // Check that the right number of arguments was
    //    passed:
    if (argc < 2)
    {
        fprintf (stderr,
                 "usage: %s <file>\n",
                 argv[0]);
        exit (EXIT_FAILURE);
    }

    // Open the file whose name was provided
    //    to the program in the command-line
    //    argument argv[1]:
    if ((file = open (argv[1], O_RDONLY)) == -1)
    {
        perror ("open");
        exit (EXIT_FAILURE);
    }

    // fstat() returns information about the file:
    if (fstat (file, &file_info) == -1)
    {
        perror ("fstat");
        exit (EXIT_FAILURE);
    }

    // The S_ISREG() macro checks if the given
    //    file is a regular file (and not a
    //    disk, socket, or other special file:)
    if (!S_ISREG (file_info.st_mode))
    {
        fprintf (stderr,
                 "%s is not a regular file\n",
                 argv[1]);
        exit (EXIT_FAILURE);
    }

    // sb.st_size contains the size of the file
    //    in bytes:
    p = mmap (0,
              file_info.st_size,
              PROT_READ,
              MAP_SHARED,
              file,
              0);
    if (p == MAP_FAILED)
    {
        perror ("mmap");
        exit (EXIT_FAILURE);
    }

    // Since the file was mapped to memory, we
    //    can start using the file as a variable,
    //    so we can close the file now.
    if (close (file) == -1)
    {
        perror ("close");
        exit (EXIT_FAILURE);
    }

    // We refer to the bytes of the file by
    //    using array notation p[len]. That is,
    //    the content of the file can now be
    //    referred to using array notation! It's
    //    both fast and convenient to use:
    for (len = 0; len < file_info.st_size; len++)
        putchar (p[len]); // Prints a char to screen.

    // Remove the mapping of the file from memory:
    if (munmap (p, file_info.st_size) == -1)
    {
        perror ("munmap");
        exit (EXIT_FAILURE);
    }

    return EXIT_FAILURE;
}
