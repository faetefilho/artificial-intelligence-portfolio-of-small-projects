package chapter_06;
import java.util.Scanner;

public class MaximumFinder 
{
    public static void main(String[] args) 
    {
        // create Scanner for input from command window
        Scanner input = new Scanner(System.in);
        
        double number1, number2, number3;
        // prompt for and input three floating-point values
        try
        {
            System.out.print(
             "Enter three floating-point values separated by spaces: ");
            number1 = input.nextDouble(); // read first double
            number2 = input.nextDouble(); // read second double
            number3 = input.nextDouble(); // read third double
        }
        finally
        {
            input.close();
        }
        
  
        // determine the maximum value
        double result = maximum(number1, number2, number3); 
  
        // display maximum value, string concatenation 
        System.out.println("Maximum is: " + result);
     } 
  
     // returns the maximum of its three double parameters 
     // public: it can be called from methods from other classes
     // static methods within the same classes can call each other directly, like in
     // maximum instead of MaximumFinder.maximum, there is more to static than this
     // Math.sqrt(90) can be called without creating an object first. Because it is a static method         
     public static double maximum(double x, double y, double z) 
     {   
        //software reuse of other already available functions                                                                                             
        return Math.max(x, Math.max(y, z));                                        
     }
}
