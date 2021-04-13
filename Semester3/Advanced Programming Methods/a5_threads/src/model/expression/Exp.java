package model.expression;

import exceptions.MyException;
import model.adt.IDict;
import model.adt.IHeap;
import model.value.IValue;

public abstract class Exp {

    public abstract IValue evaluate(IDict<String,IValue> symTable, IHeap<IValue> heapTable) throws MyException;
    public abstract String toString();
}
