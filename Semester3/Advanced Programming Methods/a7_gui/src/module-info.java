module a7 {
    requires javafx.graphics;
    requires javafx.fxml;
    requires javafx.controls;
    requires javafx.base;
    opens view.gui;
    opens model;
    opens model.adt;
}