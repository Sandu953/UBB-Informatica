module cs.map.lab7 {
    requires javafx.controls;
    requires javafx.fxml;
    requires java.sql;


    opens cs.map.lab7 to javafx.fxml;
    exports cs.map.lab7;
    exports cs.map.lab7.controller;
    exports cs.map.lab7.domain;
    exports cs.map.lab7.repository;
    exports cs.map.lab7.service;
    opens cs.map.lab7.controller to javafx.fxml;
    opens cs.map.lab7.domain to javafx.base;
}