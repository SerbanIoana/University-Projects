import controller.Controller;
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
import view.ExitCommand;
import view.RunExample;
import view.TextMenu;

public class Interpreter {
    public static void main(String[] args) {

        //int v; v=2; Print(v)
        IStmt ex1 = new CompStmt(new VarDeclStmt("v",new IntType()),
                new CompStmt(new AssignStmt("v",new ValueExp(new IntValue(2))),
                        new PrintStmt(new VarExp("v"))));

        PrgState prgState1 = new PrgState(new MyHeap<>(), new MyStack<>(), new MyDict<>(), new MyDict<>(), new MyList<>(), ex1);
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

        PrgState prgState2 = new PrgState(new MyHeap<>(), new MyStack<>(), new MyDict<>(), new MyDict<>(), new MyList<>(), ex2);
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

        PrgState prgState3 = new PrgState(new MyHeap<>(), new MyStack<>(), new MyDict<>(), new MyDict<>(), new MyList<>(), ex3);
        IRepository repo3 = new Repository("log3.txt");
        repo3.addPrg(prgState3);
        Controller controller3 = new Controller(repo3,true);


        //bool b; b=3; Print(b) -> Exception
        IStmt ex4 = new CompStmt(new VarDeclStmt("b",new BoolType()),
                new CompStmt(new AssignStmt("b",new ValueExp(new IntValue(3))),
                        new PrintStmt(new VarExp("b"))));

        PrgState prgState4 = new PrgState(new MyHeap<>(), new MyStack<>(), new MyDict<>(), new MyDict<>(), new MyList<>(), ex4);
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

        PrgState prgState5 = new PrgState(new MyHeap<>(), new MyStack<>(), new MyDict<>(), new MyDict<>(), new MyList<>(), ex5);
        IRepository repo5 = new Repository("log5.txt");
        repo5.addPrg(prgState5);
        Controller controller5 = new Controller(repo5,true);


        //Ref int v;new(v,20);Ref Ref int a; new(a,v);print(v);print(a)
        //Heap={1->20, 2->(1,int)}, SymTable={v->(1,int), a->(2,Ref int)} and Out={(1,int),(2,Ref int)}
        IStmt exHAllocation = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(new HeapAllocationStmt("v", new ValueExp(new IntValue(20))),
                        new CompStmt( new VarDeclStmt("a",new RefType(new RefType( new IntType()))),
                                new CompStmt(new HeapAllocationStmt("a", new VarExp("v")),
                                        new CompStmt(new PrintStmt(new VarExp("v")),
                                                new PrintStmt(new VarExp("a")))))));

        PrgState prgStateHAllocation = new PrgState(new MyHeap<>(), new MyStack<>(), new MyDict<>(), new MyDict<>(), new MyList<>(), exHAllocation);
        IRepository repo6 = new Repository("log6.txt");
        repo6.addPrg(prgStateHAllocation);
        Controller  controller6 = new Controller(repo6, true);


        //Ref int v;new(v,20);Ref Ref int a; new(a,v);print(rH(v));print(rH(rH(a))+5)
        //Heap={1->20, 2->(1,int)}, SymTable={v->(1,int), a->(2,Ref int)} and Out={20, 25}
        IStmt exHReading = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(new HeapAllocationStmt("v", new ValueExp(new IntValue(20))),
                        new CompStmt( new VarDeclStmt("a",new RefType(new RefType( new IntType()))),
                                new CompStmt(new HeapAllocationStmt("a", new VarExp("v")),
                                        new CompStmt(new PrintStmt(new HeapReadExp(new VarExp("v"))),
                                                new PrintStmt(new ArithExp(new HeapReadExp(new HeapReadExp(new VarExp("a"))),new ValueExp(new IntValue(5)),'+')))))));

        PrgState prgStateHReading = new PrgState(new MyHeap<>(), new MyStack<>(), new MyDict<>(), new MyDict<>(), new MyList<>(), exHReading);
        IRepository repo7 = new Repository("log7.txt");
        repo7.addPrg(prgStateHReading);
        Controller  controller7 = new Controller(repo7, true);


        //Ref int v;new(v,20);print(rH(v)); wH(v,30);print(rH(v)+5);
        //Heap={1->30}, SymTable={v->(1,int)} and Out={20, 35}
        IStmt exHWriting = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(new HeapAllocationStmt("v", new ValueExp(new IntValue(20))),
                        new CompStmt(new PrintStmt(new HeapReadExp(new VarExp("v"))),
                                new CompStmt(new HeapWriteStmt("v", new ValueExp(new IntValue(30))),
                                        new PrintStmt(new ArithExp(new HeapReadExp(new VarExp("v")), new ValueExp(new IntValue(5)), '+'))))));

        PrgState prgStateHWriting = new PrgState(new MyHeap<>(), new MyStack<>(), new MyDict<>(), new MyDict<>(), new MyList<>(), exHWriting);
        IRepository repo8 = new Repository("log8.txt");
        repo8.addPrg(prgStateHWriting);
        Controller  controller8 = new Controller(repo8, true);


        //Ref int v;new(v,20);Ref Ref int a; new(a,v); new(v,30);print(rH(rH(a)))
        IStmt exGarbageCollector = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(new HeapAllocationStmt("v", new ValueExp(new IntValue(20))),
                        new CompStmt( new VarDeclStmt("a",new RefType(new RefType( new IntType()))),
                                new CompStmt(new HeapAllocationStmt("a", new VarExp("v")),
                                        new CompStmt(new HeapAllocationStmt("v", new ValueExp(new IntValue(30))),
                                                new PrintStmt(new HeapReadExp(new HeapReadExp(new VarExp("a")))))))));

        PrgState prgStateGarbageCollect = new PrgState(new MyHeap<>(), new MyStack<>(), new MyDict<>(), new MyDict<>(), new MyList<>(), exGarbageCollector);
        IRepository repo9 = new Repository("log9.txt");
        repo9.addPrg(prgStateGarbageCollect);
        Controller  controller9 = new Controller(repo9, true);


        //int v; v=4; (while (v>0) print(v);v=v-1);print(v)
        IStmt exWhile = new CompStmt(new VarDeclStmt("v", new IntType()),
                new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(4))),
                        new CompStmt( new WhileStmt(new RelationalExp(new VarExp("v"), new ValueExp(new IntValue(0)), ">"),
                                new CompStmt(new PrintStmt(new VarExp("v")), new AssignStmt("v", new ArithExp(new VarExp("v"), new ValueExp(new IntValue(1)),'-')))),
                                new PrintStmt(new VarExp("v")))));

        PrgState prgStateWhile = new PrgState(new MyHeap<>(), new MyStack<>(), new MyDict<>(), new MyDict<>(), new MyList<>(), exWhile);
        IRepository repo10 = new Repository("log10.txt");
        repo10.addPrg(prgStateWhile);
        Controller  controller10 = new Controller(repo10, true);


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

        PrgState prgStateFork = new PrgState(new MyHeap<>(), new MyStack<>(), new MyDict<>(), new MyDict<>(), new MyList<>(), exFork);
        IRepository repo11 = new Repository("log11.txt");
        repo11.addPrg(prgStateFork);
        Controller  controller11 = new Controller(repo11, true);


        TextMenu menu = new TextMenu();
        menu.addCommand(new ExitCommand("0","exit"));
        menu.addCommand(new RunExample("1", ex1.toString(), controller1));
        menu.addCommand(new RunExample("2", ex2.toString(), controller2));
        menu.addCommand(new RunExample("3", ex3.toString(), controller3));
        menu.addCommand(new RunExample("4", ex4.toString(), controller4));
        menu.addCommand(new RunExample("5", ex5.toString(), controller5));
        menu.addCommand(new RunExample("6", exHAllocation.toString(), controller6));
        menu.addCommand(new RunExample("7", exHReading.toString(), controller7));
        menu.addCommand(new RunExample("8", exHWriting.toString(), controller8));
        menu.addCommand(new RunExample("9", exGarbageCollector.toString(), controller9));
        menu.addCommand(new RunExample("10", exWhile.toString(), controller10));
        menu.addCommand(new RunExample("11", exFork.toString(), controller11));

        menu.show();
    }
}
