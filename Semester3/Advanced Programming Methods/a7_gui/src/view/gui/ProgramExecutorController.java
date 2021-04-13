package view.gui;

import controller.Controller;
import exceptions.MyException;
import javafx.collections.FXCollections;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import model.PrgState;
import model.adt.*;
import model.statement.IStmt;
import model.value.IValue;

import java.io.BufferedReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class ProgramExecutorController {

    private PrgState parentPrgState;
    private Controller controller;

    @FXML
    private TextField prgStatesTextField;

    @FXML
    private ListView<String> prgStateIdsListView;

    @FXML
    private ListView<String> exeStackListView;

    @FXML
    private ListView<String> outListView;

    @FXML
    private TableView<SymbolTableViewEntry> symbolTableView;

    @FXML
    private TableColumn<SymbolTableViewEntry, String> symbolTableVarName;

    @FXML
    private TableColumn<SymbolTableViewEntry, String> symbolTableValue;

    @FXML
    private TableView<HeapTableViewEntry> heapTableView;

    @FXML
    private TableColumn<HeapTableViewEntry, String> heapTableAddress;

    @FXML
    private TableColumn<HeapTableViewEntry, String> heapTableValue;

    @FXML
    private ListView<String> fileTableListView;

    @FXML
    private Button runOneStepButton;


    @FXML
    public void initialize() {
        prgStateIdsListView.getSelectionModel().setSelectionMode(SelectionMode.SINGLE);

        symbolTableVarName.setCellValueFactory(new PropertyValueFactory<SymbolTableViewEntry, String>("name"));
        symbolTableValue.setCellValueFactory(new PropertyValueFactory<SymbolTableViewEntry, String>("val"));

        heapTableAddress.setCellValueFactory(new PropertyValueFactory<HeapTableViewEntry, String>("address"));
        heapTableValue.setCellValueFactory(new PropertyValueFactory<HeapTableViewEntry, String>("val"));

        this.parentPrgState = null;
    }

    public void setController(Controller newController) {
        this.controller = newController;

        try {
            populateAll();
        }
        catch (MyException e) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Runtime Error");
            alert.setContentText("Error: " + e.getMessage());
            alert.showAndWait();
        }
    }

    private void populateAll() {
        List<PrgState> prgStatesList = this.controller.getPrgStatesList();
        PrgState currentPrgState;
        prgStatesTextField.setText(String.valueOf(prgStatesList.size()));

        if (prgStatesList.size() == 0) {
            if (parentPrgState == null) {
                throw new MyException("No program state left!");
            }
            else {
                currentPrgState = parentPrgState;
                parentPrgState = null;
            }
        }
        else {
            currentPrgState = prgStatesList.get(0);
            parentPrgState = prgStatesList.get(0);
        }

        try {
            prgStateIdsListView.getSelectionModel().selectIndices(0);
            populatePrgStateIdsListView(prgStatesList);
            populateExeStackListView(currentPrgState);
            populateOutListView(currentPrgState);
            populateSymbolTableView(currentPrgState);
            populateHeapTableView(currentPrgState);
            populateFileTableListView(currentPrgState);
        } catch (MyException e){
            System.out.println(e.getMessage());

            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Runtime Error");
            alert.setContentText("Error: " + e.getMessage());
            alert.showAndWait();
        }
    }

    private void populatePrgStateIdsListView(List<PrgState> prgStatesList){
        ArrayList<String> prgStatesIdsList = new ArrayList<>();
        for (PrgState prgState: prgStatesList){
            String prgStateId = String.valueOf(prgState.getId());
            prgStatesIdsList.add(prgStateId);
        }
        prgStateIdsListView.setItems(FXCollections.observableArrayList(prgStatesIdsList));
    }

    private void populateExeStackListView(PrgState currentPrgState) {
        IStack<IStmt> exeStack = currentPrgState.getExeStack();
        List<String> exeStackList = new ArrayList<>();

        for(IStmt stmt : exeStack.getStack())
            exeStackList.add(stmt.toString());

        Collections.reverse(exeStackList);
        exeStackListView.setItems(FXCollections.observableArrayList(exeStackList));
    }

    private void populateOutListView(PrgState currentPrgState) {
        IList<IValue> out = currentPrgState.getOut();
        List<String> outList = new ArrayList<>();

        for(IValue val : out.getList())
            outList.add(val.toString());

        outListView.setItems(FXCollections.observableArrayList(outList));
    }

    private void populateSymbolTableView(PrgState currentPrgState) {
        IDict<String, IValue> symTable = currentPrgState.getSymTable();
        ArrayList<SymbolTableViewEntry> symTableEntries = new ArrayList<>();

        for(String name : symTable.getDictionary().keySet()){
            IValue val = symTable.getDictionary().get(name);
            SymbolTableViewEntry entry = new SymbolTableViewEntry(name, val);
            symTableEntries.add(entry);
        }
        symbolTableView.setItems(FXCollections.observableArrayList(symTableEntries));
    }

    private void populateHeapTableView(PrgState currentPrgState) {
        IHeap<IValue> heapTable = currentPrgState.getHeapTable();
        ArrayList<HeapTableViewEntry> heapTableEntries = new ArrayList<>();

        for(Integer address : heapTable.getContent().keySet()){
            IValue val = heapTable.getContent().get(address);
            HeapTableViewEntry entry = new HeapTableViewEntry(address, val);
            heapTableEntries.add(entry);
        }
        heapTableView.setItems(FXCollections.observableArrayList(heapTableEntries));
    }

    private void populateFileTableListView(PrgState currentPrgState) {
        IDict<String, BufferedReader> fileTable = currentPrgState.getFileTable();
        List<String> fileTableList = new ArrayList<>();

        for(String filename : fileTable.getDictionary().keySet()) {
            String fileString = filename + "->" + fileTable.getDictionary().get(filename).toString();
            fileTableList.add(fileString);
        }
        fileTableListView.setItems(FXCollections.observableArrayList(fileTableList));
    }

    @FXML
    private void handleChangePrgState() {
        try {
            int id = this.prgStateIdsListView.getSelectionModel().getSelectedIndex();
            PrgState prgState = this.controller.getPrgStatesList().get(id);
            populateExeStackListView(prgState);
            populateSymbolTableView(prgState);
        } catch (MyException e){
            System.out.println(e.getMessage());

            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Error Dialog");
            alert.setContentText("Error: " + e.getMessage());
            alert.showAndWait();
        }
    }

    @FXML
    private void handleRunOneStepButtonAction() {
        try{
            List<PrgState> prgStateList = controller.getPrgStatesList();

            if(prgStateList.size() > 0 || parentPrgState != null){
                this.controller.oneStep();
            }
            populateAll();
        }
        catch (MyException e) {
            System.out.println(e.getMessage());

            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Error Dialog");
            alert.setContentText("Error: " + e.getMessage());
            alert.showAndWait();
        }
    }
}
