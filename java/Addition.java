import java.util.Scanner;  // program uses class scanner, must appear before first class
public class Addition  // file name must be same 
{
    // main method begins execution of Java application
    public static void main(String[] args) 
    {
        // create a Scanner to obtain input from the command window
        Scanner input = new Scanner(System.in);
        int number1; // first number to add
        int number2; // second number to add
        int sum; // sum of number1 and number2
        try
        { 
            System.out.print("Enter first integer: "); // prompt
            number1 = input.nextInt(); // read first number from user
    
            System.out.print("Enter second integer: "); // prompt 21
            number2 = input.nextInt(); // read second number from user
        }
        finally
        {
            input.close();  //need to close to avoid memory leak
        }
        
        
        sum = number1 + number2; // add numbers, then store total in sum
        // %s for string, %n for new line
        System.out.printf("Sum is %d%n", sum);
    } // end method main
}
