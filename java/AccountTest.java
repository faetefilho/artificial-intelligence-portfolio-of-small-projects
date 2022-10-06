package chapter_03;
// AccountTest.java Driver application
import java.util.Scanner;

public class AccountTest 
{
    // a static method is special, bc you can call it without first creating
    // an object of the class in which the method is declared
    public static void main(String[] args)
    {
        // create Scanner object to get input
        Scanner input = new Scanner(System.in);

        // create an account object account1
        // Declaring an account constructor for a custom object initialization
        Account account1 = new Account("Buzz Lightyear", 70);
        // bc constructor was created, compiler will not create default constructor
        // so statement below cannot be used
        //Account account2 = new Account();

        // display initial value for instance variable, null (for string type)
        // every instance variable has a default initial value, so they dont
        // need to be initialized
        System.out.printf("%s balance is: $%.2f%n", account1.getName(), account1.getBalance());
        
        //prompt for and read name
        System.out.println("Please enter name: ");
        try
        {
            String theName = input.nextLine();
            account1.setName(theName);
        }
        finally
        {
            //input.close();
        }
        
        // prompt for and read balance
        System.out.println("Enter deposit amount: ");
        try
        {
            double depositAmount = input.nextDouble();  // return double value
            account1.deposit(depositAmount);
        }
        finally
        {
            input.close();
        }
        
        System.out.println();  // blank line

        //display the name stored in object account1
        System.out.printf("Name in object account is: %n%s%n", account1.getName());
        // display balance
        System.out.printf("%s balance is: $%.2f%n", account1.getName(), account1.getBalance());

    }

}
