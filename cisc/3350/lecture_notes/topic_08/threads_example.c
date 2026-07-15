/* A C program using pthread_create() and
 *    pthread_join() to create 3 threads and manage
 *    their execution and termination.
 *
 *    Miriam Briskman, 4/16/2023
 *    CISC 3350, Brooklyn College
 *    Licensed under CC BY-NC 4.0
 */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <errno.h>

// Defining a function that will be run
//    by threads:
void * run (void * message)
{
    printf ("%s", (char *) message);
    return message;
}

int main (void)
{
    pthread_t my_threads [3];
    int ret, index;

    char * messages [] = {"Hello from Thread 1!\n",
                          "Thread 2 says hi!\n",
                          "What's up? It's Thread 3!\n"};

    // Create 3 threads, assigning each its own
    //    message:
    for (index = 0; index < 3; index++)
    {
        ret = pthread_create (&(my_threads[index]),
                              NULL,
                              run,
                              (void *) (messages[index]));
        if (ret)
        {
            errno = ret;
            perror ("pthread_create");
            exit (EXIT_FAILURE);
        }
    }

    // Wait for the threads to exit. If we didn't
    //    join here, we'd risk terminating this
    //    main thread before the other 3 threads
    //    finished working:
    for (index = 0; index < 3; index++)
    {
        ret = pthread_join (my_threads[index], NULL);
        if (ret)
        {
            errno = ret;
            perror ("pthread_join");
            exit (EXIT_FAILURE);
        }
    }

    return EXIT_SUCCESS;
}
