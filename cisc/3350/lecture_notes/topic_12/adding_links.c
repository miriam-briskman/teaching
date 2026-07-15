/* A program that creates a hard link and a soft
 *    link for a file given at argv[1]. Both are
 *    created in the same directory where the
 *    original file is stored. The program then
 *    calls "ls -il" to show that the 2 links were
 *    created. Finally, the program removes both
 *    links and calls "ls -il" again.
 *
 *    Miriam Briskman, 5/10/2023
 *    CISC 3350, Brooklyn College
 *    Licensed under CC BY-NC 4.0
 */


#include <unistd.h> // chdir().
//#include <fcntl.h>  // 
#include <libgen.h> // dirname().
#include <string.h> // strlen(), strcpy().
#include <stdlib.h> // EXIT_SUCCESS, EXIT_FAILURE.
#include <stdio.h>  // perror(), printf(), fprintf().

#define BUF_SIZE 65000

int main (int argc, char *argv[])
{
    int ret;

    if (argc < 2)
    {
        fprintf (stderr,
                 "usage: %s <file>\n",
                 argv[0]);
        exit (EXIT_FAILURE);
    }

    // Creating an array to store a copy of argv[1].
    // We do this because dirname(), which we call
    //    later, may modify argv[1], which we don't
    //    want, so we need to keep a copy!
    char * pathcopy = malloc ((strlen (argv[1]) + 1)
                              * sizeof(char));
    if (pathcopy == NULL)
    {
        perror ("malloc");
        exit (EXIT_FAILURE);
    }

    // Copying argv[1] to pathcopy:
    pathcopy = strcpy (pathcopy, argv[1]);

    // Change the directory to the file's
    //    directory:
    ret = chdir (dirname (pathcopy));
    if (ret)
    {
        perror ("chdir");
        exit (EXIT_FAILURE);
    }

    // Create a hard link:
    ret = link (argv[1], "./hardlink");
    if (ret)
    {
        perror ("link");
        exit (EXIT_FAILURE);
    }

    // Create a soft link:
    ret = symlink (argv[1], "./symlink");
    if (ret)
    {
        perror ("symlink");
        exit (EXIT_FAILURE);
    }

    printf ("Content of the directory "
            "after adding the 2 links:\n");

    // Calling "ls -il":
    ret = system ("ls -il --color=auto");
    if (ret == -1)
    {
        perror ("system");
        exit (EXIT_FAILURE);
    }

    printf ("\nThe content of the file "
            "referenced by the hard link is:\n");

    // cat-ing the content of the hard link:
    ret = system ("cat hardlink");
    if (ret == -1)
    {
        perror ("system");
        exit (EXIT_FAILURE);
    }

    printf ("\n");

    printf ("The content of the file "
            "referenced by the soft link is:\n");

    ret = system ("cat symlink");
    if (ret == -1)
    {
        perror ("system");
        exit (EXIT_FAILURE);
    }

    // Removing the links:
    ret = unlink ("./hardlink");
    if (ret)
    {
        perror ("unlink");
        exit (EXIT_FAILURE);
    }

    ret = unlink ("./symlink");
    if (ret)
    {
        perror ("unlink");
        exit (EXIT_FAILURE);
    }

    printf ("\nContent of the directory "
            "after removing the links:\n");

    // Calling "ls -il" to confirm the links were removed:
    ret = system ("ls -il --color=auto");
    if (ret == -1)
    {
        perror ("system");
        exit (EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
