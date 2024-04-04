package cs.map.lab7.controller;

import cs.map.lab7.repository.PrietenieDBRepository;
import cs.map.lab7.repository.RequestDBRepository;
import cs.map.lab7.repository.UtilizatorDBRepository;
import cs.map.lab7.service.Service;
import javafx.event.ActionEvent;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Modality;
import javafx.stage.Stage;

import java.io.IOException;

public class SceneSwitcher {
    public static void switchSceneAndCloseCurrent(ActionEvent event, String fxmlPath, Object controller,
                                                  UtilizatorDBRepository repoUtilizator,
                                                  PrietenieDBRepository repoPrietenie, RequestDBRepository repoRequest,
                                                  Service service, String username) throws IOException {

        Stage currentStage = (Stage) ((Node) event.getSource()).getScene().getWindow();
        FXMLLoader loader = new FXMLLoader(SceneSwitcher.class.getResource(fxmlPath));
        Parent root = loader.load();

        // Obține controlerul după încărcarea fișierului FXML
        Object loadedController = loader.getController();

        if (loadedController instanceof BaseController) {
            BaseController baseController = (BaseController) loadedController;

            // Setează dependințele în controler

            baseController.setUserRepository(repoUtilizator);
            baseController.setRepoPrietenie(repoPrietenie);
            baseController.setRepoRequest(repoRequest);
            baseController.setUserService(service);
            // Verifică dacă controlerul acceptă parametrul username
            if (baseController instanceof AppController) {
                ((AppController) baseController).setCurentUserName(username);
            }
        }

        currentStage.setScene(new Scene(root));

        currentStage.show();
        // Resetează stadiul ferestrei după ce fereastra este închisă
        currentStage = null;
    }
}