package model.statement;

import exceptions.MyException;
import model.PrgState;
import model.adt.*;
import model.type.IType;
import model.value.IValue;

import java.io.BufferedReader;

public class ForkStmt implements IStmt {
    private final IStmt stmt;

    public ForkStmt(IStmt stmt)
    {
        this.stmt = stmt;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        IHeap<IValue> heapTable = state.getHeapTable();
        IStack<IStmt> newStack = new MyStack<IStmt>();
        IDict<String, IValue> newSymTable = state.getSymTable().deepCopy();
        IDict<String, BufferedReader> fileTable = state.getFileTable();
        IList<IValue> out = state.getOut();

        return new PrgState(heapTable, newStack, newSymTable, fileTable, out, stmt);
    }

    @Override
    public String toString() {
        return "Fork(" + stmt.toString() + ")";
    }

    @Override
    public IDict<String, IType> typecheck(IDict<String, IType> typeEnv) throws MyException {
        IDict<String, IType> typeEnv1 = stmt.typecheck(typeEnv);
        return typeEnv1.deepCopy();
    }
}
