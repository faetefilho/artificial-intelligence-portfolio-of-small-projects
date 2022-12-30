// Handling ArithmeticExceptions and InputMismatchExceptions.
import java.util.InputMismatchException;
import java.util.Scanner;

public class DivideByZeroWithExceptionHandling
{
    // demonstrates throwing an exception when a divide-by-zero occurs
    public static int quotient(int numerator, int denominator)
    // throws clause specify the exception the method may throw if problem occurs
        throws ArithmeticException {
        return numerator / denominator; // possible division by zero
    } 

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in); 
        boolean continueLoop = true; // determines if more input is needed

        do {                                                                
            try { // read two numbers and calculate quotient 
                // scope of try block: local variables of a try block are not accessible in the 
                // corresponding catch blocks. same for catch block scope                
                System.out.print("Please enter an integer numerator: ");    
                int numerator = scanner.nextInt();                            
                System.out.print("Please enter an integer denominator: ");  
                // an input mismatch would be throw at the line below
                int denominator = scanner.nextInt();                          
                // while a arithmetic exception would be throw by this method,
                // that is why the arithmetic exception is in the method quotient                                                            
                int result = quotient(numerator, denominator);              
                System.out.printf("%nResult: %d / %d = %d%n", numerator,     
                denominator, result);                                     
                continueLoop = false; // input successful; end looping        
            }   
            // Every try block must be followed by at least one catch/finnaly block    
            // Only the first matching catch executes                                                       
            catch (InputMismatchException inputMismatchException) {        
                System.err.printf("%nException: %s%n",                       
                inputMismatchException);                                  
                scanner.nextLine(); // discard input so user can try again    
                System.out.printf(                                          
                "You must enter integers. Please try again.%n%n");          
            }                                                              
            catch (ArithmeticException arithmeticException) {              
                System.err.printf("%nException: %s%n", arithmeticException);
                System.out.printf(                                          
                "Zero is an invalid denominator. Please try again.%n%n");   
            }             
            // finally block, if present, will execute whether or not an exception is thrown
            // in the corresponding try block. even if the try block exits with a 
            // return, break or continue                                                 
        } while (continueLoop);      
        scanner.close();                                     
    } 
} 
