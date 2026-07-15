/* The Driver.java class that sums non-negative integers as follows:
result = sum(n) = sigma_{i=1}^n(i).
Examples:
* For n = 3, the sum is 1 + 2 + 3 = 6.
* For n = 4, the sum is 1 + 2 + 3 + 4 = 10.
* For n = 5, the sum is 1 + 2 + 3 + 4 + 5 = 15.
*/

class SummationThread extends Thread
{
    /* Variables: */
    private int upper, sum;

    /* Constructor: */
    public SummationThread(int upper)
    {
        this.upper = upper;
    }

    /* A thread will run the following method
           once we call the start() method. */
    @Override
    public void run()
    {
        this.sum = 0;
        for (int i = 1; i <= this.upper; i++)
            this.sum += i;
    }

    /* A method that returns 'sum' as an
           Integer object: */
    public Integer getSum()
    {
        return Integer.valueOf(this.sum);
    }
}

public class Driver
{
    public static void main(String[] args)
    {
        // Store the 2nd command-line argument
        //    to this Java program in 'upper':
        int upper = Integer.parseInt(args[0]);

        SummationThread thread1 = new SummationThread(upper);

        // Start executing the code in the run() method:
        thread1.start(); 

        // Wait for the thread to finish running:
        try
        {
            thread1.join(); 
        }
        catch (InterruptedException e)
        {
            e.printStackTrace();
        }

        // Print the summation calculated by 'thread1':
        System.out.println("sum = " + thread1.getSum());
    }
}