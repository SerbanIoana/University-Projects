package model.statement;

import exceptions.MyException;
import model.PrgState;
import model.adt.IDict;
import model.type.BoolType;
import model.type.IType;
import model.type.IntType;
import model.value.BoolValue;
import model.value.IValue;
import model.value.IntValue;

public class VarDeclStmt implements IStmt {
    private String var_name;
    private IType type;

    public VarDeclStmt(String var_name, IType type) {
        this.var_name = var_name;
        this.type = type;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        IDict<String, IValue> symTable = state.getSymTable();

        if (symTable.isDefined(var_name))
            throw new MyException("Variable named "+ var_name + " has already been declared!");
        else {
            IValue val;

            if(type.equals(new IntType()))
                val = new IntValue(0);
            else {
                if(type.equals(new BoolType()))
                    val = new BoolValue(false);
                else
                    throw new MyException("Invalid type!");
            }
            symTable.add(var_name, val);
        }
        return state;
    }

    @Override
    public String toString() {
        return type.toString() + " " + var_name;
    }

    public String getVar_name() { return var_name; }
    public IType getType() { return type; }
}
