package model.expression;

import exceptions.MyException;
import model.adt.IDict;
import model.value.IValue;

public class VarExp extends Exp {
    private String id;

    public VarExp(String id) {
        this.id = id;
    }

    @Override
    public IValue evaluate(IDict<String, IValue> symTable) throws MyException {
        return symTable.lookup(this.id);
    }

    @Override
    public String toString() {
        return id;
    }

    public String getId() { return id; }
}
