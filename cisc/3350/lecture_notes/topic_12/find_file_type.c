// A program outputing the type of a file whose name is
//     passed as the 1st argument (argv[1]) to the
//     program.

// This program is taken from Linux System Programming:
//     Talking Directly to the Kernel and C Library, 
//     2nd Edition, by Love. ISNB: 978-1-44933953-1,
//     pages 244-245.

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

     ret = stat (argv[1], &sb); // Calling stat().
     if (ret)
     {
         perror ("stat");
         exit (EXIT_FAILURE);
     }

     printf ("File type of %s: ", argv[1]);

     // Below, we do a bitwise AND (using &) to
     //    extract only the file type out of the
     //    st_mode field (which also contains
     //    information about file permission, but
     //    we don't need them now so we ignore
     //    them.)
     // See a more complete explanation at:
     //    https://stackoverflow.com/a/31449965/14167156
     switch (sb.st_mode & S_IFMT)
     {
         case S_IFBLK:  printf("block device node.\n");
                        break;
         case S_IFCHR:  printf("character device node.\n");
                        break;
         case S_IFDIR:  printf("directory.\n");
                        break;
         case S_IFIFO:  printf("FIFO (a queue).\n");
                        break;
         case S_IFLNK:  printf("symbolic link.\n");
                        break;
         case S_IFREG:  printf("regular file.\n");
                        break;
         case S_IFSOCK: printf("socket.\n");
                        break;
         default:       printf("unknown.\n");
    }
 
    return EXIT_SUCCESS;
}
