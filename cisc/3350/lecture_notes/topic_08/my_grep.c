// CISC 3350: HW 5 Assignment Program
//
// Instructions: Below each one of the Task boxes 1-6,
//               write the code that the task describes.
//               After the lines of code are (correctly)
//               added, the program will compile and
//               run correctly.
//               In each of the tasks, you'll write
//               anywhere between 1 to 7 lines of code.
//               Note:
//               Don't change or delete any existing code.

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>

// Constants:
#define MAX_NUM 32768 // Maximum number of files allowed in my_grep
#define BUF_SIZE 4001 // Maximum length allowed for a line read from
                      //     a file (including the null character)

// Global Variables:
char * PATTERN; // Will point at the string that we search for.
long long total_lines_read = 0; // By the end of the program
                                //    will contain the total
                                //    number of lines that were
                                //    searched by all threads.

// Mutexes:
/************************************************************\
|*                          Task 1                          *|
|* Right below this comment, define and intialize a mutex   *|
|*    variable. Name this mutex as you wish.                *|
|* This mutex variable will be used to synchronize the      *|
|*    activities of the threads and prevent them from       *|
|*    corrupting the data in the global (shared) variable   *|
|*    'total_lines_read' that we defined above.             *|
\************************************************************/










// Function: 'searchfile'
// Input: filename (void *)
// Output: pointer to number of lines searched in file
// Purpose: each thread will run this function and will
//          search for the pattern inside the file
//          whose name is passed in 'filename', write
//          the lines of text where PATTERN was found to
//          stdout, and return the number of lines
//          where PATTERN was found.
void * searchfile (void * filename)
{
    // Declare a buffer:
    char *buffer;
         //*tempPtr; // general purpose char pointer
    // and variable to hold buffer length:
    int buffer_len;
    // A file pointer:
    FILE * infile;
    // Also, variable holding number of matched lines:
    long long matching = 0;

    // Allocate memory for the char buffer:
    if ((buffer = (char*) malloc (BUF_SIZE * sizeof (char))) == NULL)
    {
        perror ("my_grep: malloc");
        exit (EXIT_FAILURE);
    }

    // Cast filename to (char*) and open the file
    if ((infile = fopen ((char*) filename, "r")) == NULL)
    {
        perror ("my_grep: fopen");
        free (buffer);
        exit (EXIT_FAILURE);
    }

    // Using 'fgets' loop to read from file:
    while (fgets (buffer, BUF_SIZE, infile) != NULL)
    {
       /************************************************************\
       |*                          Task 2                          *|
       |* Right below this comment, acquire the lock of the mutex  *|
       |*    variable you defined in Task 1. That is, add code     *|
       |*    that will lock-up the 'total_lines_read++;' line and  *|
       |*    therefore, will allow only one thread at a time to    *|
       |*    execute this line.                                    *|
       \************************************************************/










       // Increment the total number of read lines.
       //    Race conditions happen with this code line,
       //    which is why we lock this statement using a mutex.
       total_lines_read++;

       /************************************************************\
       |*                          Task 3                          *|
       |* Right below this comment, release the lock of the mutex  *|
       |*    variable you defined in Task 1.                       *|
       \************************************************************/








      
       // Finding the length of the line:
       buffer_len = strlen(buffer);
      
       // Case when the line is longer than 4000 chars (disallowed):
       if (buffer_len == BUF_SIZE - 1 && buffer[BUF_SIZE - 2] != '\n')
       {
           fprintf (stderr, "my_grep: An excessively long line was detected. Returning from thread...\n");
           free (buffer);
           exit (EXIT_FAILURE);
       }
       // Case when empty line is read in (allowed; continue reading new lines)
       else if (buffer_len == 1 && buffer[0] == '\n')
           continue;
      
       // If a match was found, print the line.
       if (strstr(buffer, PATTERN) != NULL)
       {
          printf ("%s: %s", (char *) filename, buffer);
    
          // Increment the number of matches: 
          matching++;
       }
    } // End of while loop

    // Dealocating memory:
    free (buffer);
    // Closing files:
    fclose (infile);

    // Print out how many matchings were found in this file:
    printf ("--%s has %lld matched lines\n", (char *) filename, matching);

    // Finally, exit the thread and return a pointer to the # of matching lines:
    /************************************************************\
    |*                          Task 4                          *|
    |* Right below this comment, call pthread_exit() to exit    *|
    |*    'searchfile' (and, thus, terminate the thread.)       *|
    |*    Remember that pthread_exit() takes a single argument  *|
    |*    representing the return value of 'searchfile'.        *|
    |*    The goal of a thread is to return the variable that   *|
    |*    contains the number of lines that the thread found    *|
    |*    that match the provided pattern.                      *|
    \************************************************************/









} // End of 'searchfile'

// Main function:
int main (int argc, char *argv[])
{
    // Check if we have the right number of arguments (at least 3)
    if (argc < 3)
    {
        fprintf (stderr, "my_grep: at least 3 arguments must be passed!\n"); 
        exit (EXIT_FAILURE);
    }
    // At this point, we know that argc >= 3.
    // However, we must make sure that the number of files is not too big:
    if (argc > MAX_NUM)
    {
        fprintf (stderr, "my_grep: too many filenames were passed!\n");
        exit (EXIT_FAILURE);
    }

    // Variable declaration:
    pthread_t *threads;   // Pointer to threads array that will be created
    long long result,     // Will hold returned values from 'pthread' functions
              sum = 0,    // Sum of total matches returned from the threads
              i;          // Loop index
    void *lines;          // Number of matching lines returned by a thread

    // Allocating memory for the PATTERN string:
    if ((PATTERN = (char*) malloc (strlen(argv[1]) * sizeof(char))) == NULL)
    {
        perror ("my_grep: malloc:");
        exit (EXIT_FAILURE);
    }

    // Copying the string in argv[1] into PATTERN:
    if (strcpy (PATTERN, argv[1]) == NULL)
    {
        fprintf (stderr, "my_grep: strcpy failed!\n");
        free (PATTERN);
        exit (EXIT_FAILURE);
    }

    // Allocate the threads array on the heap:
    if ((threads = (pthread_t*) malloc ((argc - 2) * sizeof (pthread_t))) == NULL)
    {
       perror ("my_grep: malloc:");
       free (PATTERN);
       exit (EXIT_FAILURE);
    }

    // In a loop, create threads, each for each filename
    //    (for a total of argc - 2 threads) to search the files.
    for (i = 0; i < argc - 2; i++)
    {
       /************************************************************\
       |*                          Task 5                          *|
       |* Right below this comment, call pthread_create() to       *|
       |*    create threads that will read each file and search    *|
       |*    for the pattern in it. Note that the thread variables,*|
       |*    'threads', were already created and allocated above.  *|
       |* These calls to pthread_create() shouldn't receive any    *|
       |*    special attributes, so you can pass NULL for the      *|
       |*    attributes argument. The goal of each thread is to    *|
       |*    run the 'searchfile' function, which accepts the name *|
       |*    of the input file that the thread should read.        *|
       |* Note that the names of the files are provided in the     *|
       |*    command line arguments argv[2], argv[3], argv[4], ... *|
       |*    and that the argument to 'searchfile' must be cast    *|
       |*    to (void *) just as the examples on slides 42 and 44  *|
       |*    in our lecture notes show.                            *|
       |* Finally, your code must check for errors: if             *|
       |*    pthread_create() returns a number other than 0, your  *|
       |*    code must print the error message, free() the PATTERN *|
       |*    and 'threads' arrays, (since they were                *|
       |*    allocated with malloc(), so we must free them,) and   *|
       |*    exit the program with EXIT_FAILURE. See slide 44 for  *|
       |*    a proper way to check for pthread_create() errors.    *|
       \************************************************************/










    }

    // If we reached this line, all threads were successfully created.
    // Then, after the threads run, we have to join them:
    for (i = 0; i < argc - 2; i++)
    {
       /************************************************************\
       |*                          Task 6                          *|
       |* Right below this comment, call pthread_join() to         *|
       |*    join (wait for) the threads you created above.        *|
       |* The 2nd argument to pthread_join() should be a pointer   *|
       |*    to the 'lines' variable.                              *|
       |* Finally, your code must check for errors: if             *|
       |*    pthread_join() returns a number other than 0, your    *|
       |*    code must print the error message, free() the PATTERN *|
       |*    and 'threads' arrays, (since they were                *|
       |*    allocated with malloc(), so we must free them,) and   *|
       |*    exit the program with EXIT_FAILURE. See slide 57 for  *|
       |*    an example of checking for pthread_join() errors.     *|
       \************************************************************/










       printf ("[main] Thread #%lld returned with value: %lld\n", i+1, (long long)lines); 
       sum += (long long)lines; // add up the returned values 
    }

    // Print total # of matching lines + total # of lines scanned:
    printf ("[main] Total of %lld matched lines among total of %lld lines scanned\n", sum, total_lines_read);

    // Free the memory allocated for PATTERN:
    free (PATTERN);
    // Free the memory allocated for the threads:
    free (threads);

    return EXIT_SUCCESS;

} // End of main

// End of Program
