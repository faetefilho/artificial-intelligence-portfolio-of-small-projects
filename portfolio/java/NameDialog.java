package chapter_03;

import javax.swing.JOptionPane;

public class NameDialog 
{
    public static void main(String[] args) 
    {
        String name = JOptionPane.showInputDialog("What is your name", args);

        String message = String.format("Welcome to Java Programming %s", name);

        JOptionPane.showMessageDialog(null, message, message, 0);

    }
}
