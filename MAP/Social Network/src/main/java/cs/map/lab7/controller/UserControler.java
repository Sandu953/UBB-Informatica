package cs.map.lab7.controller;


import cs.map.lab7.domain.*;
import cs.map.lab7.repository.*;
import cs.map.lab7.service.Service;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.StackPane;
import javafx.stage.Modality;
import javafx.stage.Stage;

import java.io.IOException;
import java.sql.Date;
import java.time.format.DateTimeFormatter;
import java.time.format.FormatStyle;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;
import java.util.Optional;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class UserControler {

    @FXML
    public Button btnUpdate;
    @FXML
    public Button btnAdMesaj;
    @FXML
    public TextField getIDFrom;
    @FXML
    public TextField getIDTo;
    @FXML
    public TextArea getMesaj;
    @FXML
    public Button btnConv;

    @FXML
    public Button btnAddCerere;
    @FXML
    public TextField getIDFromR;
    @FXML
    public TextField getIDToR;
    @FXML
    public Button accepta;
    @FXML
    public Button respinge;
    @FXML
    public Button btnDelCerere;
    @FXML
    public Button nextUser;
    @FXML
    public Button nextRequest;
    @FXML
    public Button previousUser;
    @FXML
    public Button previousRequest;
    @FXML
    public Button logare;
    public Label curentPageLabel;
    public Label maximPageLabel;


    @FXML
    private TextField getNume;
    @FXML
    private TextField getID;
    @FXML
    private TextField getPrenume;
    @FXML
    private TextField getN;
    @FXML
    private TextField getLuna;
    @FXML
    private TextField getIDLuna;
    @FXML
    private TextField getStr;
    @FXML
    private TableView<Utilizator> userTableView;
    @FXML
    private TableColumn<Utilizator, Long> id;
    @FXML
    private TableColumn<Utilizator, String> nume;
    @FXML
    private TableColumn<Utilizator, Status> prenume;

    @FXML
    public TableView<FriendRequest> requestTableView;
    @FXML
    public TableColumn<FriendRequest, Long> idfrom;
    @FXML
    public TableColumn<FriendRequest, Long> idto;
    @FXML
    public TableColumn<FriendRequest, Date> data_from;
    @FXML
    public TableColumn<FriendRequest, String> status;
    @FXML
    public ComboBox<Integer> elementePagina;
    ObservableList<Utilizator> userModel = FXCollections.observableArrayList();
    ObservableList<FriendRequest> requestModel = FXCollections.observableArrayList();
    private UtilizatorDBRepository repoUtilizator;
    private PrietenieDBRepository repoPrietenie;
    private RequestDBRepository repoRequest;
    private Service service;
    private int currentPageUser = 0;
    private int currentPageRequest = 0;
    private int pageSize = 5;
    private int totalNumberOfElements = 0;

    public void setUserRepository(UtilizatorDBRepository userRepository) {
        this.repoUtilizator = userRepository;
        //initModel();

    }

    public void setRepoPrietenie(PrietenieDBRepository repo) {
        this.repoPrietenie = repo;
    }

    public void setRepoRequest(RequestDBRepository repo) {
        this.repoRequest = repo;
        //initModelRequest();
    }

    public void setUserService(Service srv) {
        this.service = srv;
        initModel();
        initModelRequest();
        List<Integer> lista = new ArrayList<>();
        for (int i = 1; i <= 10; i++)
            lista.add(i);
        ObservableList<Integer> List = FXCollections.observableArrayList(lista);
        elementePagina.setItems(List);
    }


    @FXML
    public void initialize() {
        userTableView.setItems(userModel);

        id.setCellValueFactory(new PropertyValueFactory<>("id"));
        nume.setCellValueFactory(new PropertyValueFactory<>("lastName"));
        prenume.setCellValueFactory(new PropertyValueFactory<>("firstName"));

        idfrom.setCellValueFactory(new PropertyValueFactory<>("idfrom"));
        idto.setCellValueFactory(new PropertyValueFactory<>("idto"));
        data_from.setCellValueFactory(new PropertyValueFactory<>("data"));
        status.setCellValueFactory(new PropertyValueFactory<>("status"));
        requestTableView.setItems(requestModel);

    }

    @FXML
    public void setPageSize(ActionEvent actionEvent) {
        this.pageSize = elementePagina.getValue();
        currentPageRequest = 0;
        currentPageUser = 0;
        initModel();
        initModelRequest();
    }

    private void initModel() {

        Page<Utilizator> page = service.findAllUsers(new Pageable(currentPageUser, pageSize));

        int maxPage = (int) Math.ceil((double) page.getTotalElementCount() / pageSize) - 1;
        if (currentPageUser > maxPage) {
            currentPageUser = maxPage;
            page = service.findAllUsers(new Pageable(currentPageUser, pageSize));
        }

        userModel.setAll(StreamSupport.stream(page.getElementsOnPage().spliterator(),
                false).collect(Collectors.toList()));
        totalNumberOfElements = page.getTotalElementCount();

        previousUser.setDisable(currentPageUser == 0);
        nextUser.setDisable((currentPageUser + 1) * pageSize >= totalNumberOfElements);
        curentPageLabel.setText(String.valueOf(currentPageUser + 1));
        maximPageLabel.setText("/"+(maxPage+ 1));
    }

    private void initModelRequest() {

        Page<FriendRequest> page = service.findAllRequest(new Pageable(currentPageRequest, pageSize));

        int maxPage = (int) Math.ceil((double) page.getTotalElementCount() / pageSize) - 1;
        if (currentPageRequest > maxPage) {
            currentPageRequest = maxPage;
            page = service.findAllRequest(new Pageable(currentPageRequest, pageSize));
        }

        requestModel.setAll(StreamSupport.stream(page.getElementsOnPage().spliterator(),
                false).collect(Collectors.toList()));
        totalNumberOfElements = page.getTotalElementCount();

        previousRequest.setDisable(currentPageRequest == 0);
        nextRequest.setDisable((currentPageRequest + 1) * pageSize >= totalNumberOfElements);
    }

    private static Stage logareStage;

    @FXML
    public void logare(ActionEvent event) throws IOException {

        if (logareStage == null) { // Dacă fereastra nu este deja deschisă
            FXMLLoader loader = new FXMLLoader(getClass().getResource("/cs/map/lab7/views/logare-view.fxml"));

            Parent root = loader.load();

            LoginController controller = loader.getController();
            controller.setUserRepository(repoUtilizator);
            controller.setRepoPrietenie(repoPrietenie);
            controller.setRepoRequest(repoRequest);
            controller.setUserService(service);


            logareStage = new Stage();
            logareStage.setScene(new Scene(root));

            // Blochează interacțiunea cu fereastra principală până când fereastra de logare este închisă
            logareStage.initModality(Modality.APPLICATION_MODAL);

            // Adăugați un listener pentru evenimentul de închidere a ferestrei pentru a reseta stadiul ferestrei
            logareStage.setOnCloseRequest(windowEvent -> {
                logareStage = null;
            });

            // Așteaptă până când fereastra de logare este închisă
            logareStage.showAndWait();
            initModel();
            initModelRequest();
        }
    }


    @FXML
    public void onPreviousUser(ActionEvent actionEvent) {
        currentPageUser--;
        initModel();
    }

    @FXML
    public void onNextUser(ActionEvent actionEvent) {
        currentPageUser++;
        initModel();
    }

    @FXML
    public void onPreviousRequest(ActionEvent actionEvent) {
        currentPageRequest--;
        initModelRequest();
    }

    @FXML
    public void onNextRequest(ActionEvent actionEvent) {
        currentPageRequest++;
        initModelRequest();
    }

    public static void showErrorPopup(String message) {
        Alert alert = new Alert(Alert.AlertType.ERROR);
        alert.setTitle("Error");
        alert.setHeaderText("An error has occured");
        alert.setContentText(message);
        alert.showAndWait();
    }

    @FXML
    private void adauga(ActionEvent actionEvent) {
        try {
            long id = Long.parseLong(this.getID.getText());
            String nume = this.getNume.getText();
            if (nume.isEmpty()) throw new Exception("Nume null!");
            String prenume = this.getPrenume.getText();
            if (prenume.isEmpty()) throw new Exception("Prenume null!");
            service.addUtilizator(id, prenume, nume);

            getID.clear();
            getNume.clear();
            getPrenume.clear();

            initModel();
        } catch (Exception e) {
            System.out.println(e.getMessage());
            showErrorPopup(e.getMessage());
        }

    }

    @FXML
    private void adaugaMesaj(ActionEvent actionEvent) {
        try {
            long id_from = Long.parseLong(this.getIDFrom.getText());
            String[] id_to = this.getIDTo.getText().split(",");
            if (id_to.length == 0) throw new Exception("ID To null!");
            List<Long> l = new ArrayList<>();
            for (String s : id_to) {
                l.add(Long.parseLong(s));
            }
            String mesaj = this.getMesaj.getText();
            if (mesaj.isEmpty()) throw new Exception("Mesaj null!");
            service.addMessage(id_from, l, mesaj);
            getIDFrom.clear();
            getIDTo.clear();
            getMesaj.clear();
        } catch (Exception e) {
            System.out.println(e.getMessage());
            showErrorPopup(e.getMessage());
        }

    }

    @FXML
    private void addRequest(ActionEvent actionEvent) {

        try {
            long id_from = Long.parseLong(this.getIDFromR.getText());
            long id_to = Long.parseLong(this.getIDToR.getText());
            if (repoPrietenie.findOne(new Tuple<>(id_from, id_to)).isPresent())
                throw new Exception("Exista deja prietenia!");
            if (repoRequest.findOne(new Tuple<>(id_from, id_to)).isPresent() &&
                    Objects.equals(repoRequest.findOne(new Tuple<>(id_from, id_to)).get().getStatus(), Status.rejected))
                service.updateRequest(repoRequest.findOne(new Tuple<>(id_from, id_to)).get(), Status.pending);
            else
                service.addRequest(id_from, id_to);
            initModelRequest();

        } catch (Exception e) {
            System.out.println(e.getMessage());
            showErrorPopup(e.getMessage());
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
    private void accepta(ActionEvent actionEvent) {
        FriendRequest selected = requestTableView.getSelectionModel().getSelectedItem();
        if (selected != null && Objects.equals(selected.getStatus(), Status.pending)) {
            service.updateRequest(selected, Status.approved);
            service.addFriendship(selected.getIdfrom(), selected.getIdto(), selected.getData());
            initModelRequest();
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
    private void afisareConversatii(ActionEvent actionEvent) {
        try {
            long id_from = Long.parseLong(this.getIDFrom.getText());
            long id_to = Long.parseLong(this.getIDTo.getText());

            String str = service.conversation(id_from, id_to).stream()
                    .map(tup -> tup.getFrom().getLastName() + " " + tup.getFrom().getFirstName() + ": " +
                            tup.getMessage() + "\nTrimis la: " +
                            tup.getData().format(DateTimeFormatter.ofLocalizedTime(FormatStyle.MEDIUM)) + '\n')
                    .collect(Collectors.joining("\n"));
            getIDFrom.clear();
            getIDTo.clear();
            openSecondaryWindow(str);
        } catch (Exception e) {
            System.out.println(e.getMessage());
            showErrorPopup(e.getMessage());
        }

    }

    @FXML
    public void updateUser(ActionEvent actionEvent) {
        try {
            long id = Long.parseLong(this.getID.getText());
            String nume = this.getNume.getText();
            if (nume.isEmpty()) throw new Exception("Nume null!");
            String prenume = this.getPrenume.getText();
            if (prenume.isEmpty()) throw new Exception("Prenume null!");
            if (repoUtilizator.findOne(id).isEmpty()) throw new Exception("Nu exista utilizatorul!");
            service.updateUtilizator(id, prenume, nume);

            getID.clear();
            getNume.clear();
            getPrenume.clear();

            initModel();
        } catch (Exception e) {
            System.out.println(e.getMessage());
            showErrorPopup(e.getMessage());
        }
    }

    @FXML
    private void sterge(ActionEvent actionEvent) {
        Utilizator selectedUser = userTableView.getSelectionModel().getSelectedItem();
        if (selectedUser != null) {
            repoUtilizator.delete(selectedUser.getId());
            initModel();
        } else {
            MessageAlert.showErrorMessage(null, "Nu este selectat nici un utilizator!");
        }

    }

    @FXML
    private void afisare(ActionEvent actionEvent) {
        initModel();
    }

    @FXML
    private void nPrieteni(ActionEvent actionEvent) {
        try {
            //string.clear();
            int n = Integer.parseInt(this.getN.getText());
            List<Tuple<Utilizator, Integer>> l = service.getUsersFriends(n);
            String str = l.stream()
                    .map(tup -> tup.getLeft().getFirstName() + ": " + tup.getRight() + " prieteni")
                    .collect(Collectors.joining("\n"));
            openSecondaryWindow(str);
        } catch (Exception e) {
            System.out.println(e.getMessage());
            showErrorPopup(e.getMessage());
        }

    }

    @FXML
    private void utilizatoriLuna(ActionEvent actionEvent) {
        try {
            int luna = Integer.parseInt(this.getLuna.getText());
            int n = Integer.parseInt(this.getIDLuna.getText());
            List<Tuple<Optional<Utilizator>, Prietenie>> lista = service.getFriendshipsFromMonth(n, luna);
            String str = lista.stream()
                    .map(tup -> tup.getLeft().get().getFirstName() + " " + tup.getLeft().get().getLastName() + " " + tup.getRight().getDate())
                    .collect(Collectors.joining("\n"));
            openSecondaryWindow(str);
        } catch (Exception e) {
            System.out.println(e.getMessage());
            showErrorPopup(e.getMessage());
        }

    }

    @FXML
    public void utlizatoriString(ActionEvent actionEvent) {
        try {
            String s = this.getStr.getText();
            String str = service.getUsersString(s).stream()
                    .map(tup -> tup.getFirstName() + " " + tup.getLastName())
                    .collect(Collectors.joining("\n"));
            openSecondaryWindow(str);
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


}
