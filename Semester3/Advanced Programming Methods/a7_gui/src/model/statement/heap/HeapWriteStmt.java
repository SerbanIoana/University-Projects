package model.statement.heap;

import exceptions.MyException;
import model.PrgState;
import model.adt.IDict;
import model.adt.IHeap;
import model.expression.Exp;
import model.statement.IStmt;
import model.type.IType;
import model.type.RefType;
import model.value.IValue;
import model.value.RefValue;

public class HeapWriteStmt implements IStmt {
    private final String var_name;
    private final Exp exp;

    public HeapWriteStmt(String var_name, Exp exp) {
        this.var_name = var_name;
        this.exp = exp;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        IDict<String, IValue> symTable = state.getSymTable();
        IHeap<IValue> heapTable = state.getHeapTable();

        if (symTable.isDefined(var_name)) {
            IValue val = symTable.lookup(var_name);

            if (val.getType() instanceof RefType) {
                RefValue ref_val = (RefValue) val;
                int address = ref_val.getAddress();

                if(heapTable.isDefined(address)) {
                    IValue old_content = heapTable.get(address);
                    IValue new_content = this.exp.evaluate(symTable, heapTable);

                    if (new_content.getType().equals(ref_val.getLocationType())) {
                        heapTable.update(address, new_content);
                        return null;
                    } else
                        throw new MyException("Type mismatch: expression type doesn't match variable reference type!");
                } else
                    throw new MyException("The address doesn't exist in the heap!");
            } else
                throw new MyException("The type of the expression is not ReferenceType!");
        } else
            throw new MyException("The variable is not defined!");
    }

    @Override
    public String toString() {
        return "wH(" + this.var_name + ", " + this.exp.toString() + ")";
    }

    @Override
    public IDict<String, IType> typecheck(IDict<String, IType> typeEnv) throws MyException {
        IType exp_type = exp.typecheck(typeEnv);
        IType var_type = typeEnv.lookup(var_name);

        if (var_type.equals(new RefType(exp_type)))
            return typeEnv;
        throw new MyException("Typecheck error: HeapWriteStmt variable and expression have different types!");
    }

}
