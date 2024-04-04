package cs.map.lab7.controller;

import cs.map.lab7.domain.*;
import cs.map.lab7.repository.*;
import cs.map.lab7.service.Service;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.StackPane;
import javafx.stage.Stage;

import java.io.IOException;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.time.format.FormatStyle;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

import static cs.map.lab7.controller.SceneSwitcher.switchSceneAndCloseCurrent;
import static cs.map.lab7.controller.UserControler.showErrorPopup;

public class AppController implements BaseController {
    @FXML
    public ComboBox<Integer> elementePagina;
    @FXML
    public Button Delogare;
    @FXML
    public TableView<FriendRequest> requestTableView;
    @FXML
    public TableColumn<Utilizator, String> userNameRequest;
    @FXML
    public TableColumn<FriendRequest, LocalDate> requestData;
    @FXML
    public TextField usernameMesaj;
    @FXML
    public TextArea mesaj;
    @FXML
    public Button trimiteMesaj;
    @FXML
    public Button conversatie;
    @FXML
    public TextField getRequestTo;

    @FXML
    private TableView<Utilizator> prietenieTableView;
    @FXML
    public TableColumn<Utilizator, String> nume;
    @FXML
    public TableColumn<Utilizator, String> prenume;
    @FXML
    public TableColumn<Utilizator, String> userName;

    private UtilizatorDBRepository repoUtilizator;
    private PrietenieDBRepository repoPrietenie;
    private RequestDBRepository repoRequest;
    private Service service;

    ObservableList<Utilizator> userModel = FXCollections.observableArrayList();

    ObservableList<FriendRequest> requestModel = FXCollections.observableArrayList();

    String curentUserName;

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

    public void setCurentUserName(String username) {
        curentUserName = username;
        initModel();
        initModelRequest();
    }

    @FXML
    public void initialize() {
        prietenieTableView.setItems(userModel);
        requestTableView.setItems(requestModel);

        nume.setCellValueFactory(new PropertyValueFactory<>("lastName"));
        prenume.setCellValueFactory(new PropertyValueFactory<>("firstName"));
        userName.setCellValueFactory(new PropertyValueFactory<>("username"));

        userNameRequest.setCellValueFactory(new PropertyValueFactory<>("username"));
        requestData.setCellValueFactory(new PropertyValueFactory<>("data"));
    }


    private void initModel() {
        userModel.setAll(StreamSupport.stream(service.getUserFriendsIterable(curentUserName).spliterator(),
                false).collect(Collectors.toList()));
    }

    private void initModelRequest() {
        requestModel.setAll(StreamSupport.stream(service.getUsersFriendRequest(curentUserName).spliterator(),
                false).collect(Collectors.toList()));
    }

    @FXML
    public void switchToLogare(ActionEvent event) throws IOException {
        LoginController appController = new LoginController();
        switchSceneAndCloseCurrent(event, "/cs/map/lab7/views/logare-view.fxml",
                appController, repoUtilizator, repoPrietenie, repoRequest, service, "");
    }

    @FXML
    public void adaugaMesaj(ActionEvent actionEvent) {
        try {
            String username_to = this.usernameMesaj.getText();
            if (username_to.isEmpty()) throw new Exception("Username null!");
            String mesajUser = this.mesaj.getText();
            if (mesajUser.isEmpty()) throw new Exception("Mesaj null!");

            Utilizator user_from = service.findAfterUserName(curentUserName).get();
            if (service.findAfterUserName(username_to).isEmpty()) throw new Exception("Nu exista utilizatorul!");
            Utilizator user_to = service.findAfterUserName(username_to).get();
            List<Long> l = new ArrayList<>();
            l.add(user_to.getId());
            service.addMessage(user_from.getId(), l, mesajUser);

            usernameMesaj.clear();
            mesaj.clear();

        } catch (Exception e) {
            System.out.println(e.getMessage());
            showErrorPopup(e.getMessage());
        }
    }

    private void openSecondaryWindow(String deAfisat) {
        // Creează o nouă fereastră (Stage)
        Stage secondaryStage = new Stage();
        secondaryStage.setTitle("Fereastra Secundară");

        // Creează un obiect Label cu șirul
        javafx.scene.control.Label label = new javafx.scene.control.Label(deAfisat + "\n\n\n");

        // Layout pentru fereastra secundară
        StackPane secondaryLayout = new StackPane();
        secondaryLayout.getChildren().add(label);

        // Setează scena pentru fereastra secundară
        Scene secondaryScene = new Scene(secondaryLayout);
        secondaryStage.setScene(secondaryScene);
        secondaryStage.setWidth(300);

        // Arată fereastra secundară
        secondaryStage.show();
    }

    @FXML
    private void afisareConversatii(ActionEvent actionEvent) {
        try {

            String username_to = this.usernameMesaj.getText();
            if (service.findAfterUserName(username_to).isEmpty()) throw new Exception("Nu exista utilizatorul!");
            Utilizator user_to = service.findAfterUserName(username_to).get();

            Utilizator user_from = service.findAfterUserName(curentUserName).get();


            String str = service.conversation(user_from.getId(), user_to.getId()).stream()
                    .map(tup -> tup.getFrom().getLastName() + " " + tup.getFrom().getFirstName() + ": " +
                            tup.getMessage() + "\nTrimis la: " +
                            tup.getData().format(DateTimeFormatter.ofLocalizedTime(FormatStyle.MEDIUM)) + '\n')
                    .collect(Collectors.joining("\n"));
            usernameMesaj.clear();
            mesaj.clear();
            openSecondaryWindow(str);
        } catch (Exception e) {
            System.out.println(e.getMessage());
            showErrorPopup(e.getMessage());
        }

    }

    @FXML
    private void accepta(ActionEvent actionEvent) {
        FriendRequest selected = requestTableView.getSelectionModel().getSelectedItem();
        if (selected != null && Objects.equals(selected.getStatus(), Status.pending)) {
            service.updateRequest(selected, Status.approved);
            service.addFriendship(selected.getIdfrom(), selected.getIdto(), selected.getData());
            repoRequest.delete(new Tuple<>(selected.getIdfrom(), selected.getIdto()));
            initModelRequest();
            initModel();
        } else {
            assert selected != null;
            if (Objects.equals(selected.getStatus(), Status.rejected))
                MessageAlert.showErrorMessage(null, "Cererea este respinsa!");
            else if (Objects.equals(selected.getStatus(), Status.approved))
                MessageAlert.showErrorMessage(null, "Cererea este acceptata!");
            else
                MessageAlert.showErrorMessage(null, "Nici o cerere selectata!");
        }

    }

    @FXML
    private void respinge(ActionEvent actionEvent) {
        FriendRequest selected = requestTableView.getSelectionModel().getSelectedItem();
        if (selected != null && Objects.equals(selected.getStatus(), Status.pending)) {
            service.updateRequest(selected, Status.rejected);
            repoRequest.delete(new Tuple<>(selected.getIdfrom(), selected.getIdto()));
            initModelRequest();
        } else {
            assert selected != null;
            if (Objects.equals(selected.getStatus(), Status.approved))
                MessageAlert.showErrorMessage(null, "Cererea este acceptata!");
            else if (Objects.equals(selected.getStatus(), Status.rejected))
                MessageAlert.showErrorMessage(null, "Cererea este respinsa!");
            else
                MessageAlert.showErrorMessage(null, "Nici o cerere selectata!");
        }
    }

    @FXML
    private void deleteRequest(ActionEvent actionEvent) {
        FriendRequest selected = requestTableView.getSelectionModel().getSelectedItem();
        if (selected != null) {
            repoRequest.delete(new Tuple<>(selected.getIdfrom(), selected.getIdto()));
            initModelRequest();
        } else {
            MessageAlert.showErrorMessage(null, "Nici o cerere selectata!");
        }
    }

    @FXML
    private void addRequest(ActionEvent actionEvent) {
        try {
            String username_to = this.getRequestTo.getText();
            if (username_to.isEmpty()) throw new Exception("Username null!");
            if (service.findAfterUserName(username_to).isEmpty()) throw new Exception("Nu exista utilizatorul!");
            Utilizator user_to = service.findAfterUserName(username_to).get();

            Utilizator user_from = service.findAfterUserName(curentUserName).get();

            if (repoPrietenie.findOne(new Tuple<>(user_from.getId(), user_to.getId())).isPresent())
                throw new Exception("Exista deja prietenia!");
            if (repoRequest.findOne(new Tuple<>(user_from.getId(), user_to.getId())).isPresent() &&
                    Objects.equals(repoRequest.findOne(new Tuple<>(user_from.getId(), user_to.getId())).get().getStatus(), Status.rejected))
                service.updateRequest(repoRequest.findOne(new Tuple<>(user_from.getId(), user_to.getId())).get(), Status.pending);
            else
                service.addRequest(user_from.getId(), user_to.getId());
            initModelRequest();
            getRequestTo.clear();
            MessageAlert.showMessage(null, Alert.AlertType.CONFIRMATION, "Atentie!", "Cerere Trimisa");

        } catch (Exception e) {
            System.out.println(e.getMessage());
            showErrorPopup(e.getMessage());
        }

    }

    @FXML
    private void deleteFriendship(ActionEvent actionEvent) {
        Utilizator selected = prietenieTableView.getSelectionModel().getSelectedItem();
        if (selected != null) {
            Utilizator curentUser = service.findAfterUserName(curentUserName).get();
            service.deleteFriendship(curentUser.getId(), selected.getId());
            initModel();
        } else {
            MessageAlert.showErrorMessage(null, "Nici o persoana selectata!");
        }
    }


}
