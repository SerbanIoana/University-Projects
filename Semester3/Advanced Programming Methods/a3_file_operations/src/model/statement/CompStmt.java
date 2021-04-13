package model.statement;

import exceptions.MyException;
import model.PrgState;
import model.adt.IStack;

public class CompStmt implements IStmt {
    private IStmt first;
    private IStmt second;

    public CompStmt(IStmt first, IStmt second) {
        this.first = first;
        this.second = second;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        IStack<IStmt> exeStack = state.getExeStack();
        exeStack.push(second);
        exeStack.push(first);
        return state;
    }

    @Override
    public String toString() {
        return "(" + first.toString() + "; " + second.toString() + ")";
    }

    public IStmt getFirst() { return first; }
    public IStmt getSecond() { return second; }
}
