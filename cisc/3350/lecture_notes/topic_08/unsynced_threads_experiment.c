/* This program demostrates the results of
 *    a race condition. While, in theory,
 *    we expect a specific number to be
 *    output, a different number may be
 *    generated in practice due to an
 *    existing race condition.
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
//    all the threads:)
int number = THREAD_NUM;

// A function that increments the global
//    variable 'number':
void * add (void * arg)
{
    number = number + 1; // <-- Race condition here!
    return arg;
}

int main ()
{
    pthread_t threads [THREAD_NUM];
    int i = 0, j, ret;

    printf ("In each round of this experiment, "
            "each one of %d threads will attempt "
            "to increment 0.\nTheoretically, "
            "after %d increments, the result "
            "should be %d.\nIn practice, this "
            "isn't always the case!\n\n",
            THREAD_NUM,
            THREAD_NUM,
            THREAD_NUM);

    printf ("This experiment will keep running "
            "until the result is other than %d:\n\n",
            THREAD_NUM);

    // Run the experiment until number is other than
    //    THREAD_NUM:
    while (number == THREAD_NUM)
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

        // Wait for the threads to return:
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
            (i + 1), number);
    
    printf ("The reason for this situation is a "
            "race condition that prevents additions"
            "\nfrom being done in sequential order, "
            "thus corrupting the result.\n\n");

    printf ("Specifically, the machine instructions "
            "of 2 or more of the threads \nwere "
            "interleaved, which caused this "
            "corruption to happen.\n");

    return EXIT_SUCCESS;
}
