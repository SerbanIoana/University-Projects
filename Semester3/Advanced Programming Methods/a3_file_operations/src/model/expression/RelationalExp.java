package model.expression;

import exceptions.MyException;
import model.adt.IDict;
import model.type.IntType;
import model.value.BoolValue;
import model.value.IValue;
import model.value.IntValue;

public class RelationalExp extends Exp {
    private final Exp exp1;
    private final Exp exp2;
    private final String op;

    public RelationalExp(Exp exp1, Exp exp2, String op) {
        this.exp1 = exp1;
        this.exp2 = exp2;
        this.op = op;
    }

    @Override
    public IValue evaluate(IDict<String, IValue> symTable) throws MyException {
        IValue val1, val2;

        val1 = exp1.evaluate(symTable);
        if (val1.getType().equals(new IntType())) {

            val2 = exp2.evaluate(symTable);
            if (val2.getType().equals(new IntType())) {
                IntValue i1 = (IntValue) val1;
                IntValue i2 = (IntValue) val2;

                int n1, n2;
                n1 = i1.getValue();
                n2 = i2.getValue();

                if (op.equals("=="))
                    return new BoolValue(n1==n2);
                if (op.equals("!="))
                    return new BoolValue(n1!=n2);
                if (op.equals("<"))
                    return new BoolValue(n1<n2);
                if (op.equals("<="))
                    return new BoolValue(n1<=n2);
                if (op.equals(">"))
                    return new BoolValue(n1>n2);
                if (op.equals(">="))
                    return new BoolValue(n1>=n2);
                throw new MyException("Invalid operator!");
            } else
                throw new MyException("Second operand is not an int!");
        } else
            throw new MyException("First operand is not an int!");
    }

    @Override
    public String toString() {
        return exp1.toString() + op + exp2.toString();
    }

    public Exp getExp1() { return exp1; }
    public Exp getExp2() { return exp2; }
    public String getOp() { return op; }
}
