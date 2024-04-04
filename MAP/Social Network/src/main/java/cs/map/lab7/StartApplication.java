package cs.map.lab7;
import javax.crypto.Cipher;
import javax.crypto.KeyGenerator;
import javax.crypto.SecretKey;
import java.util.Base64;
import cs.map.lab7.controller.UserControler;
import cs.map.lab7.repository.MessageDBRepository;
import cs.map.lab7.repository.PrietenieDBRepository;
import cs.map.lab7.repository.RequestDBRepository;
import cs.map.lab7.repository.UtilizatorDBRepository;
import cs.map.lab7.service.Service;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

public class StartApplication extends Application {


    public static void main(String[] args) {
        launch();
    }

    @Override
    public void start(Stage primaryStage) throws Exception {

        String url = "jdbc:postgresql://localhost:5432/socialnetwork";
        String user = "postgres";
        String password = "Parola";

        SecretKey secretKey = KeyGenerator.getInstance("AES").generateKey();

        UtilizatorDBRepository userDBRepository = new UtilizatorDBRepository(url, user, password, secretKey);
        PrietenieDBRepository prietenieDBRepository = new PrietenieDBRepository(url, user, password);
        RequestDBRepository requestDBRepository = new RequestDBRepository(url, user, password, secretKey);
        MessageDBRepository messageDBRepository = new MessageDBRepository(url, user, password, userDBRepository);

        Service service = new Service(userDBRepository, prietenieDBRepository, requestDBRepository, messageDBRepository);

        FXMLLoader fxmlLoader = new FXMLLoader(StartApplication.class.getResource("views/users-view.fxml"));
        Scene scene = new Scene(fxmlLoader.load());
        UserControler controler = fxmlLoader.getController();

        controler.setUserRepository(userDBRepository);
        controler.setRepoPrietenie(prietenieDBRepository);
        controler.setRepoRequest(requestDBRepository);
        controler.setUserService(service);

        service.updateAllUsers();

        primaryStage.setTitle("Users");
        primaryStage.setScene(scene);
        primaryStage.show();
    }


}
