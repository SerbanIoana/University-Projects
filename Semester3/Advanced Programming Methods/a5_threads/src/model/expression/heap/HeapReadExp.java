package model.expression.heap;

import exceptions.MyException;
import model.adt.IDict;
import model.adt.IHeap;
import model.expression.Exp;
import model.type.RefType;
import model.value.IValue;
import model.value.RefValue;

public class HeapReadExp extends Exp {
    private final Exp exp;

    public HeapReadExp(Exp exp) {
        this.exp = exp;
    }

    @Override
    public IValue evaluate(IDict<String, IValue> symTable, IHeap<IValue> heapTable) throws MyException {
        IValue val = this.exp.evaluate(symTable, heapTable);

        if (val.getType() instanceof RefType) {
            RefValue ref_val = (RefValue) val;
            int address = ref_val.getAddress();

            if(heapTable.isDefined(address)) {
                return heapTable.get(address);
            } else
                throw new MyException("The address doesn't exists in the heap!");
        } else
            throw new MyException("The value of the expression is not a Reference Value!");
    }

    @Override
    public String toString() {
        return "rH(" + this.exp.toString() + ")";
    }
}
