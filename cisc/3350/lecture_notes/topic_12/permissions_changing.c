/* A program changing the permissions of a file
 *    and printing the update to the terminal.
 *
 *    Miriam Briskman, 5/8/2023
 *    CISC 3350, Brooklyn College
 *    Licensed under CC BY-NC 4.0
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// Function prototype:
void print_permissions (struct stat);
int int_to_permissions (int);

int main (int argc, char *argv[])
{
    struct stat sb; // The 'statistics' stucture.
    int ret;

    if (argc < 3)
    {
        fprintf (stderr,
                 "usage: %s <file> <permissions "
                 "as a number: 777>\n",
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

    printf ("Current file permissions of %s:\n",
            argv[1]);
    print_permissions (sb);

    ret = chmod (argv[1],
                 int_to_permissions (atoi (argv[2])));
    if (ret)
    {
        perror ("chmod");
        exit (EXIT_FAILURE);
    }

    // Calling stat():
    ret = stat (argv[1], &sb);
    if (ret)
    {
        perror ("stat");
        exit (EXIT_FAILURE);
    }

    // Print the updated permissions of the file:
    printf ("Updated file permissions of %s:\n",
            argv[1]);
    print_permissions (sb);
    
    return EXIT_SUCCESS;
}

// A function printing the current permissions
//    of the file:
void print_permissions (struct stat sb)
{
    switch (sb.st_mode & S_IFMT)
    {
         case S_IFBLK:  printf("b");
                        break;
         case S_IFCHR:  printf("c");
                        break;
         case S_IFDIR:  printf("d");
                        break;
         case S_IFIFO:  printf("f");
                        break;
         case S_IFLNK:  printf("l");
                        break;
         case S_IFREG:  printf("-");
                        break;
         case S_IFSOCK: printf("s");
                        break;
         default:       printf("u");
    }

    printf ( (sb.st_mode & S_IRUSR) ? "r" : "-");
    printf ( (sb.st_mode & S_IWUSR) ? "w" : "-");
    printf ( (sb.st_mode & S_IXUSR) ? "x" : "-");
    printf ( (sb.st_mode & S_IRGRP) ? "r" : "-");
    printf ( (sb.st_mode & S_IWGRP) ? "w" : "-");
    printf ( (sb.st_mode & S_IXGRP) ? "x" : "-");
    printf ( (sb.st_mode & S_IROTH) ? "r" : "-");
    printf ( (sb.st_mode & S_IWOTH) ? "w" : "-");
    printf ( (sb.st_mode & S_IXOTH) ? "x" : "-");

    printf ("\n");
}

// A function that takes a numerical representation
//    of permissions, such as 644, and converts it
//    into a value that the chmod() function
//    understands.
// This value (integer) is returned by the function.
int int_to_permissions (int permissions)
{
    int res = 0;

    // First digit for the owner permissions:
    switch ((permissions % 1000) / 100)
    {
        case 0: break;
        case 1: res = res | S_IXUSR;
                break;
        case 2: res = res | S_IWUSR;
                break;
        case 3: res = res | S_IXUSR | S_IWUSR;
                break;
        case 4: res = res | S_IRUSR;
                break;
        case 5: res = res | S_IRUSR | S_IXUSR;
                break;
        case 6: res = res | S_IRUSR | S_IWUSR;
                break;
        case 7: res = res | S_IRUSR | S_IWUSR | S_IXUSR;
                break;
    }

    // 2nd digit for the group permissions:
    switch ((permissions % 100) / 10)
    {
        case 0: break;
        case 1: res = res | S_IXGRP;
                break;
        case 2: res = res | S_IWGRP;
                break;
        case 3: res = res | S_IXGRP | S_IWGRP;
                break;
        case 4: res = res | S_IRGRP;
                break;
        case 5: res = res | S_IRGRP | S_IXGRP;
                break;
        case 6: res = res | S_IRGRP | S_IWGRP;
                break;
        case 7: res = res | S_IRGRP | S_IWGRP | S_IXGRP; 
                break;
    }

    // 3rd digit for the others' permissions:
    switch (permissions % 10)
    {
        case 0: break;
        case 1: res = res | S_IXOTH;
                break;
        case 2: res = res | S_IWOTH;
                break;
        case 3: res = res | S_IXOTH | S_IWOTH;
                break;
        case 4: res = res | S_IROTH;
                break;
        case 5: res = res | S_IROTH | S_IXOTH;
                break;
        case 6: res = res | S_IROTH | S_IWOTH;
                break;
        case 7: res = res | S_IROTH | S_IWOTH | S_IXOTH;
                break;
    }

    return res;
}
