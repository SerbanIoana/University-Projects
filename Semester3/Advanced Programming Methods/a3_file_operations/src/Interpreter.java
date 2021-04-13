import controller.Controller;
import model.PrgState;
import model.adt.MyDict;
import model.adt.MyList;
import model.adt.MyStack;
import model.expression.ArithExp;
import model.expression.ValueExp;
import model.expression.VarExp;
import model.statement.*;
import model.statement.files.CloseRFileStmt;
import model.statement.files.OpenRFileStmt;
import model.statement.files.ReadFileStmt;
import model.type.BoolType;
import model.type.IntType;
import model.type.StringType;
import model.value.BoolValue;
import model.value.IntValue;
import model.value.StringValue;
import repository.IRepository;
import repository.Repository;
import view.ExitCommand;
import view.RunExample;
import view.TextMenu;

public class Interpreter {
    public static void main(String[] args) {

        //int v; v=2; Print(v)
        IStmt ex1 = new CompStmt(new VarDeclStmt("v",new IntType()),
                new CompStmt(new AssignStmt("v",new ValueExp(new IntValue(2))),
                        new PrintStmt(new VarExp("v"))));

        PrgState prgState1 = new PrgState(new MyStack<>(), new MyDict<>(), new MyDict<>(), new MyList<>(), ex1);
        IRepository repo1 = new Repository("log1.txt");
        repo1.addPrg(prgState1);
        Controller controller1 = new Controller(repo1,true);


        //int a; int b; a=2+3*5; b=a+1; Print(b)
        IStmt ex2 = new CompStmt(new VarDeclStmt("a", new IntType()),
                new CompStmt(new VarDeclStmt("b", new IntType()),
                        new CompStmt(new AssignStmt("a", new ArithExp(new ValueExp(new IntValue(2)),
                                new ArithExp(new ValueExp(new IntValue(3)), new ValueExp(new IntValue(5)),'*'),'+')),
                                new CompStmt(new AssignStmt("b", new ArithExp(new VarExp("a"), new ValueExp(new IntValue(1)),'+')),
                                        new PrintStmt(new VarExp("b"))))));

        PrgState prgState2 = new PrgState(new MyStack<>(), new MyDict<>(), new MyDict<>(), new MyList<>(), ex2);
        IRepository repo2 = new Repository("log2.txt");
        repo2.addPrg(prgState2);
        Controller controller2 = new Controller(repo2,true);


        //bool a; int v; a=true; (If a Then v=2 Else v=3); Print(v)
        IStmt ex3 = new CompStmt(new VarDeclStmt("a", new BoolType()),
                new CompStmt(new VarDeclStmt("v", new IntType()),
                        new CompStmt(new AssignStmt("a", new ValueExp(new BoolValue(true))),
                                new CompStmt(new IfStmt(new VarExp("a"), new AssignStmt("v", new ValueExp(new IntValue(2))),
                                        new AssignStmt("v", new ValueExp(new IntValue(3)))),
                                        new PrintStmt(new VarExp("v"))))));

        PrgState prgState3 = new PrgState(new MyStack<>(), new MyDict<>(), new MyDict<>(), new MyList<>(), ex3);
        IRepository repo3 = new Repository("log3.txt");
        repo3.addPrg(prgState3);
        Controller controller3 = new Controller(repo3,true);


        //bool b; b=3; Print(b) -> Exception
        IStmt ex4 = new CompStmt(new VarDeclStmt("b",new BoolType()),
                new CompStmt(new AssignStmt("b",new ValueExp(new IntValue(3))),
                        new PrintStmt(new VarExp("b"))));

        PrgState prgState4 = new PrgState(new MyStack<>(), new MyDict<>(), new MyDict<>(), new MyList<>(), ex4);
        IRepository repo4 = new Repository("log4.txt");
        repo4.addPrg(prgState4);
        Controller controller4 = new Controller(repo4,true);


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

        PrgState prgState5 = new PrgState(new MyStack<>(), new MyDict<>(), new MyDict<>(), new MyList<>(), ex5);
        IRepository repo5 = new Repository("log5.txt");
        repo5.addPrg(prgState5);
        Controller controller5 = new Controller(repo5,true);


        TextMenu menu = new TextMenu();
        menu.addCommand(new ExitCommand("0","exit"));
        menu.addCommand(new RunExample("1", ex1.toString(), controller1));
        menu.addCommand(new RunExample("2", ex2.toString(), controller2));
        menu.addCommand(new RunExample("3", ex3.toString(), controller3));
        menu.addCommand(new RunExample("4", ex4.toString(), controller4));
        menu.addCommand(new RunExample("5", ex5.toString(), controller5));

        menu.show();
    }
}
