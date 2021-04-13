package model.statement.files;

import exceptions.MyException;
import model.PrgState;
import model.adt.IDict;
import model.adt.IHeap;
import model.expression.Exp;
import model.statement.IStmt;
import model.type.IType;
import model.type.IntType;
import model.type.StringType;
import model.value.IValue;
import model.value.IntValue;
import model.value.StringValue;

import java.io.BufferedReader;
import java.io.IOException;

public class ReadFileStmt implements IStmt {
    private Exp exp;
    private String var_name;

    public ReadFileStmt(Exp exp, String var_name){
        this.exp = exp;
        this.var_name = var_name;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        IDict<String, IValue> symTable = state.getSymTable();
        IDict<String, BufferedReader> fileTable = state.getFileTable();
        IHeap<IValue> heapTable = state.getHeapTable();

        if(symTable.isDefined(this.var_name))
        {
            IType type = (symTable.lookup(var_name)).getType();
            if(type.equals(new IntType()))
            {
                IValue val = exp.evaluate(symTable, heapTable);
                if(val.getType().equals(new StringType()))
                {
                    StringValue str = (StringValue) val;
                    String file_name = (String) str.getValue();

                    if (fileTable.isDefined(file_name))
                    {
                        try
                        {
                            BufferedReader file_descriptor = fileTable.lookup(file_name);
                            String line = file_descriptor.readLine();

                            if(line == null)
                                symTable.update(var_name, new IntValue(0));
                            else
                                symTable.update(var_name, new IntValue(Integer.parseInt(line)));
                        } catch (IOException e) {
                            throw new MyException(e.getMessage());
                        }
                    }
                    else
                        throw new MyException("File named "+ file_name + " doesn't exist!");
                }
                else
                    throw  new MyException("Type of the expression is not string!");
            }
            else
                throw  new MyException("Type of variable " + var_name + " is not int!");
        }
        else
            throw new MyException("Variable named " + var_name + " was not declared!");

        return null;
    }

    @Override
    public String toString() {
        return "ReadFile(" + exp.toString() + ", " + var_name + ")";
    }
}
