package chapter_05;

public class AutoPolicy 
{
    private int accountNumber;
    private String makeAndModel;
    private String state;
    
    // constructor
    public AutoPolicy(int accountNumber, String makeAndModel, String state)
    {
        this.accountNumber = accountNumber;
        this.makeAndModel = makeAndModel;
        this.state = state;
    }

    //set account Number
    public void setAccountNumber( int accountNumber)
    {
        this.accountNumber = accountNumber;
    }

    // return account nu,ber
    public int getAccountNumber()
    {
        return accountNumber;
    }

    // sets make and model
    public void setMakeAndModel(String makeAndModel)
    {
        this.makeAndModel = makeAndModel;
    }

    // returns make and model
    public String getMakeAndModel()
    {
        return makeAndModel;
    }

    //set the state
    public void setState(String state)
    {
        this.state = state;
    }

    // return state
    public String getState()
    {
        return state;
    }

    // check if there is no fault insirrance
    public boolean isNoFaultState()
    {
        boolean noFaultState;

        switch (getState())
        {
            case "MA":
            case "NJ":
            case "NY":
            case "PA":
                noFaultState = true;
                break;
            default:
                noFaultState = false;
                break;
        }

        return noFaultState;
    }
}
