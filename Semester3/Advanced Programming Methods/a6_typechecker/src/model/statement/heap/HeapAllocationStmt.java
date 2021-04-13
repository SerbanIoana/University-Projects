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

public class HeapAllocationStmt implements IStmt {
    private final String var_name;
    private final Exp exp;

    public HeapAllocationStmt(String var_name, Exp exp) {
        this.var_name = var_name;
        this.exp = exp;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        IDict<String, IValue> symTable = state.getSymTable();
        IHeap<IValue> heapTable = state.getHeapTable();

        if (symTable.isDefined(var_name)) {
            IType var_type = symTable.lookup(var_name).getType();

            if (var_type instanceof RefType) {
                RefType varRef_type = (RefType) var_type;
                IValue val = this.exp.evaluate(symTable, heapTable);

                if (val.getType().equals(varRef_type.getInner())) {
                    int new_address = heapTable.getFreeLocation();
                    heapTable.specificAdd(new_address, val);
                    symTable.update(var_name, new RefValue(new_address, val.getType()));
                } else
                    throw new MyException("The types aren't the same!");
            } else
                throw new MyException("Type of variable " + var_name + " isn't ReferenceType!");
        } else
            throw new MyException("The used variable " + var_name + " was not declared before!");

        return null;
    }

    @Override
    public String toString() {
        return "new(" + this.var_name + ", " + this.exp.toString() + ")";
    }

    @Override
    public IDict<String, IType> typecheck(IDict<String, IType> typeEnv) throws MyException {
        IType var_type = typeEnv.lookup(var_name);
        IType exp_type = exp.typecheck(typeEnv);

        if (var_type.equals(new RefType(exp_type)))
            return typeEnv;
        else
            throw new MyException("Typecheck error: HeapAllocationStmt variable and expression have different types!");
    }

}
