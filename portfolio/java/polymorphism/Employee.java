// Employee abstract superclass
// Cannot be used directly to create objects

public abstract class Employee {
    private final String firstName;
    private final String lastName;
    private final String socialSecurityNumber;

    // constructor, validation skipped in this example
    public Employee(String firstName, String lastName, String socialSecurityNumber){
        this.firstName = firstName;
        this.lastName = lastName;
        this.socialSecurityNumber = socialSecurityNumber;
    }

    // return first name
    public String getFirstName() {return firstName;}
    // return last name
    public String getLastName() {return lastName;}
    // return ssn name
    public String getSocialSecurityNumber() {return socialSecurityNumber;}

    //return String representation of employee object
    // override toString from object (from which all classes inherit)
    @Override
    public String toString(){
        // using get methods bc private variables are not accessible by subclasses
        return String.format("%s %s%nsocial security number: %s", getFirstName(), getLastName(), getSocialSecurityNumber());

    }
    // abstract method must be overriden by concrete subclasses
    public abstract double earnings(); // no implementation here

}