package cs.map.lab7.controller;

import cs.map.lab7.domain.Utilizator;
import cs.map.lab7.repository.PrietenieDBRepository;
import cs.map.lab7.repository.RequestDBRepository;
import cs.map.lab7.repository.UtilizatorDBRepository;
import cs.map.lab7.service.Service;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.stage.Stage;

import java.io.IOException;
import java.util.Objects;

import static cs.map.lab7.controller.SceneSwitcher.switchSceneAndCloseCurrent;

public class LoginController implements BaseController {

    public Button Login;
    public PasswordField getPassword;
    public TextField getUser;
    private UtilizatorDBRepository repoUtilizator;
    private PrietenieDBRepository repoPrietenie;
    private RequestDBRepository repoRequest;
    private Service service;

    public void setUserRepository(UtilizatorDBRepository userRepository) {
        this.repoUtilizator = userRepository;
    }

    public void setRepoPrietenie(PrietenieDBRepository repo) {
        this.repoPrietenie = repo;
    }

    public void setRepoRequest(RequestDBRepository repo) {
        this.repoRequest = repo;
    }

    public void setUserService(Service srv) {
        this.service = srv;
    }

    public static void showErrorPopup(String message) {
        Alert alert = new Alert(Alert.AlertType.ERROR);
        alert.setTitle("Error");
        alert.setHeaderText("An error has occured");
        alert.setContentText(message);
        alert.showAndWait();
    }

    @FXML
    public void switchToApp(ActionEvent event) throws IOException {

        try {
            int ok = 0;
            String username = this.getUser.getText();
            String password = this.getPassword.getText();
            if (service.existaUser(username,password)) {
                ok = 1;
                AppController appController = new AppController();
                switchSceneAndCloseCurrent(event, "/cs/map/lab7/views/app-view.fxml",
                        appController, repoUtilizator, repoPrietenie, repoRequest, service, username);
            }
            if (ok == 0) throw new Exception("Utilizator sau parola gresite");
        } catch (Exception e) {
            System.out.println(e.getMessage());
            showErrorPopup(e.getMessage());
        }
    }
}
