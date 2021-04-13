package model.statement;

import exceptions.MyException;
import model.PrgState;
import model.adt.IDict;
import model.adt.IStack;
import model.expression.Exp;
import model.type.BoolType;
import model.value.BoolValue;
import model.value.IValue;

public class IfStmt implements IStmt {
    private Exp exp;
    private IStmt then_stmt, else_stmt;

    public IfStmt(Exp exp, IStmt then_stmt, IStmt else_stmt) {
        this.exp = exp;
        this.then_stmt = then_stmt;
        this.else_stmt = else_stmt;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        IStack<IStmt> exeStack = state.getExeStack();
        IDict<String, IValue> symTable = state.getSymTable();

        IValue val = exp.evaluate(symTable);
        if (val.getType().equals(new BoolType())) {
            BoolValue b = (BoolValue)val;
            boolean n = b.getValue();

            if(n)
                exeStack.push(then_stmt);
            else
                exeStack.push(else_stmt);
        }
        else
            throw new MyException("Conditional expression is not a boolean!");
        return state;
    }

    @Override
    public String toString() {
        return "(IF(" + exp.toString() + ") THEN(" + then_stmt.toString() +
                ") ELSE(" + else_stmt.toString()+"))";
    }

    public Exp getExp() { return exp; }
    public IStmt getThen_stmt() { return then_stmt; }
    public IStmt getElse_stmt() { return else_stmt; }
}
