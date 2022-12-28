public interface Payable {
    public abstract double getPaymentAmount();
}
// for the implementation of this interface on another class:
// public class Invoice implements Payable{
//  ...
//  ...
//  @Override
//  public double getPaymentAmount() {
//      return someCalculationHere();
//}    
//}