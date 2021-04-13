package model.statement;

import exceptions.MyException;
import model.PrgState;
import model.adt.IDict;
import model.type.IType;

public interface IStmt {
    public PrgState execute(PrgState state) throws MyException;
    public String toString();
    public IDict<String, IType> typecheck(IDict<String, IType> typeEnv) throws MyException;
}