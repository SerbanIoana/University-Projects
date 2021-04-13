package model.statement.files;

import exceptions.MyException;
import model.PrgState;
import model.adt.IDict;
import model.adt.IHeap;
import model.expression.Exp;
import model.statement.IStmt;
import model.type.StringType;
import model.value.IValue;
import model.value.StringValue;

import java.io.BufferedReader;
import java.io.IOException;

public class CloseRFileStmt implements IStmt {
    private Exp exp;

    public CloseRFileStmt(Exp exp){
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
            String file_name = (String) str.getValue();

            if (fileTable.isDefined(file_name))
            {
                BufferedReader file_descriptor = fileTable.lookup(file_name);
                try
                {
                    file_descriptor.close();
                    fileTable.delete(file_name);
                }
                catch (IOException e) {
                    throw new MyException(e.getMessage());
                }
            }
            else
                throw new MyException("File named "+ file_name + " doesn't exist!");
        }
        else
            throw new MyException("Type of the expression is not string!");

        return state;
    }

    @Override
    public String toString() {
        return "CloseRFile("+exp.toString()+")";
    }
}
