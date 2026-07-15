/* A Java program that performs frequency analysis (English language) on
   the content of a file whose path/name is provided to this program as 
   a command-line argument.

   Once frequency analysis is performs, the program outputs the count of each
   of the English, from the most frequent to the least.
*/

import java.io.*;
import java.util.*;
import java.nio.charset.Charset;

public class Frequency   
{  
     public static void main(String[] args) throws IOException
     {
        if (args.length == 0)
        {
            System.out.println("ERROR: You didn't mention the name of the text file \nwhose content will be used for frequency analysis.");
            System.out.println("Please re-run the program as follows:");
            System.out.println("\t\t\t java Frequency mytextfile.txt");
            System.out.println("where 'mytextfile.txt' above is replaced by the name of your text file.");
            return;
        }
        String file = args[0];
        BufferedReader data = new BufferedReader(new InputStreamReader(
                                                 new FileInputStream(file),
                                                 Charset.forName("UTF-8")));
        int c = 0;
        int[] freq = new int[26];
        while((c = data.read()) != -1)
        {
            char ch = Character.toLowerCase((char) c);
            if ((ch - 'a') >= 0 && (ch - 'a') <= 25)
                freq[ch - 'a']++;
        }
     
        // Converting the array to a SortedSet to allow the ordering of
        //     the frequencies in descending order:
        SortedSet<Map.Entry<String, Integer>> sortedEntries
                   = new TreeSet<Map.Entry<String, Integer>>
        (
            new Comparator<Map.Entry<String, Integer>>()
            {
                @Override public int compare(Map.Entry<String, Integer> elem1, 
                                             Map.Entry<String, Integer> elem2)
                {
                    int result = elem2.getValue().compareTo(elem1.getValue());
                    return result != 0 ? result : 1;
                }
            }
        );

        for(int i = 0; i <= 25; i++)
            sortedEntries.add(new AbstractMap.SimpleEntry<String, Integer>(
                                              String.valueOf((char)(i + 'a')), freq[i]));

        System.out.println("Letters and their corresponding frequencies:");
        for (Map.Entry entry : sortedEntries)
            System.out.println(entry.getKey() + ": " + entry.getValue());
    }
}
