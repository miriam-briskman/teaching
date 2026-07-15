/* A Java program that hashes a piece of text that the user
   types, outputs the digest, and asks the user to re-enter
   the same data to compare with the digest.
*/

import java.io.*;
import java.security.*;

public class Hashing
{  
     public static void main(String[] args) throws IOException
     {
        System.out.print("Type the data you wish to hash here: >> ");
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String data = reader.readLine();
        System.out.println("----------------------------");
        System.out.println("The data you entered is: " + data);
        String digest = sha256(data);
        System.out.println("The SHA 256 digest is: " + digest);
        System.out.println("----------------------------");
        Boolean flag = false;
        String digest2;
        while (flag == false)
        {
            System.out.print("Type the data you entered at the start of this program: >> ");
            data = reader.readLine();
            System.out.println("----------------------------");
            System.out.println("The data you entered now is: " + data);
            digest2 = sha256(data);
            System.out.println("The SHA 256 digest is: " + digest2);
            if (digest2.equals(digest) == false)
            {
                System.out.println("The data you entered now is different from the data you entered at the start of the program.");
                System.out.println("----------------------------");
                System.out.print("Please try again: ");
            }
            else
            {
                System.out.println("You successfully entered the same data as the one entered at the start of the program!");
                System.out.println("----------------------------");
                System.out.println("Bye for now!");
                flag = true;
            }
        }
    }

    /* The function below is taken from https://stackoverflow.com/a/11009612/14167156 */
    public static String sha256(final String base) {
    try{
        final MessageDigest digest = MessageDigest.getInstance("SHA-256");
        final byte[] hash = digest.digest(base.getBytes("UTF-8"));
        final StringBuilder hexString = new StringBuilder();
        for (int i = 0; i < hash.length; i++) {
            final String hex = Integer.toHexString(0xff & hash[i]);
            if(hex.length() == 1) 
              hexString.append('0');
            hexString.append(hex);
        }
        return hexString.toString();
    } catch(Exception ex){
       throw new RuntimeException(ex);
    }
}
}
