package model.statement;

import exceptions.MyException;
import model.PrgState;
import model.adt.IDict;
import model.adt.IHeap;
import model.adt.IStack;
import model.expression.Exp;
import model.type.BoolType;
import model.value.BoolValue;
import model.value.IValue;

public class WhileStmt implements IStmt {
    private Exp exp;
    private IStmt stmt;

    public WhileStmt(Exp exp, IStmt stmt)
    {
        this.exp = exp;
        this.stmt = stmt;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        IStack<IStmt> exeStack = state.getExeStack();
        IDict<String, IValue> symTable = state.getSymTable();
        IHeap<IValue> heapTable = state.getHeapTable();

        IValue val = exp.evaluate(symTable, heapTable);
        if (val.getType() instanceof BoolType) {
            BoolValue boolVal = (BoolValue) val;
            if (boolVal.getValue()) {
                exeStack.push(this);
                exeStack.push(this.stmt);
            }
            return state;
        } else
            throw new MyException("Expression does not evaluate to a boolean value!");
    }

    @Override
    public String toString() {
        return this.exp.toString() + " " + this.stmt.toString();
    }

}
