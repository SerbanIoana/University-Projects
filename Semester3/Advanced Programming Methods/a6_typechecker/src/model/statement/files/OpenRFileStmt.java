package model.statement.files;

import exceptions.MyException;
import model.PrgState;
import model.adt.IDict;
import model.adt.IHeap;
import model.expression.Exp;
import model.statement.IStmt;
import model.type.IType;
import model.type.StringType;
import model.value.IValue;
import model.value.StringValue;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;

public class OpenRFileStmt implements IStmt {
    private final Exp exp;

    public OpenRFileStmt(Exp exp){
        this.exp = exp;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        IDict<String, IValue> symTable = state.getSymTable();
        IDict<String, BufferedReader> fileTable = state.getFileTable();
        IHeap<IValue> heapTable = state.getHeapTable();

        IValue val = exp.evaluate(symTable, heapTable);
        if(val.getType().equals(new StringType()))
        {
            StringValue str = (StringValue) val;
            String name = (String) str.getValue();

            if (fileTable.isDefined(name))
                throw new MyException("File named "+ name + " has already been declared!");
            else {
                try
                {
                    BufferedReader file_descriptor = new BufferedReader(new FileReader(name));
                    fileTable.add(name, file_descriptor);
                } catch (FileNotFoundException e) {
                    throw new MyException("File named "+ name + " doesn't exist!");
                }
            }
        }
        else
            throw  new MyException("Type of the expression is not string!");
        return null;
    }

    @Override
    public String toString() {
        return "OpenRFile("+exp.toString()+")";
    }

    @Override
    public IDict<String, IType> typecheck(IDict<String, IType> typeEnv) throws MyException {
        IType exp_type = exp.typecheck(typeEnv);

        if (exp_type.equals(new StringType()))
            return typeEnv;
        else
            throw new MyException("Typecheck error: OpenRFileStmt expression is not a String!");
    }

}
