/* This program demostrates that, with
 *    thread synchronization, no race
 *    conditions happen, so data isn't
 *    corrupted. This program includes
 *    a solution to the issue demonstrated
 *    in unsynced_threads_experiment.c
 *    
 *    Miriam Briskman, 4/16/2023
 *    CISC 3350, Brooklyn College
 *    Licensed under CC BY-NC 4.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>

// The number of thread structures:
#define THREAD_NUM 1000

// An integer global variable (accessible by
//     all the threads:)
int number = THREAD_NUM;

// Definiting the mutex type:
pthread_mutex_t my_mutex = PTHREAD_MUTEX_INITIALIZER;

void * add (void * arg)
{
    pthread_mutex_lock (&my_mutex); // Locking
    number = number + 1;
    pthread_mutex_unlock (&my_mutex); // Unlocking
    return arg;
}

int main ()
{
    pthread_t threads [THREAD_NUM];
    int i = 0, j, ret;

    printf ("In each round of this experiment, each "
            "one of %d threads will attempt to "
            "increment 0.\n"
            "Since this program synchronizes threads, "
            "the result is guaranteed to be "
            "exactly %d.\n",
            THREAD_NUM,
            THREAD_NUM);

    printf ("We run only 1000 rounds:\n\n");

    // Run the experiment until number is other
    //    than THREAD_NUM:
    while (number == THREAD_NUM && i < 1000)
    {
        // Initialize 'number' to 0:
        number = 0;

        // Let the threads start running:
        for (j = 0; j < THREAD_NUM; j++)
        {
            ret = pthread_create (&(threads[j]),
                                  NULL,
                                  add,
                                  NULL);
            if (ret)
            {
                errno = ret;
                perror ("pthread_create");
                exit (EXIT_FAILURE);
            }
        }

        /* Wait for the threads to return: */
        for (j = 0; j < THREAD_NUM; j++)
        {
            ret = pthread_join (threads[j], NULL);
            if (ret)
            {
                errno = ret;
                perror ("pthread_join");
                exit (EXIT_FAILURE);
            }
        }

        i++;
    }

    printf ("-----------------------------------"
            "-----\n"
            "In round %d: result = %d.\n"
            "-----------------------------------"
            "-----\n\n", 
            i, number);

    if (number == THREAD_NUM)
        printf ("Getting %d in each of the rounds "
                "implies that we eliminated the "
                "race condition!\n",
                THREAD_NUM);
    else
    {
        printf ("The reason for this situation is "
                "a race condition that prevents "
                "additions\nfrom being done in "
                "sequential order, thus corrupting "
                "the result.\n\n");

        printf ("Specifically, the machine instructions "
                "of 2 or more of the threads \nwere "
                "interleaved, which caused this "
                "corruption to happen.\n");
    }

    return EXIT_SUCCESS;
}
