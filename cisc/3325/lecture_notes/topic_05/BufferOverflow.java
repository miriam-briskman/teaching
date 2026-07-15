// A Java program that creates an array of characters
//     of size 10 elements, but proceeds to access
//     40 characters.

class BufferOverflow
{
    public static void main(String[] args)
    {
        // Creating the array of characters:
        char[] my_characters = new char[10];

        int i;
        // Populating the array with "ABCDEFGHIJ":
        for (i = 0; i <= 9; i++)
        {
            my_characters[i] = (char)('A' + i);
        }

        // Printing 40 memory locations starting at
        //    my_characters[0] to the screen:
        for (i = 0; i <= 39; i++)
        {
            System.out.println(my_characters[i]
                               + " (Numeric value of character: "
                               + (int) my_characters[i]
                               + ")");
        }

        System.out.println("Done!");
    }
}
