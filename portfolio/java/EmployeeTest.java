package chapter_08;

public class EmployeeTest {
    public static void main(String[] args) {
       // show that count is 0 before creating Employees
       // static class variables and methods exists, and can be used, 
       // even if no objects of that class have been instantiated
       System.out.printf("Employees before instantiation: %d%n",
          Employee.getCount());
 
       // create two Employees; count should be 2
       Employee e1 = new Employee("Susan", "Baker");
       Employee e2 = new Employee("Bob", "Blue");   
     
       // show that count is 2 after creating two Employees
       System.out.printf("%nEmployees after instantiation:%n");
       // invoke every static method by using the class name and a dot (.) 
       // to emphasize that the method being called is a static method
       System.out.printf("via e1.getCount(): %d%n", Employee.getCount());
       System.out.printf("via e2.getCount(): %d%n", Employee.getCount());
       System.out.printf("via Employee.getCount(): %d%n", 
          Employee.getCount());
    
       // get names of Employees
       System.out.printf("%nEmployee 1: %s %s%nEmployee 2: %s %s%n",
          e1.getFirstName(), e1.getLastName(), 
          e2.getFirstName(), e2.getLastName());
    } 
 } 
