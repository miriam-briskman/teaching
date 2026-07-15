/* This program exemplifies the vectored I/O
 *    writev() function. It writes 3 lines of text
 *    into a file using the single system call
 *    writev(). Note that writev(), being a system
 *    call, works on file descriptors (as covered
 *    in Topic 4) and not on file pointers.
 *
 *    Miriam Briskman, 3/8/2023
 *    CISC 3350, Brooklyn College
 *    Licensed under CC BY-NC 4.0
 */

#include <stdio.h>     // printf(), perror()
#include <stdlib.h>    // EXIT_SUCCESS, EXIT_FAILURE
#include <sys/types.h> // ssize_t type
#include <fcntl.h>     // creat()
#include <string.h>    // strlen()
#include <unistd.h>    // close()
#include <sys/uio.h>   // writev(), iovec structure

int main ()
{
    struct iovec arr[3]; // Array of structures.
    ssize_t num; // ssize_t is usually implemented
                 // as an integer. We need one
                 // because writev() returns a
                 // ssize_t variable, so we need
                 // it to store this value.
    int file, index;

    // An array containing 3 string literals:
    char *buf[] = {
        "Winter ended a couple of months ago.\n",
        "It's spring now!\n",
        "Summer is behind the corner!\n"
    };

    // Create a new file:
    if ((file = creat ("seasons.txt", 0644)) == -1)
    {
        perror ("open");
        exit (EXIT_FAILURE);
    }

    // To prepare for writing the 3 strings
    //    above at once into a file using
    //    vectored-i/o, we first need to
    //    fill out the three iovec structures
    //    that we created at the top of the
    //    program:
    for (index = 0; index < 3; index++)
    {
        arr[index].iov_base = buf[index];
        arr[index].iov_len = strlen (buf[index]) + 1;
    }

    // Now, in one shot, we write out all the
    //    three strings into the file!
    if ((num = writev (file, arr, 3)) == -1)
    {
        perror ("writev");
        exit (EXIT_FAILURE);
    }

    printf ("We wrote out %d bytes!\n", (int) num);

    if (close (file) == -1)
    {
        perror ("close");
        exit (EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
