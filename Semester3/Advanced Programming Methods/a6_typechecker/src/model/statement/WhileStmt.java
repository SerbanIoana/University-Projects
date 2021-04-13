package model.statement;

import exceptions.MyException;
import model.PrgState;
import model.adt.IDict;
import model.adt.IHeap;
import model.adt.IStack;
import model.expression.Exp;
import model.type.BoolType;
import model.type.IType;
import model.value.BoolValue;
import model.value.IValue;

public class WhileStmt implements IStmt {
    private final Exp exp;
    private final IStmt stmt;

    public WhileStmt(Exp exp, IStmt stmt)
    {
        this.exp = exp;
        this.stmt = stmt;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        IStack<IStmt> exeStack = state.getExeStack();
        IDict<String, IValue> symTable = state.getSymTable();
        IHeap<IValue> heapTable = state.getHeapTable();

        IValue val = exp.evaluate(symTable, heapTable);
        if (val.getType() instanceof BoolType) {
            BoolValue boolVal = (BoolValue) val;
            if (boolVal.getValue()) {
                exeStack.push(this);
                exeStack.push(this.stmt);
            }
            return null;
        } else
            throw new MyException("Expression does not evaluate to a boolean value!");
    }

    @Override
    public String toString() {
        return "(While(" + this.exp.toString() + ") " + this.stmt.toString() + ")";
    }

    @Override
    public IDict<String, IType> typecheck(IDict<String, IType> typeEnv) throws MyException {
        IType exp_type = exp.typecheck(typeEnv);

        if (exp_type.equals(new BoolType())) {
            stmt.typecheck(typeEnv.deepCopy());
            return typeEnv;
        }
        else
            throw new MyException("Typecheck error: WhileStmt condition is not of BoolType!");

    }

}
