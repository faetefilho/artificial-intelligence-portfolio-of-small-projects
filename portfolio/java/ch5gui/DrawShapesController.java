
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;

public class DrawShapesController {

    @FXML // controller class instance variable for fx:id canvas in GUI
    private Canvas canvas; // to get the Graphics context

    @FXML
    void drawOvalsButtonPressed(ActionEvent event) {
        draw("Ovals");

    }

    @FXML
    void drawRectanglesButtonPressed(ActionEvent event) {
        draw("Rectangles");
    }

    
    public void draw(String choice) {
        GraphicsContext gc = canvas.getGraphicsContext2D();
        
        //clear canvas for next shape
        gc. clearRect(0, 0, canvas.getWidth(), canvas.getHeight());

        int step = 10;

        //draw 10 overlapping shapes
        for (int i = 0; i < 10; i++){
            switch (choice){
                case "Rectangles":
                    gc.strokeRect(10 + i * step, 10 + i * step, 90 + i * step, 90 + i * step);
                    break;
                case "Ovals":
                    gc.strokeOval(10 + i * step, 10 + i * step, 90 + i * step, 90 * step);
                    break;
            }
        }

    }

}

