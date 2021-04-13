package model.statement.files;

import exceptions.MyException;
import model.PrgState;
import model.adt.IDict;
import model.expression.Exp;
import model.statement.IStmt;
import model.type.StringType;
import model.value.IValue;
import model.value.StringValue;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;

public class OpenRFileStmt implements IStmt {
    private Exp exp;

    public OpenRFileStmt(Exp exp){
        this.exp = exp;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        IDict<String, IValue> symTable = state.getSymTable();
        IDict<String, BufferedReader> fileTable = state.getFileTable();

        IValue val = exp.evaluate(symTable);
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
        return state;
    }

    @Override
    public String toString() {
        return "OpenRFile("+exp.toString()+")";
    }

}
