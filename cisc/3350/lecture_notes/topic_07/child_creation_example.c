/* A C program that forks, executes, and waits upon
 *    a child process. It demonstrates the use of
 *    the getpid(), getppid(), fork(), execlp(),
 *    waitpid(), perror(), fprintf(), atexit(), and
 *    exit() syscalls/functions.
 *
 *    Miriam Briskman, 3/15/2023
 *    CISC 3350, Brooklyn College
 *    Licensed under CC BY-NC 4.0
 */

#include <sys/types.h> // pid_t, gid_t, etc.
#include <unistd.h>    // Defines some system calls.
#include <sys/wait.h>  // wait(), waitpid(), etc.
#include <stdio.h>     // perror(), printf(), fprintf().
#include <stdlib.h>    // EXIT_SUCCESS, EXIT_FAILURE.
#include <inttypes.h>  // intmax_t.

// Definition of a function that we call
//    during a process's termination:
void bye (void)
{
   printf ("Parent: Signing off!\n");
}

// Definition of another function we call
//    during a process's termination:
void out (void)
{
   printf ("Parent: atexit() succeeded!\n");
}

// Follow-up question:
// Why don't we need to include a copy of
//    the bye() and out() function declarations
//    here?
// Hint: what is the difference between the
//    bye() and out() functions here and the
//    functions that we created in 'functions.c'
//    that we covered several lectures ago?

int main ()
{
   printf ("Parent: started executing now!\n");

   // Fork (create) a child process:
   pid_t childpid = fork();
   if (childpid == -1)
   {
       perror ("fork");
       exit (EXIT_FAILURE);
   }

   // We enter this 'if' only inside the parent
   //    process:
   if (childpid)
   {
       // The function out() and then the function
       //    bye() will execute automatically right
       //    before the parent terminates. The
       //    execution of the functions that atexit()
       //    registers is in the reversed order of
       //    the registration (we first register
       //    bye() and then out(), but they are
       //    called in the opposite order: out()
       //    followed by bye().
       if (atexit (bye) != 0)
       {
            fprintf (stderr,
                     "atexit(): can't register bye().\n");
            exit (EXIT_FAILURE);
       }
       if (atexit (out) != 0)
       {
            fprintf (stderr,
                     "atexit(): can't register out().\n");
            exit (EXIT_FAILURE);
       }

       printf ("Parent: My pid = %jd.\n",
               (intmax_t) getpid ());
       printf ("Parent: I just forked a child! "
               "I'll wait for it to terminate.\n");

       int status;

       // Wait for the child with ID of 'childpid'
       //    to return before continuing the
       //    parent's execution. The parent will
       //    pause its execution on the CPU while
       //    waiting for the child, and the
       //    waitpid() call will only return when
       //    the child finished working.
       pid_t temp = waitpid (childpid, &status, 0);
       if (temp == -1)
       {
           perror ("waitpid");
           // out() and bye() might be called here:
           exit (EXIT_FAILURE);
       }

       printf ("Parent: The child that just returned "
               "has the pid = %d.\n",
               temp);

       // Let's check what happened with the child:
       if (WIFEXITED (status))
           printf ("Parent: It terminated normally "
                   "with the exit status = %d.\n",
                   WEXITSTATUS (status));
       if (WIFSIGNALED (status))
           printf ("Parent: It was killed by the "
                   "signal = %d%s.\n",
                    WTERMSIG (status),
                    WCOREDUMP (status) ? " (dumped core)" : "");
       if (WIFSTOPPED (status))
           printf ("Parent: It was stopped by the "
                   "signal = %d.\n",
                   WSTOPSIG (status));
       if (WIFCONTINUED (status))
           printf ("Parent: Its execution "
                   "continued.\n");
   }
   // We enter this 'else' only inside the child
   //    process:
   else // Inside the child, 'childpid' is always 0.
   {
       printf ("Child: My pid = %jd.\n",
               (intmax_t) getpid ());
       printf ("Child: Parent's pid = %jd.\n",
               (intmax_t) getppid ());

       printf ("Child: I'll call execlp() now and "
               "replace myself with the 'ls -al' "
               "command:\n");

       // Execute the command/program: ls -al as the
       //    child!
       if (execlp ("ls", "ls", "-al", NULL) == -1)
       {
           perror ("execlp");
           exit (EXIT_FAILURE);
       }

       // When execlp() executes, the child's
       //    process will be replaced completely
       //    with the program "ls -al".
   }

   // Only the parent calls out() and bye() here:
   return EXIT_SUCCESS;
}
