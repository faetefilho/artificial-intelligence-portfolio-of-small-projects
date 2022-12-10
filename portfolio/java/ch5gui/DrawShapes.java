import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

public class DrawShapes extends Application {
    @Override
    public void start(Stage stage) throws Exception{
        // Loads DrawShapes.fxml and configures the DrawShapesController
        Parent root = FXMLLoader.load(getClass().getResource("DrawShapes.fxml"));
        Scene scene = new Scene(root); // attach scene graph to scene
        stage.setTitle("DrawShapes"); // window title bar
        stage.setScene(scene); // attach scene to stage
        stage.show(); // display the stage
    }

    // application execution starts here
    public static void main(String[] args){
        launch(args); //create drawLines object and call its start method
    }
}
