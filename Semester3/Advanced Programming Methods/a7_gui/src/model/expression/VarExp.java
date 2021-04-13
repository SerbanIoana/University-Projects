package model.expression;

import exceptions.MyException;
import model.adt.IDict;
import model.adt.IHeap;
import model.type.IType;
import model.value.IValue;

public class VarExp extends Exp {
    private String id;

    public VarExp(String id) {
        this.id = id;
    }

    @Override
    public IValue evaluate(IDict<String, IValue> symTable, IHeap<IValue> heapTable) throws MyException {
        return symTable.lookup(this.id);
    }

    @Override
    public String toString() {
        return id;
    }

    @Override
    public IType typecheck(IDict<String, IType> typeEnv) throws MyException {
        return typeEnv.lookup(id);
    }

    public String getId() { return id; }
}
