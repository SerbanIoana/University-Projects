package model.expression;

import exceptions.MyException;
import model.adt.IDict;
import model.value.IValue;

public abstract class Exp {

    public abstract IValue evaluate(IDict<String,IValue> symTable) throws MyException;
    public abstract String toString();
}
