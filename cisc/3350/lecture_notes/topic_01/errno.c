/* A C program that shows how to detect and print
 *    error messages in various ways.
 *
 * We will attempt to issue a system call such
 *    that it fails, intentionally, to test the
 *    methods of C to detect errors, including
 *    (1) checking the returned value of a system
 *    call, and (2) checking the value of the
 *    'errno' variable that C uses to indicate
 *    what specific error happened.
 *    
 *    Miriam Briskman, 2/8/2023
 *    CISC 3350, Brooklyn College
 *    Licensed under CC BY-NC 4.0
 */


// Include a reference to C's standard input &
//    output library without which no messages
//    can be printed to the screen:
#include <stdio.h>
// Include the definition of the 'errno' variable
//    that is set every time an error occurs in a
//    function call:
#include <errno.h>
// Include the library that defines the close()
//    system call:
#include <unistd.h>
// The String library is needed to print error
//     messages, for example by using strerror().
#include <string.h>


// main function:
int main() 
{ 
    // Print the value of 'errno', which is
    //    defined in the <errno.h> library that
    //    was included above, before making any
    //    system calls:
    printf ("At the start of the program,"
            " errno is: %d.\n", errno);
    printf ("Now, we will attempt a faulty"
            " call to close().\n");

    // Setting 'errno' to 0 just in case:
    errno = 0;

    // Now, we attempt to call the close()
    //    system call, which is a function
    //    used to close an open file.
    //    However, to make it fail on purpose,
    //    we try to close a file that was
    //    never open. According to the manual
    //    page on close(), the errno variable
    //    can be set in a number of ways,
    //    including when the integer file
    //    descriptor that is passed to close()
    //    isn't a valid open file descriptor.
    //    The reason we decided to save these
    //    values in variable is that calls to
    //    perror() and strerror() might set
    //    errno to different values at any time.

    // A file descriptor can only be 0, 1, 2, 3, ...
    int return_value = close(-1);
    int copy_of_errno = errno;
    
    // Since the descriptor -1 above can never
    //    represent an open file, we expect that
    //    (1) the value of 'return_value' is -1
    //    since this is the value close()
    //    returns when it fails, and (2) errno
    //    was set within close() to a non-zero
    //    integer, which indicates an error.
    
    // Now, we try printing a human-understandable
    //    statement about the error that happened.
    //    The message that should be printed to the
    //    terminal is of the form: "close: such and
    //    such error happened". The name 'perror'
    //    means 'print error'.
    if (return_value == -1)
        perror ("close");

    // We also print return_value and
    //    copy_of_errno that we saved earlier:
    printf ("After the call to close(),"
            " the returned value by close() was: %d,"
            " and errno was set to: %d.\n",
            return_value, copy_of_errno);

    // We also demonstrate how to print the error
    //    message using the strerror() function,
    //    which returns a pointer to the error
    //    string that perror() would print, but
    //    without printing it. strerror() accepts
    //    the errno value to be able to return
    //    the pointer.
    char * error_string = strerror (copy_of_errno);

    // Now, we print the string the pointer to
    //    which we obtained:
    printf ("The error message that strerror()"
            " returned is: %s.\n", error_string);

    // For the sake of completion, the use of the
    //    thread-safe function strerror_r() is
    //    demonstrated:

    // Creation of a 'buf' array of size 1024 bytes:
    char buf[1024];
    int strerror_r_returned_value
        = strerror_r (copy_of_errno, buf, sizeof(buf));
    printf ("The error message that strerror_r()"
            " returned is: %s.\n", buf);
    printf ("strerror_r() itself returned with"
            " code %d.\n", strerror_r_returned_value);

    // Just as a check, we show what the three
    //    functions return when there is no error
    //    (when errno remains zero:)
    printf ("\nWe now check what perror(), strerror(),"
            " and strerror_r() return when"
            " there is no error:\n");
    errno = 0;
    perror ("<Place function name here>");
    printf ("The message that strerror()"
            " returned is: %s.\n", strerror (0));

    // Another array for strerror_r() to use:
    char buf2[1024];
    strerror_r_returned_value
        = strerror_r (0, buf2, sizeof(buf2));
    printf ("The message that strerror_r()"
            " returned is: %s.\n", buf2);
    printf ("strerror_r() itself returned with"
            " code %d.\n", strerror_r_returned_value);

    // Exit the program with 0 as a message,
    //    showing that the execution was successful.
    return 0; 
}
