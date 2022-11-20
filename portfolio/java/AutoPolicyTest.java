package chapter_05;

public class AutoPolicyTest 
{
    public static void main(String[] args)
    {
        AutoPolicy policy1 = new AutoPolicy(111, "Toyota Camry", "NJ");
        AutoPolicy policy2 = new AutoPolicy(222, "Tesla Model 3", "ME");

        policyInNoFaultState(policy1);
        policyInNoFaultState(policy2);
    }   
    
    //display wether each policy is a no-fault
    

    public static void policyInNoFaultState(AutoPolicy policy)
    {
        System.out.println("The auto policy:");
        System.out.printf("Account #: %d; Car: %s; State %s %s a no-fault state%n%n",
            policy.getAccountNumber(), policy.getMakeAndModel(),
            policy.getState(), (policy.isNoFaultState() ? "is": "is not") );
 
    }


}
