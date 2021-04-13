package model.statement;

import exceptions.MyException;
import model.PrgState;
import model.adt.IDict;
import model.adt.IHeap;
import model.expression.Exp;
import model.type.IType;
import model.value.IValue;

public class AssignStmt implements IStmt {
    private final String id;
    private final Exp exp;

    public AssignStmt(String id, Exp exp) {
        this.id = id;
        this.exp = exp;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        IDict<String, IValue> symTable = state.getSymTable();
        IHeap<IValue> heapTable = state.getHeapTable();

        if (symTable.isDefined(id)) {
            IValue val = exp.evaluate(symTable, heapTable);
            IType type_id = (symTable.lookup(id)).getType();

            if (val.getType().equals(type_id))
                symTable.update(id, val);
            else
                throw new MyException("Declared type of variable " + id + " and type of the assigned expression do not match!");
        }
        else
            throw new MyException("The used variable " + id + " was not declared before!");
        return null;
    }

    @Override
    public String toString() {
        return id + "=" + exp.toString();
    }

    @Override
    public IDict<String, IType> typecheck(IDict<String, IType> typeEnv) throws MyException {
        IType var_type = typeEnv.lookup(id);
        IType exp_type = exp.typecheck(typeEnv);

        if (var_type.equals(exp_type))
            return typeEnv;
        else
            throw new MyException("Typecheck error: AssigStmt variable and expression have different types!");
    }

    public String getId() { return id; }
    public Exp getExp() { return exp; }
}
