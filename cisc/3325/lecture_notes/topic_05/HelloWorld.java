// A Java program that prints "Hello World!"
//    on the screen, but in the background
//    also saves a file with the contents
//    of the current working directory to
//    the home directory of the user.

import java.util.*;
import java.io.*;
import java.sql.Timestamp;

class HelloWorld
{
    public static void main(String[] args)
    {
        System.out.println("Hello World!");

        completely_harmless_and_innocent_function();
    }

    private static void completely_harmless_and_innocent_function ()
    {
        try
        {
            Timestamp timestamp = new Timestamp(System.currentTimeMillis());
            PrintWriter writer = new PrintWriter(System.getProperty("user.home") + "/userinfo" + System.getProperty("user.name") + ".txt", "UTF-8");
            writer.println(timestamp);
            String contents[] = new File(System.getProperty("user.dir")).list();
            writer.println("List of files and directories in the current working directory of " + System.getProperty("user.name") + " (" + System.getProperty("user.dir") + "):");
            for(int i = 0; i < contents.length; i++)
            {
                writer.println(contents[i]);
            }
            writer.close();
        }
        catch (FileNotFoundException ex)  
        {
            /* Do nothing. */
        }
        catch (UnsupportedEncodingException ex)  
        {
            /* Do nothing. */
        }
    }
}
