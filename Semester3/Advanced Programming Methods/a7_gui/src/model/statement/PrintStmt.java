package model.statement;

import exceptions.MyException;
import model.PrgState;
import model.adt.IDict;
import model.adt.IHeap;
import model.adt.IList;
import model.expression.Exp;
import model.type.IType;
import model.value.IValue;

public class PrintStmt implements IStmt {
    private final Exp exp;

    public PrintStmt(Exp exp) {
        this.exp = exp;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        IList<IValue> out = state.getOut();
        IDict<String, IValue> symTable = state.getSymTable();
        IHeap<IValue> heapTable = state.getHeapTable();

        out.add(exp.evaluate(symTable, heapTable));
        return null;
    }

    @Override
    public String toString() {
        return "print("+exp.toString()+")";
    }

    @Override
    public IDict<String, IType> typecheck(IDict<String, IType> typeEnv) throws MyException {
        exp.typecheck(typeEnv);
        return typeEnv;
    }

    public Exp getExp() { return exp; }
}
