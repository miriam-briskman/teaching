/* The following program exemplifies calls to
 *    fopen() fwrite(), fread(), and fclose(). We
 *    write the binary data of a single structure
 *    into a file. This same file is then opened
 *    for reading, and we read this data back in
 *    again as binary data into another structure
 *    instance, s. We then print the data fields
 *    of s to the terminal.
 *
 *    Miriam Briskman, 3/8/2023
 *    CISC 3350, Brooklyn College
 *    Licensed under CC BY-NC 4.0
 */

#include <stdio.h>
#include <stdlib.h> // For EXIT_FAILURE, EXIT_SUCCESS.

struct Dog
{
    char breed[100];
    unsigned int age; // in years
    char nature[100];
};

int main (void)
{
    FILE *in_file, *out_file;

    struct Dog lucky = {"Labrador retriever",
                        5,
                        "Playful, Loving"};
    struct Dog stella;

    // Above, 'lucky' and 'stella' are both
    //    instances of the 'Dog' structure.
    //    Specifically, 'lucky' and 'stella'
    //    are twins! Only 'lucky' was
    //    initiated so far, and we will
    //    initiate 'stella' now via file i/o!

    // Create a new file 'data' for writing:
    out_file = fopen ("data", "w");
    if (!out_file) // Same as (out_file == NULL)
    {
        perror ("fopen");
        exit (EXIT_FAILURE);
    }

    // Write lucky's data in binary manner into
    //    the file:
    if (!fwrite (&lucky,
                 sizeof (struct Dog),
                 1,
                 out_file))
    {
        perror ("fwrite");
        exit (EXIT_FAILURE);
    }

    /* Explanation:
       Above, fwrite() accesses the address in
       memory where the information about
       lucky is stored. Because all the data
       fields of a structure are stored
       consecutively in memory, the function
       needs to know how many bytes a Dog
       structure uses in memory and copy
       that data over to the file. The 'sizeof'
       operator finds this information.
       We need to copy only one instance of
       the Dog struct, so the 3rd argument to
       the function is 1.
    */

    // Close the file 'out_file':
    if (fclose (out_file))
    {
        perror ("fclose");
        exit (EXIT_FAILURE);
    }

    // Open the 'data' file for reading:
    in_file = fopen ("data", "r");
    if (!in_file)
    {
        perror ("fopen");
        exit (EXIT_FAILURE);
    }

    // Read in the binary data:
    if (!fread (&stella,
                sizeof (struct Dog),
                1,
                in_file))
    {
        perror ("fread");
        exit (EXIT_FAILURE);
    }

    // Close the file 'in_file':
    if (fclose (in_file))
    {
        perror ("fclose");
        exit (EXIT_FAILURE);
    }

    // Finally, print information about stella
    //     in the terminal:
    printf ("Information about Stella:\n"
            "Breed: %s\n"
            "Age: %i\n"
            "Nature: %s\n",
            stella.breed, stella.age, stella.nature);

    return EXIT_SUCCESS;
}
