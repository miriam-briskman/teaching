/* This program exemplifies the vectored I/O
 *    readv() function. It assumes the existence
 *    of the file 'seasons.txt' within the current
 *    directory and that it has 3 lines of text in
 *    it. All 3 lines of text will be read in with
 *    the single system call readv(). Note that
 *    readv(), being a system call, works on file
 *    descriptors (as covered in Topic 4) and not
 *    on file pointers.
 *
 *    Miriam Briskman, 3/8/2023
 *    CISC 3350, Brooklyn College
 *    Licensed under CC BY-NC 4.0
 */

#include <stdio.h>     // printf(), perror()
#include <stdlib.h>    // EXIT_SUCCESS, EXIT_FAILURE
#include <fcntl.h>     // open(), O_RDONLY flag
#include <unistd.h>    // close()
#include <sys/uio.h>   // readv(), iovec structure

int main ()
{
    // To be able to use readv(), we first need
    //    to know how many characters we will be
    //    reading from each line:
    int sizes [3] = {38, 18, 30};

    int file, index;

    // An array of 3 strings. We will store the
    //    the lines that we read from the file
    //    in these strings:
    char * seasons [3];

    // Create those char arrays on the heap:
    for (index = 0; index < 3; index++)
        seasons[index] = malloc (sizes[index]
                                 * sizeof(char));

    struct iovec arr[3]; // Array of structures.

    // Open the file "seasons.txt" for reading:
    if ((file = open ("seasons.txt", O_RDONLY)) == -1)
    {
        perror ("open");
        exit (EXIT_FAILURE);
    }

    // To prepare for writing the 3 strings
    //    that we read from the file using
    //    vectored-i/o, we first need to
    //    fill out the three iovec structures
    //    that we created at the top of the
    //    program:
    for (index = 0; index < 3; index++)
    {
        arr[index].iov_base = seasons[index];
        arr[index].iov_len = sizes[index];
    }

    // Now, in one shot, we read in all the
    //    three strings from the file!
    if (readv (file, arr, 3) == -1)
    {
        perror ("readv");
        exit (EXIT_FAILURE);
    }

    // Print all the lines that we read in:
    for (index = 1; index < 4; index++)
        printf ("%d: %s", index, seasons[index - 1]);

    // Free the allocated 'seasons' arrays:
    for (index = 0; index < 3; index++)
        free (seasons[index]);

    // Close the file:
    if (close (file) == -1)
    {
        perror ("close");
        exit (EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
