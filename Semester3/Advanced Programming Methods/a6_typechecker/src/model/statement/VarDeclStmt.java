package model.statement;

import exceptions.MyException;
import model.PrgState;
import model.adt.IDict;
import model.type.IType;
import model.value.IValue;

public class VarDeclStmt implements IStmt {
    private final String var_name;
    private final IType type;

    public VarDeclStmt(String var_name, IType type) {
        this.var_name = var_name;
        this.type = type;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        IDict<String, IValue> symTable = state.getSymTable();

        if (symTable.isDefined(this.var_name))
            throw new MyException("Variable named "+ var_name + " has already been declared!");
        else {
            IValue val = this.type.defaultValue();
            symTable.add(var_name, val);
        }
        return null;
    }

    @Override
    public String toString() {
        return type.toString() + " " + var_name;
    }

    @Override
    public IDict<String, IType> typecheck(IDict<String, IType> typeEnv) throws MyException {
        typeEnv.add(var_name,type);
        return typeEnv;
    }

    public String getVar_name() { return var_name; }
    public IType getType() { return type; }
}
