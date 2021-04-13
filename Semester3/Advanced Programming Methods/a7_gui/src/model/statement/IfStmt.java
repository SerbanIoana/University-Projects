package model.statement;

import exceptions.MyException;
import model.PrgState;
import model.adt.IDict;
import model.adt.IHeap;
import model.adt.IStack;
import model.expression.Exp;
import model.type.BoolType;
import model.type.IType;
import model.value.BoolValue;
import model.value.IValue;

public class IfStmt implements IStmt {
    private final Exp exp;
    private final IStmt then_stmt, else_stmt;

    public IfStmt(Exp exp, IStmt then_stmt, IStmt else_stmt) {
        this.exp = exp;
        this.then_stmt = then_stmt;
        this.else_stmt = else_stmt;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        IStack<IStmt> exeStack = state.getExeStack();
        IDict<String, IValue> symTable = state.getSymTable();
        IHeap<IValue> heapTable = state.getHeapTable();

        IValue val = exp.evaluate(symTable, heapTable);
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
        return null;
    }

    @Override
    public String toString() {
        return "(IF(" + exp.toString() + ") THEN(" + then_stmt.toString() +
                ") ELSE(" + else_stmt.toString()+"))";
    }

    @Override
    public IDict<String, IType> typecheck(IDict<String, IType> typeEnv) throws MyException {
        IType exp_type = exp.typecheck(typeEnv);

        if (exp_type.equals(new BoolType())) {
            then_stmt.typecheck(typeEnv.deepCopy());
            else_stmt.typecheck(typeEnv.deepCopy());
            return typeEnv;
        }
        else
            throw new MyException("Typecheck error: IfStmt condition is not of BoolType!");
    }

    public Exp getExp() { return exp; }
    public IStmt getThen_stmt() { return then_stmt; }
    public IStmt getElse_stmt() { return else_stmt; }
}
