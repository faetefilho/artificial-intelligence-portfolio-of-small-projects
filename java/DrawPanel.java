package chapter_04;
// Graphics: provide methods for drawing text and shapes on the screen
import java.awt.Graphics;
// JPanel: provides an area on which we can draw
import javax.swing.JPanel;

// extends indicate this class is enhanced type of JPanel, this is inheritance
// JPanel is the superclass and DrawPanel the subclass
public class DrawPanel extends JPanel
{
    // draws an X from the corners of the panel
    public void paintComponent(Graphics g)
    {
        // call paintComponent to ensure the panel displays correctly
        super.paintComponent(g);

        int width = getWidth();
        int height = getHeight();

        //draw a line from the upper-left to the lower-right
        g.drawLine(0, 0, width, height);

        //draw a line from the lower-left to the upper-right
        g.drawLine(0, height, width, 0);
    }
}
