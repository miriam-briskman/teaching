/* A C program that demonstrates uses of the creat(),
 *    open(), read(), write(), pread(), pwrite(),
 *    ftruncate(), fsync(), sync(), lseek(), and
 *    close() file I/O system calls.
 *
 *    Miriam Briskman, 2/27/2023
 *    CISC 3350, Brooklyn College
 *    Licensed under CC BY-NC 4.0
 */

#define _XOPEN_SOURCE 500

// Library defining types such as size_t (usually
//    as an unsigned integer:)
#include <sys/types.h>
// Library defining modes such as S_IRUSR
//    (=0000400, r for owner:)
#include <sys/stat.h>
// Library defining the open() syscall and flags
//    such as O_RDONLY:
#include <fcntl.h>
// Library defining standard symbolic constants and
//    types. Needed for read(), write(), fsync(),
//    sync(), lseek(), ftruncate(), and close():
#include <unistd.h>
// Needed for perror():
#include <stdio.h>
// Needed for 'EXIT_SUCCESS' and 'EXIT_FAILURE':
#include <stdlib.h>
// Needed for strlen():
#include <string.h>

// An unsigned integer constant representing the
//    size of an array that we create.
const size_t BUF_SIZE = 100;

int main ()
{
    // An array consisting of the alphabet:
    char alphabet [] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    //////////////////////////////////////
    // Creating and writing into a file //
    //////////////////////////////////////

    // Create a new file and open it for writing.
    //    The file's permissions will be: read &
    //    write for the owner, and read-only for the
    //    owner's group and other users.
    int file_descriptor = creat ("content.txt", 
                                 S_IWUSR | S_IRUSR | 
                                 S_IRGRP | S_IROTH);
    // The above call to creat() is equivalent to 
    // the following call to open():
    //
    // open ("content.txt", O_WRONLY | O_CREAT | O_TRUNC,
    //       S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);

    if (file_descriptor == -1) // Checking for errors!
    {
        perror ("creat");
        exit (EXIT_FAILURE);
    }

    // We now use the write() system call to write
    //    the alphabet into the file:
    ssize_t chars_written = write (file_descriptor, 
                                   alphabet,
                                   strlen (alphabet));
    if (chars_written == -1)
    {
        perror ("write");
	exit (EXIT_FAILURE);
    }

    // Since we are not guaranteed that this writing
    //    will actually be saved to the disk right
    //    away, and since we do want to save the change
    //    to the disk without waiting, we can force it
    //    to happen with fsync():
    int output = fsync (file_descriptor);
    if (output == -1)
    {
        perror ("fsync");
        exit (EXIT_FAILURE);
    }

    // We are ready now to close the file.
    // Instead of doing:
    //     int result = close (file_descriptor);
    //     if (result == -1)
    //     {
    //         perror ("close");
    //         exit (EXIT_FAILURE);
    //     }
    // We use a shorter approach:
    if (close (file_descriptor) == -1)
    {
        perror ("close");
	exit (EXIT_FAILURE);
    }
    

    //////////////////////////////////////////////////////
    // Reading from a file and printing to the terminal //
    //////////////////////////////////////////////////////
 
    // We now re-open the same one file that we created
    //    earlier, but now for reading only:
    file_descriptor = open ("content.txt", O_RDONLY);
    if (file_descriptor == -1) // Checking for errors!
    {
        perror ("open");
        exit (EXIT_FAILURE);
    }

    // Create a char array that into which we will store
    //    the content that we read in:
    char buf [BUF_SIZE];

    // Attempt reading up to BUF_SIZE - 1 characters. We
    //     need the last spot to store the null character
    //     '\0' in it:
    ssize_t number_of_chars_read_in = read (file_descriptor,
                                            buf,
                                            BUF_SIZE - 1);
    // Checking for errors:
    if (number_of_chars_read_in == -1)
    {
        perror ("read");
        exit (EXIT_FAILURE);
    }

    // If we got to this point, we know that
    //    'number_of_chars_read_in' tells how many characters
    //    up to 99 were read from the file into the array
    //    'buf' that we created above. Let's put the null
    //    char right after the data we read in, and print the
    //    contents of 'buf'!
    buf[number_of_chars_read_in] = '\0';

    char message1 [] = "1. We read the following "
                       "content from the file:\n",
	 message2 [] = "2. We read the following "
                       "content from the file:\n",
	 message3 [] = "3. We read the following "
                       "content from the file:\n",
	 message4 [] = "4. We read the following "
                       "content from the file:\n";
    
    // The following write() system calls write content
    //    to the screen. The screen is considered in
    //    Linux as an open file with the descriptor of
    //    STDOUT_FILENO. 
    if (write (STDOUT_FILENO,
               message1,
               strlen (message1))
        == -1)
    {
        perror ("write");
        exit (EXIT_FAILURE);
    }
    if (write (STDOUT_FILENO,
               buf,
               number_of_chars_read_in)
        == -1)
    {
        perror ("write");
        exit (EXIT_FAILURE);
    }
    if (write (STDOUT_FILENO, "\n", 1) == -1)
    {
        perror ("write");
        exit (EXIT_FAILURE);
    }

    // Close the file now:
    if (close (file_descriptor) == -1)
    {
        perror ("close");
        exit (EXIT_FAILURE);
    }

    //////////////////////////////////////////
    // Reading from and writing into a file //
    //////////////////////////////////////////

    // We now re-open the same one file that we
    //    created earlier, but now for both
    //    reading and writing:
    file_descriptor = open ("content.txt", O_RDWR);
    // Checking for errors:
    if (file_descriptor == -1)
    {
        perror ("open");
        exit (EXIT_FAILURE);
    }

    // Let's truncate the size of the file to only
    //    10 characters:
    if (ftruncate(file_descriptor, 10) == -1)
    {
        perror ("ftruncate");
        exit (EXIT_FAILURE);
    }

    // After this truncation, let's read the content
    //    of the file!
    number_of_chars_read_in = read (file_descriptor,
                                    buf,
                                    BUF_SIZE - 1);
    // Checking for errors:
    if (number_of_chars_read_in == -1)
    {
        perror ("read");
        exit (EXIT_FAILURE);
    }

    buf[number_of_chars_read_in] = '\0';

    // Let's print what we read to the screen:
    if (write (STDOUT_FILENO,
               message2,
               strlen (message2))
        == -1)
    {
        perror ("write");
        exit (EXIT_FAILURE);
    }
    if (write (STDOUT_FILENO,
               buf,
               number_of_chars_read_in)
        == -1)
    {
        perror ("write");
        exit (EXIT_FAILURE);
    }
    if (write (STDOUT_FILENO, "\n", 1) == -1)
    {
        perror ("write");
        exit (EXIT_FAILURE);
    }

    // While we were reading the file, the reading
    //    position moved to the end of the file.
    //    To change the reading and writing
    //    position, you will use the lseek() system
    //    call. We now want to return the position
    //    to the top of the file:
    off_t position = lseek (file_descriptor,
                            (off_t) 0,
                            SEEK_SET);
    // Above, (off_t) is used to convert the integer
    //    0 to a literal of the off_t data type.
    //    SEEK_SET tells that we want to jump to the
    //    exact position of 0 inside the file.
    if (position == (off_t) -1)
    {
        perror ("lseek");
        exit (EXIT_FAILURE);
    }

    // We now write the word "Hello" at the
    //    beginning of the file. We will later see
    //    how it will affect its content:
    chars_written = write (file_descriptor,
                           "Hello",
                           strlen ("Hello"));
    if (chars_written == -1)
    {
        perror ("write");
        exit (EXIT_FAILURE);
    }

    // Since we just made a change to the content,
    //    let's commit this change to the disk right
    //    away by using sync():
    sync();
    // sync() doesn't return a value and never fails,
    //    so we don't check for errors.
    // sync() will commit the changes for ALL the
    //    modified files that the program currently
    //    has opened.
    
    // We change the position of the file to the
    //    beginning again because we want to read
    //    from it again:
    position = lseek (file_descriptor,
                      (off_t) 0,
                      SEEK_SET);
    if (position == (off_t) -1)
    {
        perror ("lseek");
        exit (EXIT_FAILURE);
    }

    // Let's read the file's content and print it:
    number_of_chars_read_in = read (file_descriptor,
                                    buf,
                                    BUF_SIZE - 1);
    // Checking for errors:
    if (number_of_chars_read_in == -1)
    {
        perror ("read");
        exit (EXIT_FAILURE);
    }

    buf[number_of_chars_read_in] = '\0';

    // Let's print what we read to the screen:
    if (write (STDOUT_FILENO,
               message3,
               strlen (message3))
        == -1)
    {
        perror ("write");
        exit (EXIT_FAILURE);
    }
    if (write (STDOUT_FILENO,
               buf,
               number_of_chars_read_in)
        == -1)
    {
        perror ("write");
        exit (EXIT_FAILURE);
    }
    if (write (STDOUT_FILENO, "\n", 1) == -1)
    {
        perror ("write");
        exit (EXIT_FAILURE);
    }

    // As the last exercise for this program, we
    //    will attempt to write more content at the
    //    end of the file - but at a spot that is
    //    further beyond the end. We'll see what
    //    such a reading does to the file when we
    //    later run this program.

    // We write the word: "Wow" at position 20 into
    //    the file. Instead of moving the position
    //    of the file as we did for the previous
    //    calls to read() and write(), we now use
    //    the syscalls pread() and pwrite(), which
    //    do the same thing as read() and write()
    //    but don't change the position inside the
    //    file. In the call to pwrite() below, the
    //    argument 20 (the last argument) indicates
    //    at what position we wish to start writing
    //    that content inside the file.
    chars_written = pwrite (file_descriptor,
                            "Wow",
                            strlen ("Wow"),
                            20);
    if (chars_written == -1)
    {
        perror ("pwrite");
        exit (EXIT_FAILURE);
    }

    // Next, we read the file from the beginning. As
    //    we did it for pwrite(), we pass 0 as the
    //    4th argument to pread() to tell that we
    //    want to start reading from the beginning
    //    of the file, without changing the position
    //    inside the file:
    number_of_chars_read_in = pread (file_descriptor,
                                     buf,
                                     BUF_SIZE - 1,
                                     0);
    // Checking for errors:
    if (number_of_chars_read_in == -1)
    {
        perror ("pread");
        exit (EXIT_FAILURE);
    }

    buf[number_of_chars_read_in] = '\0';

    // Let's print what we read to the screen:
    if (write (STDOUT_FILENO,
               message4,
               strlen (message4))
        == -1)
    {
        perror ("write");
        exit (EXIT_FAILURE);
    }
    if (write (STDOUT_FILENO,
               buf,
               number_of_chars_read_in)
        == -1)
    {
        perror ("write");
        exit (EXIT_FAILURE);
    }
    if (write (STDOUT_FILENO, "\n", 1) == -1)
    {
        perror ("write");
        exit (EXIT_FAILURE);
    }

    if (write (STDOUT_FILENO,
               "In the last reading, we "
               "actually read a total of ", 
               strlen ("In the last reading, we "
                       "actually read a total of "))
        == -1)
    {
        perror ("write");
        exit (EXIT_FAILURE);
    }

    // Copy the integer value in
    //    'number_of_chars_read_in' to the 'buf'
    //    char array:
    sprintf(buf, "%zu", number_of_chars_read_in);

    if (write (STDOUT_FILENO, buf, strlen(buf)) == -1)
    {
        perror ("write");
        exit (EXIT_FAILURE);
    }
    if (write (STDOUT_FILENO,
               " bytes.\n",
               strlen(" bytes.\n"))
        == -1)
    {
        perror ("write");
        exit (EXIT_FAILURE);
    }

    // Finally, close the file:
    if (close (file_descriptor) == -1)
    {
        perror ("close");
        exit (EXIT_FAILURE);
    }

    if (write (STDOUT_FILENO,
               "The space between "
               "locations 10 and 20 is "
               "actually padded with "
               "null characters.\n",
               80)
        == -1)
    {
        perror ("write");
        exit (EXIT_FAILURE);
    }

    if (write (STDOUT_FILENO,
               "That is, on disk, the file looks "
               "as follows:\nHelloFGHIJ\\0\\0\\0"
               "\\0\\0\\0\\0\\0\\0\\0Wow\n",
               80)
        == -1)
    {
        perror ("write");
        exit (EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
