package model.expression;

import exceptions.MyException;
import model.adt.IDict;
import model.value.IValue;

public class ValueExp extends Exp {
    private IValue value;

    public ValueExp(IValue value) {
        this.value = value;
    }

    @Override
    public IValue evaluate(IDict<String, IValue> symTable) throws MyException {
        return this.value;
    }

    @Override
    public String toString() {
        return value.toString();
    }

    public IValue getValue() {
        return value;
    }
}
