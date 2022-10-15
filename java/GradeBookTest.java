package chapter_07;

public class GradeBookTest {
    public static void main(String[] args) {
       // array of student grades                                      
       int[][] gradesArray = {  {87, 68, 94},
                                {23, 43, 54},
                                {43, 67, 8},
                                {23, 9, 98},
                                {98, 89, 45}};
       
       GradeBook myGradeBook = new GradeBook(
        "CS101 Introduction to Java Programming", gradesArray);
       System.out.printf("Welcome to the grade book for%n%s%n%n", 
            myGradeBook.getCourseName());
       myGradeBook.processGrades();
    } 
 } 
