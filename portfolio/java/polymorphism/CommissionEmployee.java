// CommissionEmpployee class extends Employee

public class CommissionEmployee extends Employee{
    private double grossSales;
    private double commissionRate;

    // constructor
    public CommissionEmployee(String firstName, String lastName, String socialSecurityNumber,
    double grossSales, double commissionRate){
        super(firstName, lastName, socialSecurityNumber);
        if (commissionRate <= 0.0 || commissionRate>=1){
            throw new IllegalArgumentException("Commission rate must be >0 and <1");
        }
        if (grossSales < 0){
            throw new IllegalArgumentException("Gross sales must be positive");
        }

        this.grossSales = grossSales;
        this.commissionRate = commissionRate;

    }

    // set gross sales
    public void setGrossSales (double grossSales){
        if (grossSales < 0){
            throw new IllegalArgumentException("Gross Sales has to be positive");
        }
        this.grossSales = grossSales;
    }
    // rеturn gross sales
    public double getGrossSales() {
        return grossSales;
    }
    // set commission rate
    public void setCommissionRate(double commissionRate){
        if (commissionRate <= 0 || commissionRate >=1){
            throw new IllegalArgumentException("Commission rate must be  >0 and < 1");
        }
        this.commissionRate = commissionRate;
    }
    // return commission rate
    public double getCommissionRate() {return commissionRate;}
    // calculate earnings; override abstract method
    @Override
    public double earnings() {
        return getCommissionRate() * getGrossSales();
    }
    // return String representation of commission employee
    @Override
    public String toString(){
        return String.format("%s: %s%n%s: $%,.2f; %s: %.2f", "commission employee",
        super.toString(), "gross sales", getGrossSales(), "commission. rate", getCommissionRate());
    } 


}