package chapter_03;
public class Account // class names begins with uppercase
    // variables and methods begin with lower case
{   
    // private: accessible only to methods in the class in which
    // they are declared
    private String name;  // instance variable
    private double balance = 0;
    // primitive instance variables are initialized by default
    // local variables are not initilized by default
    
    // constructor initializes name with parameter name
    // constructor must have same name as class, cannot return values
    public Account(String name, double balance)
    {
        this.name = name;
        if (balance > 0)
            this.balance = balance;
    }

    public void deposit(double depositAmount)
    {
        // local variables must be initialized explicitly
        if (depositAmount > 0.0)
            //this is the instance variable and there is no ambiguity 
            balance = balance + depositAmount;
    }

    public double getBalance()
    {
        return balance;
    }
    // method to set the name in the object, note that it can change a 
    // private instance variable
    public void setName(String name)
    {
        // keyword this refer to this object
        // could have chosen different name for the parameter
        // but using this is widely accepted practice
        this.name = name;
    }

    // method to retrieve name from object
    public String getName()
    {
        return name;
    }

}
