package view.gui;

import controller.Controller;
import exceptions.MyException;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.ListView;
import javafx.scene.control.SelectionMode;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;
import model.PrgState;
import model.adt.MyDict;
import model.adt.MyHeap;
import model.adt.MyList;
import model.adt.MyStack;
import model.expression.ArithExp;
import model.expression.RelationalExp;
import model.expression.ValueExp;
import model.expression.VarExp;
import model.expression.heap.HeapReadExp;
import model.statement.*;
import model.statement.files.CloseRFileStmt;
import model.statement.files.OpenRFileStmt;
import model.statement.files.ReadFileStmt;
import model.statement.heap.HeapAllocationStmt;
import model.statement.heap.HeapWriteStmt;
import model.type.BoolType;
import model.type.IntType;
import model.type.RefType;
import model.type.StringType;
import model.value.BoolValue;
import model.value.IntValue;
import model.value.StringValue;
import repository.IRepository;
import repository.Repository;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class ProgramSelectorController {

    @FXML
    public Button startProgramButton;
    @FXML
    private ListView<IStmt> listView;

    public void initialize() {
        try {

            this.listView.setItems(getStatementsList());
            this.listView.getSelectionModel().setSelectionMode(SelectionMode.SINGLE);
        }
        catch (Exception e){
            System.out.println(e.getMessage());
        }
    }

    @FXML
    public void handleStartProgramButtonAction(ActionEvent actionEvent) {
        IStmt selectedStmt = listView.getSelectionModel().getSelectedItem();
        int selectedIndex = listView.getSelectionModel().getSelectedIndex();

        try{
            //typecheck
            selectedStmt.typecheck(new MyDict<>());

            //create controller for selected prgState
            PrgState prgState = new PrgState(new MyHeap<>(), new MyStack<>(), new MyDict<>(), new MyDict<>(), new MyList<>(), selectedStmt);
            String filePath = "log" + (selectedIndex + 1) + ".txt";
            IRepository repository = new Repository(filePath);
            repository.addPrg(prgState);
            Controller selectedController = new Controller(repository, true);

            //load from ProgramExecutor window -> calls initialize()
            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(getClass().getResource("ProgramExecutor.fxml"));
            AnchorPane executorRoot = loader.load();

            //set controller field of ExecutorController as the selected controller -> calls setController()
            ProgramExecutorController executorController = loader.getController();
            executorController.setController(selectedController);

            //set scene for root layout
            Stage executorStage = new Stage();
            Scene executorScene = new Scene(executorRoot);
            executorStage.setScene(executorScene);
            executorStage.setTitle("Program " + (selectedIndex+1) + " Execution");
            executorStage.show();

        }
        catch (MyException e) {
            System.out.println(e.getMessage());
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Error Dialog");
            alert.setContentText(e.getMessage());
            alert.showAndWait();
        }
        catch (RuntimeException re) {
            System.out.println(re.getMessage());
            Alert alert = new Alert(Alert.AlertType.WARNING);
            alert.setTitle("Warning Dialog");
            alert.setContentText("Warning: No Program Was Selected!");
            alert.showAndWait();
        }
        catch (IOException e) {
            e.printStackTrace();
        }
    }


    public ObservableList<IStmt> getStatementsList() {
        List<IStmt> statementsList = new ArrayList<>();

        IStmt ex1 = new CompStmt(new VarDeclStmt("v",new IntType()),
                new CompStmt(new AssignStmt("v",new ValueExp(new IntValue(2))),
                        new PrintStmt(new VarExp("v"))));


        //int a; int b; a=2+3*5; b=a+1; Print(b)
        IStmt ex2 = new CompStmt(new VarDeclStmt("a", new IntType()),
                new CompStmt(new VarDeclStmt("b", new IntType()),
                        new CompStmt(new AssignStmt("a", new ArithExp(new ValueExp(new IntValue(2)),
                                new ArithExp(new ValueExp(new IntValue(3)), new ValueExp(new IntValue(5)),'*'),'+')),
                                new CompStmt(new AssignStmt("b", new ArithExp(new VarExp("a"), new ValueExp(new IntValue(1)),'+')),
                                        new PrintStmt(new VarExp("b"))))));


        //bool a; int v; a=true; (If a Then v=2 Else v=3); Print(v)
        IStmt ex3 = new CompStmt(new VarDeclStmt("a", new BoolType()),
                new CompStmt(new VarDeclStmt("v", new IntType()),
                        new CompStmt(new AssignStmt("a", new ValueExp(new BoolValue(true))),
                                new CompStmt(new IfStmt(new VarExp("a"), new AssignStmt("v", new ValueExp(new IntValue(2))),
                                        new AssignStmt("v", new ValueExp(new IntValue(3)))),
                                        new PrintStmt(new VarExp("v"))))));


        //bool b; b=3; Print(b) -> Exception
        IStmt ex4 = new CompStmt(new VarDeclStmt("b",new BoolType()),
                new CompStmt(new AssignStmt("b",new ValueExp(new IntValue(3))),
                        new PrintStmt(new VarExp("b"))));


        //string varf;
        //varf="test.in";
        //openRFile(varf);
        //int varc;
        //readFile(varf,varc);print(varc);
        //readFile(varf,varc);print(varc)
        //closeRFile(varf)
        IStmt ex5 = new CompStmt(new VarDeclStmt("varf", new StringType()),
                new CompStmt(new AssignStmt("varf", new ValueExp(new StringValue("test.in"))),
                        new CompStmt(new OpenRFileStmt(new VarExp("varf")),
                                new CompStmt(new VarDeclStmt("varc", new IntType()),
                                        new CompStmt(new ReadFileStmt(new VarExp("varf"), "varc"),
                                                new CompStmt(new PrintStmt(new VarExp("varc")),
                                                        new CompStmt(new ReadFileStmt(new VarExp("varf"), "varc"),
                                                                new CompStmt(new PrintStmt(new VarExp("varc")),
                                                                        new CloseRFileStmt(new VarExp("varf"))))))))));


        //Ref int v;new(v,20);Ref Ref int a; new(a,v);print(v);print(a)
        //Heap={1->20, 2->(1,int)}, SymTable={v->(1,int), a->(2,Ref int)} and Out={(1,int),(2,Ref int)}
        IStmt exHAllocation = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(new HeapAllocationStmt("v", new ValueExp(new IntValue(20))),
                        new CompStmt( new VarDeclStmt("a",new RefType(new RefType( new IntType()))),
                                new CompStmt(new HeapAllocationStmt("a", new VarExp("v")),
                                        new CompStmt(new PrintStmt(new VarExp("v")),
                                                new PrintStmt(new VarExp("a")))))));


        //Ref int v;new(v,20);Ref Ref int a; new(a,v);print(rH(v));print(rH(rH(a))+5)
        //Heap={1->20, 2->(1,int)}, SymTable={v->(1,int), a->(2,Ref int)} and Out={20, 25}
        IStmt exHReading = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(new HeapAllocationStmt("v", new ValueExp(new IntValue(20))),
                        new CompStmt( new VarDeclStmt("a",new RefType(new RefType( new IntType()))),
                                new CompStmt(new HeapAllocationStmt("a", new VarExp("v")),
                                        new CompStmt(new PrintStmt(new HeapReadExp(new VarExp("v"))),
                                                new PrintStmt(new ArithExp(new HeapReadExp(new HeapReadExp(new VarExp("a"))),new ValueExp(new IntValue(5)),'+')))))));


        //Ref int v;new(v,20);print(rH(v)); wH(v,30);print(rH(v)+5);
        //Heap={1->30}, SymTable={v->(1,int)} and Out={20, 35}
        IStmt exHWriting = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(new HeapAllocationStmt("v", new ValueExp(new IntValue(20))),
                        new CompStmt(new PrintStmt(new HeapReadExp(new VarExp("v"))),
                                new CompStmt(new HeapWriteStmt("v", new ValueExp(new IntValue(30))),
                                        new PrintStmt(new ArithExp(new HeapReadExp(new VarExp("v")), new ValueExp(new IntValue(5)), '+'))))));


        //Ref int v;new(v,20);Ref Ref int a; new(a,v); new(v,30);print(rH(rH(a)))
        IStmt exGarbageCollector = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(new HeapAllocationStmt("v", new ValueExp(new IntValue(20))),
                        new CompStmt( new VarDeclStmt("a",new RefType(new RefType( new IntType()))),
                                new CompStmt(new HeapAllocationStmt("a", new VarExp("v")),
                                        new CompStmt(new HeapAllocationStmt("v", new ValueExp(new IntValue(30))),
                                                new PrintStmt(new HeapReadExp(new HeapReadExp(new VarExp("a")))))))));


        //int v; v=4; (while (v>0) print(v);v=v-1);print(v)
        IStmt exWhile = new CompStmt(new VarDeclStmt("v", new IntType()),
                new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(4))),
                        new CompStmt( new WhileStmt(new RelationalExp(new VarExp("v"), new ValueExp(new IntValue(0)), ">"),
                                new CompStmt(new PrintStmt(new VarExp("v")), new AssignStmt("v", new ArithExp(new VarExp("v"), new ValueExp(new IntValue(1)),'-')))),
                                new PrintStmt(new VarExp("v")))));


        //int v; Ref int a; v=10;new(a,22);
        //fork(wH(a,30);v=32;print(v);print(rH(a)));
        //print(v);print(rH(a))
        IStmt exFork = new CompStmt(new VarDeclStmt("v", new IntType()),
                new CompStmt(new VarDeclStmt("a", new RefType(new IntType())),
                        new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(10))),
                                new CompStmt(new HeapAllocationStmt("a", new ValueExp(new IntValue(22))),
                                        new CompStmt(new ForkStmt(new CompStmt(new HeapWriteStmt("a", new ValueExp(new IntValue(30))),
                                                new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(32))),
                                                        new CompStmt(new PrintStmt(new VarExp("v")), new PrintStmt(new HeapReadExp(new VarExp("a"))))))),
                                                new CompStmt(new PrintStmt(new VarExp("v")), new PrintStmt(new HeapReadExp(new VarExp("a")))))))));

        statementsList.add(ex1);
        statementsList.add(ex2);
        statementsList.add(ex3);
        statementsList.add(ex4);
        statementsList.add(ex5);
        statementsList.add(exHAllocation);
        statementsList.add(exHReading);
        statementsList.add(exHWriting);
        statementsList.add(exGarbageCollector);
        statementsList.add(exWhile);
        statementsList.add(exFork);

        return FXCollections.observableArrayList(statementsList);
    }

}
