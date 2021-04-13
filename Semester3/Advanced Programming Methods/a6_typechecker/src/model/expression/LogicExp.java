package model.expression;

import exceptions.MyException;
import model.adt.IDict;
import model.adt.IHeap;
import model.type.BoolType;
import model.type.IType;
import model.value.BoolValue;
import model.value.IValue;

public class LogicExp extends Exp {
    private final Exp exp1;
    private final Exp exp2;
    private final String op;

    public LogicExp(Exp exp1, Exp exp2, String op) {
        this.exp1 = exp1;
        this.exp2 = exp2;
        this.op = op;
    }

    @Override
    public IValue evaluate(IDict<String, IValue> symTable, IHeap<IValue> heapTable) throws MyException {
        IValue val1, val2;

        val1 = exp1.evaluate(symTable, heapTable);
        if (val1.getType().equals(new BoolType())) {

            val2 = exp2.evaluate(symTable, heapTable);
            if (val2.getType().equals(new BoolType())) {
                BoolValue b1 = (BoolValue) val1;
                BoolValue b2 = (BoolValue) val2;

                boolean n1, n2;
                n1 = b1.getValue();
                n2 = b2.getValue();

                if (op.equals("&&"))
                    return new BoolValue(n1&&n2);
                if (op.equals("||"))
                    return new BoolValue(n1||n2);
                throw new MyException("Invalid operator!");
            } else
                throw new MyException("Second operand is not a boolean!");
        } else
            throw new MyException("First operand is not a boolean!");

    }

    @Override
    public String toString() {
        return exp1.toString() + " " + op + " " + exp2.toString();
    }

    @Override
    public IType typecheck(IDict<String, IType> typeEnv) throws MyException {
        IType type1, type2;
        type1 = exp1.typecheck(typeEnv);
        type2 = exp2.typecheck(typeEnv);

        if (type1.equals(new BoolType())) {
            if (type2.equals(new BoolType())) {
                return new BoolType();
            } else
                throw new MyException("Typecheck error: LogicExp second operand is not a boolean!");
        } else
            throw new MyException("Typecheck error: LogicExp first operand is not a boolean!");

    }

    public Exp getExp1() { return exp1; }
    public Exp getExp2() { return exp2; }
    public String getOp() { return op; }
}
