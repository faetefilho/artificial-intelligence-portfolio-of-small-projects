// Employee hierarchy test program.

public class PayrollSystemTest {
    public static void main(String[] args) {
        // create subclass objects                                          
        
        CommissionEmployee commissionEmployee =                             
            new CommissionEmployee(                                          
            "Sue", "Jones", "333-33-3333", 10000, .06);                      
        BasePlusCommissionEmployee basePlusCommissionEmployee =             
            new BasePlusCommissionEmployee(                                  
            "Bob", "Lewis", "444-44-4444", 5000, .04, 300);                  
    
        System.out.println("Employees processed individually:");
    
        System.out.printf("%s%n%s: $%,.2f%n%n",
            commissionEmployee, "earned", commissionEmployee.earnings());
        System.out.printf("%s%n%s: $%,.2f%n%n", 
            basePlusCommissionEmployee, 
            "earned", basePlusCommissionEmployee.earnings());
    
        // create four-element Employee array
        Employee[] employees = new Employee[2]; 
    
        // initialize array with Employees                   
        employees[0] = commissionEmployee;        
        employees[1] = basePlusCommissionEmployee;
    
        System.out.printf("Employees processed polymorphically:%n%n");
    
        // generically process each element in array employees
        for (Employee currentEmployee : employees) {
            System.out.println(currentEmployee); // invokes toString
    
            // determine whether element is a BasePlusCommissionEmployee
            if (currentEmployee instanceof BasePlusCommissionEmployee) {
                // downcast Employee reference to 
                // BasePlusCommissionEmployee reference
                // also this is a reference to employee[1], will change the array. keyword new not used
                // This casting is required if we want to access the subclass methods 
                // on the current employee object
                // Attempting the invoke a subclass-only method directly on a superclass 
                // reference is a compilation error
                BasePlusCommissionEmployee employee = 
                    (BasePlusCommissionEmployee) currentEmployee;
    
                employee.setBaseSalary(1.10 * employee.getBaseSalary());
    
                System.out.printf(
                    "new base salary with 10%% increase is: $%,.2f%n",
                    employee.getBaseSalary());
            } 
    
            // calling earnings polymorphically
            System.out.printf(
                "earned $%,.2f%n%n", currentEmployee.earnings());
        } 
    
        // get type name of each object in employees array
        for (int j = 0; j < employees.length; j++) {      
            System.out.printf("Employee %d is a %s%n", j,  
                employees[j].getClass().getName());         
        }    

        // Note they all changed, as they are references
        System.out.println(employees[1]);  
        System.out.println(basePlusCommissionEmployee);                                  
    } 
 } 
 
