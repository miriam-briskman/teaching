/* A program printing all the extended attributes
 *    of the file at argv[1] and their values.
 *
 *    Miriam Briskman, 5/8/2023
 *    CISC 3350, Brooklyn College
 *    Licensed under CC BY-NC 4.0
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/xattr.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define BUF_SIZE 32000

int main (int argc, char *argv[])
{
    ssize_t ret;

    if (argc < 2)
    {
        fprintf (stderr,
                 "usage: %s <file>\n",
                 argv[0]);
        exit (EXIT_FAILURE);
    }

    // Setting an extended attribute:
    int result = setxattr (argv[1],
                           "user.slogan",
                           "Hello World!",
                           12,
                           0);
    if (result == -1)
    {
        perror ("setxattr");
        exit (EXIT_FAILURE);
    }

    // Follow-up question:
    // According to our lecture notes
    //    about setxattr():
    //    (a) What does '12' above stand for?
    //    (b) What does '0' above stand for?

    // Creating a buffer of this size:
    char * buffer = malloc (BUF_SIZE * sizeof(char));
    if (buffer == NULL)
    {
        perror ("malloc");
        exit (EXIT_FAILURE);
    }

    // Creating a buffer for the values of
    //    attributes:
    char * value = malloc (BUF_SIZE * sizeof(char));
    if (value == NULL)
    {
        perror ("malloc");
        exit (EXIT_FAILURE);
    }

    // Find all the extended attributes of argv[1]:
    ret = listxattr (argv[1],
                     buffer,
                     BUF_SIZE);
    if (ret == -1)
    {
        perror ("listxattr");
        exit (EXIT_FAILURE);
    }

    printf ("The keys of the extended attributes "
            "are:\n%s\n",
            buffer);

    int i = 0, j = 0, n = 1;

    char temp [BUF_SIZE]; // A temporary buffer

    // Print all the attributes' keys + values:
    while (i < ret)
    {
        temp[j] = buffer[i];

        if (buffer[i] == '\0')
        {
            // Get the key and value of the
            //    attribute:
            ssize_t res = getxattr (argv[1],
                                    temp,
                                    (void *) value,
                                    BUF_SIZE);
            if (res == -1)
            {
                perror ("getxattr");
                exit (EXIT_FAILURE);
            }

            // Print the attribute:
            printf ("Attribute #%d: %s ---> %s\n",
                    n,
                    temp,
                    value);

            n++;
            j = -1;
        }

        j++;
        i++; 
    }

    free (buffer);
    free (value);

    return EXIT_SUCCESS;
}
