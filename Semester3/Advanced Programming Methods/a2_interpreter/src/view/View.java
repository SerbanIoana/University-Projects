package view;

import controller.Controller;
import exceptions.MyException;
import model.PrgState;
import model.adt.*;
import model.expression.ArithExp;
import model.expression.ValueExp;
import model.expression.VarExp;
import model.statement.*;
import model.type.BoolType;
import model.type.IntType;
import model.value.BoolValue;
import model.value.IValue;
import model.value.IntValue;

import java.util.Scanner;

public class View {
    private Controller controller;

    public View(Controller controller) {
        this.controller = controller;
    }

    public void printMenu(){
        System.out.println("\nChoose from the options below:\n");
        System.out.println("1. int v; v=2; Print(v)");
        System.out.println("2. int a; int b; a=2+3*5; b=a+1; Print(b)");
        System.out.println("3. bool a; int v; a=true; (If a Then v=2 Else v=3); Print(v)");
        System.out.println("0. EXIT");
    }

    //int v; v=2; Print(v)
    public static IStmt ex1 = new CompStmt(new VarDeclStmt("v",new IntType()),
            new CompStmt(new AssignStmt("v",new ValueExp(new IntValue(2))),
                    new PrintStmt(new VarExp("v"))));

    //int a; int b; a=2+3*5; b=a+1; Print(b)
    public static IStmt ex2 = new CompStmt(new VarDeclStmt("a", new IntType()),
            new CompStmt(new VarDeclStmt("b", new IntType()),
                    new CompStmt(new AssignStmt("a", new ArithExp(new ValueExp(new IntValue(2)),
                            new ArithExp(new ValueExp(new IntValue(3)), new ValueExp(new IntValue(5)),'*'),'+')),
                            new CompStmt(new AssignStmt("b", new ArithExp(new VarExp("a"), new ValueExp(new IntValue(1)),'+')),
                                    new PrintStmt(new VarExp("b"))))));

    //bool a; int v; a=true; (If a Then v=2 Else v=3); Print(v)
    public static IStmt ex3 = new CompStmt(new VarDeclStmt("a", new BoolType()),
            new CompStmt(new VarDeclStmt("v", new IntType()),
                    new CompStmt(new AssignStmt("a", new ValueExp(new BoolValue(true))),
                            new CompStmt(new IfStmt(new VarExp("a"), new AssignStmt("v", new ValueExp(new IntValue(2))),
                                    new AssignStmt("v", new ValueExp(new IntValue(3)))),
                                    new PrintStmt(new VarExp("v"))))));

    //bool b; b=3; Print(b) -> Exception
    public static IStmt ex4 = new CompStmt(new VarDeclStmt("b",new BoolType()),
            new CompStmt(new AssignStmt("b",new ValueExp(new IntValue(3))),
                    new PrintStmt(new VarExp("b"))));


    public PrgState init(IStmt original_program){
        IStack<IStmt> exeStack = new MyStack<>();
        IDict<String, IValue> symTable = new MyDict<>();
        IList<IValue> out = new MyList<>();
        PrgState prg_state = new PrgState(exeStack,symTable,out,original_program);
        return prg_state;
    }

    public void run(){
        //startupStatements();
        Scanner scanner = new Scanner(System.in);

        while(true){

            this.printMenu();
            System.out.println("Insert option >>> ");

            try{
                int command = scanner.nextInt();
                PrgState program = null;

                switch (command) {
                    case 0:
                        System.exit(0);
                    case 1:
                        program = init(ex1);
                        break;
                    case 2:
                        program = init(ex2);
                        break;
                    case 3:
                        program = init(ex3);
                        break;
                    case 4:
                        program = init(ex4);
                        break;
                    default:
                        break;
                }

                controller.addNewPrg(program);
                controller.allStep();
            }
            catch(MyException e) {
                System.out.println(e.getMessage());
            }
            catch(Exception e){
                System.out.println(e.getMessage());
            }
        }
    }
}

