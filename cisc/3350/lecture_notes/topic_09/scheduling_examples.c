/* A C program that demonstrates the uses of
 *    functions mentioned in the Topic 9 lecture
 *    notes: sched_yield(), nice(), getpriority(),
 *    setpriority(), CPU_ZERO(), CPU_ISSET(),
 *    CPU_SET(), CPU_CLR(), sched_getaffinity(),
 *    sched_setaffinity(), sched_getscheduler(),
 *    sched_setscheduler(), memset(),
 *    sched_getparam(), sched_get_priority_min(),
 *    sched_get_priority_max(),
 *    sched_rr_get_interval(), setrlimit(), and
 *    getrlimit().
 *
 *    Miriam Briskman, 3/27/2023
 *    CISC 3350, Brooklyn College
 *    Licensed under CC BY-NC 4.0
 */

#define _GNU_SOURCE

#include <sys/types.h>    // pid_t, gid_t, etc.
#include <unistd.h>       // Defines some system calls.
#include <stdio.h>        // perror(), printf(), fprintf().
#include <stdlib.h>       // EXIT_SUCCESS, EXIT_FAILURE.
#include <sched.h>        // scheduling functions and constants.
#include <sys/time.h>     // Time-related functions and constants.
#include <sys/resource.h> // Resource functions and constants.
#include <errno.h>        // 'errno' variable.
#include <string.h>       // memset().

int main ()
{
    // Yield the process from the CPU. This will place this
    //     process at the tail of the ready queue. It is
    //     similar to a player giving up their turn in a
    //     certain game's round.
    if (sched_yield() == -1)
    {
        perror("sched_yield");
    }

    /******************************************\
    |                Nice Values               |
    \******************************************/

    // Get the nice value of the process:
    errno = 0;
    int nice_value = nice(0);
    // To check for errors, we check the value of
    //     errno, since nice() can return -1, which is
    //     a valid nice value, so we can't use the
    //     returned value of nice() to check for errors.
    if (errno != 0) 
    {
        perror("nice");
    }

    printf("The current nice value is: %d.\n", nice_value);

    // Let's increase the nice value by 5:
    if (nice_value + 5 <= 19)
    {
        errno = 0;
        int res = nice(5);
        if (errno != 0)
        {
            perror("nice");
        }
        printf("We increased the nice value to: %d.\n", res);
    }

    // Get the nice value of the process again:
    errno = 0;
    int ret = getpriority (PRIO_PROCESS, 0);
    if (errno != 0)
    {
        perror("getpriority");
    }

    printf ("The current nice value is: %d.\n", ret);

    // Decrease the priority by 1:
    ret = setpriority (PRIO_PROCESS, 0, ret + 1);
    if (ret == -1)
    {
        perror ("setpriority");
    }

    // Get the nice value of the process again:
    errno = 0;
    ret = getpriority (PRIO_PROCESS, 0);
    if (errno != 0)
    {
        perror("getpriority");
    }

    printf ("The new nice value is: %d.\n", ret);

    /******************************************\
    |               Affinities                 |
    \******************************************/

    // The following code for getting CPU affinity is
    //     taken from slide 17 of the Chapter 6
    //     lecture notes.
    cpu_set_t set;
    int i;

    CPU_ZERO (&set); // Nullify the set: remove all the CPUs.

    // Find the affinity for the current process, and store
    //     the results in 'set':
    if (sched_getaffinity (0, sizeof (cpu_set_t), &set) == -1)
    {
        perror ("sched_getaffinity");
    }

    // Iterates through the first 16 virtual CPUs, and
    //     check if each of them is bound to the process:
    for (i = 0; i < 16; i++)
    {
        int cpu = CPU_ISSET (i, &set);
        printf ("cpu = %i is %s\n", i, cpu ? "set" : "unset");
    } 

    // Print the value of the CPU_SETSIZE constant:
    printf("This device allows checking up to %d CPUs.\n", CPU_SETSIZE);

    // Now, we'll set the affinity of the current process only
    //    to CPU-0:
    // The following code for setting CPU affinity is
    //     taken from slide 17 of the Chapter 6
    //     lecture notes.
    CPU_ZERO (&set); /* clear all CPUs */
    CPU_SET (0, &set); /* allow CPU #0 */
    CPU_CLR (1, &set); /* disallow CPU #1 */

    if (sched_setaffinity (0, sizeof (cpu_set_t), &set) == -1)
    {
        perror ("sched_setaffinity");
    }

    // Iterates through the first 16 virtual CPUs, and
    //     check if each of them is bound to the process:
    for (i = 0; i < 16; i++)
    {
        int cpu = CPU_ISSET (i, &set);
        printf ("cpu = %i is %s\n", i, cpu ? "set" : "unset");
    }

    /******************************************\
    |                 Policies                 |
    \******************************************/

    // The following code for getting the scheduling
    //     policy is taken from slide 17 of the
    //     Chapter 6 lecture notes.

    /* get our scheduling policy */
    int policy = sched_getscheduler (0);

    switch (policy)
    {
        case SCHED_OTHER: printf ("Policy is normal.\n");
                          break;
        case SCHED_RR: printf ("Policy is round-robin.\n");
                       break;
        case SCHED_FIFO: printf ("Policy is FIFO.\n");
                         break;
        case SCHED_BATCH: printf ("Policy is idle.\n");
                          break;
        case -1: perror ("sched_getscheduler");
                 break;
        default: fprintf (stderr, "Unknown policy!\n");
    }  

    // Setting the policy to round-robin with priority of 1:
    struct sched_param sp = { .sched_priority = 1 };
    if (sched_setscheduler (0, SCHED_RR, &sp) == -1)
    {
        perror ("sched_setscheduler");
    }

    // Checking if the policy was indeed set:
    policy = sched_getscheduler (0);

    switch (policy)
    {
        case SCHED_OTHER: printf ("Policy was changed to normal.\n");
                          break;
        case SCHED_RR: printf ("Policy was changed to round-robin.\n");
                       break;
        case SCHED_FIFO: printf ("Policy was changed to FIFO.\n");
                         break;
        case SCHED_BATCH: printf ("Policy was changed to idle.\n");
                          break;
        case -1: perror ("sched_getscheduler");
                 break;
        default: fprintf (stderr, "Unknown policy!\n");
    }

    // Nullify sp (since we need to use it again:)
    memset (&sp, 0, sizeof (struct sched_param));

    // Finding the priority of the process:
    if (sched_getparam (0, &sp)== -1)
    {
        perror ("sched_getparam");
    }

    printf ("Our priority is %d.\n", sp.sched_priority);

    // Nullify sp (since we need to use it again:)
    memset (&sp, 0, sizeof (struct sched_param));

    // Setting the priority of the process to 1:
    sp.sched_priority = 1;
    if (sched_setparam (0, &sp)== -1)
    {
        perror ("sched_setparam");
    }

    // Finding the min and max priorities for round-robin:
    int min = sched_get_priority_min (SCHED_RR);
    if (min == -1)
    {
        perror ("sched_get_priority_min");
    }

    int max = sched_get_priority_max (SCHED_RR);
    if (max == -1)
    {
        perror ("sched_get_priority_max");
    }

    printf ("SCHED_RR priority range is: %d - %d.\n", min, max);

    // Getting the current process's time slice length:
    struct timespec tp;

    if (sched_rr_get_interval (0, &tp) == -1)
    {
        perror ("sched_rr_get_interval");
    }

    printf ("The time slice is %lld seconds and %lld nanosecs.\n",
            (long long int) tp.tv_sec, (long long int) tp.tv_nsec);

    /******************************************\
    |                  Limits                  |
    \******************************************/

    // Setting a soft limit of RLIMIT_NOFILE to 50:
    struct rlimit rlim;
    rlim.rlim_cur = 50; /* Changing the soft limit. */
    rlim.rlim_max = RLIM_INFINITY; /* Hard limit: leaving it alone. */

    if (setrlimit (RLIMIT_NOFILE, &rlim) == -1)
    {
        perror ("setrlimit");
    }

    // Printing the hard and soft limits of RLIMIT_NOFILE:
    if (getrlimit (RLIMIT_NOFILE, &rlim) == -1)
    {
        perror ("getrlimit");
    }

    printf ("RLIMIT_NOFILE limits: soft = %ld hard = %ld.\n",
            rlim.rlim_cur, rlim.rlim_max);

    return EXIT_SUCCESS;
}
