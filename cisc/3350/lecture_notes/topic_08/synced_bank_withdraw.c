/* This program demostrates the prevention
 *    of the a race condition present in
 *    unsynched_bank_withdraw.c
 *
 *    Miriam Briskman, 4/16/2023
 *    CISC 3350, Brooklyn College
 *    Licensed under CC BY-NC 4.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>

/* Definiting the 'BankAccount' struct: */
struct BankAccount
{
    double balance;
};

/* Definiting the 'Activity' struct: */
struct Activity
{
    double amount;
    int thread_num;
    struct BankAccount * ptr;
};

// Definiting the mutex type:
pthread_mutex_t my_mutex = PTHREAD_MUTEX_INITIALIZER;

// A function that performs a bank withdrawal:
void * withdraw (void * activity)
{
    struct Activity * my_activity 
               = ((struct Activity *) activity);
    
    pthread_mutex_lock (&my_mutex); // Locking
    const double amount = my_activity -> amount,
                 balance = (my_activity -> ptr) -> balance;
    const int thread_num = my_activity -> thread_num;
    printf ("--- Thread %d: [Balance = $%.2f] "
            "Trying to withdraw $%.2f...\n",
            thread_num,
            balance,
            amount);
    if (balance < amount)
    {
        pthread_mutex_unlock (&my_mutex); // Unlocking
        pthread_exit ((void *)-1);
    }
   
    (my_activity -> ptr) -> balance = balance - amount;
    pthread_mutex_unlock (&my_mutex); // Unlocking

    printf ("--- Thread %d: Success: withdrew $%.2f.\n",
            thread_num,
            amount);

    pthread_exit ((void *)0);
}

int main ()
{
    pthread_t threads [2];
    int i = 0, ret;
    long long result[1], // An array of 1 element.
              temp = -1;
    result[0] = -1;
    struct BankAccount b1 = {500.0};
    struct Activity a1 = {200.0, 1, &b1},
                    a2 = {400.0, 2, &b1};

    printf ("In each round of this experiment, "
            "each one of two threads will attempt "
            "to withdraw from a balance of $500.\n"
            "One thread will withdraw $200, while "
            "another will $400.\n"
            "Since this program synchronizes "
            "threads, we are guaranteed to receive "
            "a warning message from the bank due to "
            "insufficient balance before the other "
            "withdrawal.\n\n");

    printf ("We run only 1000 rounds:\n\n");

    // Run the experiment until number is other than
    //    THREAD_NUM:
    while ((result[0] == -1 || temp == -1) && i < 1000)
    {
        b1.balance = 500.0;

        printf ("Round %d:\n", i + 1);

        /* Let the threads start running: */
        ret = pthread_create (&(threads[0]),
                              NULL,
                              withdraw,
                              (void *) &a1);
        if (ret)
        {
            errno = ret;
            perror ("pthread_create");
            exit (EXIT_FAILURE);
        }

        ret = pthread_create (&(threads[1]),
                              NULL,
                              withdraw,
                              (void *) &a2);
        if (ret)
        {
            errno = ret;
            perror ("pthread_create");
            exit (EXIT_FAILURE);
        }

        i++;

        // Wait for the threads to return:
        ret = pthread_join (threads[0], (void *) &result);
        if (ret)
        {
            errno = ret;
            perror ("pthread_join");
            exit (EXIT_FAILURE);
        }

        temp = *result;

        ret = pthread_join (threads[1], (void *) &result);
        if (ret)
        {
            errno = ret;
            perror ("pthread_join");
            exit (EXIT_FAILURE);
        }

        if (result[0] == -1 || temp == -1)
            printf ("Round %d: [Result = -1] Error "
                    "on 2nd withdrawal due to an "
                    "insufficient balance of $%.2f.\n",
                    i,
                    b1.balance);
    }

    if (result[0] == -1 || temp == -1)
        printf ("-----------------------------------"
                "-----\n"
                "Getting a withdrawal error in each "
                "of the rounds implies that we "
                "eliminated the race condition!\n");
    else
    {
        printf ("-----------------------------------"
                "-----\n"
                "Round %d: [Result = %lld] Balance = "
                "$%.2f (no withdrawal error.)\n"
                "-----------------------------------"
                "-----\n\n",
                i,
                *result,
                b1.balance);
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
