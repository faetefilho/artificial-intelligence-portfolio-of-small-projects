
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;

public class DrawLinesController {

    @FXML // controller class instance variable for fx:id canvas in GUI
    private Canvas canvas; // to get the Graphics context

    @FXML
    void drawLinesButtonPressed(ActionEvent event) {
        GraphicsContext gc = canvas.getGraphicsContext2D();
        // draw line from upper-left to lower-right
        gc.strokeLine(0, 0, canvas.getWidth(), canvas.getHeight());
        // draw line from upper-right to lower-left
        gc.strokeLine(canvas.getWidth(), 0, 0, canvas.getHeight());

    }

}

