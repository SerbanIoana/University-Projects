package model.statement;

import exceptions.MyException;
import model.PrgState;
import model.adt.IDict;
import model.adt.IList;
import model.expression.Exp;
import model.value.IValue;

public class PrintStmt implements IStmt {
    private Exp exp;

    public PrintStmt(Exp exp) {
        this.exp = exp;
    }


    @Override
    public PrgState execute(PrgState state) throws MyException {
        IList<IValue> out = state.getOut();
        IDict<String, IValue> symTable = state.getSymTable();
        out.add(exp.evaluate(symTable));
        return state;
    }

    @Override
    public String toString() {
        return "print("+exp.toString()+")";
    }

    public Exp getExp() { return exp; }
}
