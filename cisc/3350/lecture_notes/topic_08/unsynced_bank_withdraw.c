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

// A function that performs a bank withdrawal:
void * withdraw (void * activity)
{
    struct Activity * my_activity
               = ((struct Activity *) activity);

    /* Race condition starts here: */
    const double amount = my_activity -> amount,
                 balance = (my_activity -> ptr) -> balance;
    const int thread_num = my_activity -> thread_num;
    printf ("--- Thread %d: [Balance = $%.2f] "
            "Trying to withdraw $%.2f...\n",
            thread_num,
            balance,
            amount);
    if (balance < amount)
        pthread_exit ((void *)-1);
   
    (my_activity -> ptr) -> balance = balance - amount;
    /* Race condition ends above. */

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
            "Theoretically, before the 2nd withdrawal, "
            "the bank should eliminate that other "
            "withdrawal due to insufficient balance.\n"
            "In practice, this isn't always the case!\n\n");

    printf ("This experiment will keep running until "
            "the result is other than an error message "
            "from the bank. In other words, we will "
            "show that, eventually, a race condition "
            "will happen, and the bank will "
            "miscalculate the account balance!\n");

    // Run the experiment until number is other than
    //    THREAD_NUM:
    while (result[0] == -1 || temp == -1)
    {
        b1.balance = 500.0;

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
            printf ("Round %d: [Result = -1] Error on "
                    "2nd withdrawal due to an "
                    "insufficient balance of $%.2f.\n",
                    i,
                    b1.balance);

    }

    printf ("--------------------------------"
            "--------\n"
            "Round %d: [Result = 0] Balance = $%.2f "
            "(no withdrawal error.)\n"
            "--------------------------------"
            "--------\n\n", 
            i, b1.balance);

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
