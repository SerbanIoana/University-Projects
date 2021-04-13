package model.expression;

import exceptions.MyException;
import model.adt.IDict;
import model.adt.IHeap;
import model.type.IType;
import model.type.IntType;
import model.value.IValue;
import model.value.IntValue;

public class ArithExp extends Exp {
    private final Exp exp1;
    private final Exp exp2;
    private final char op;

    public ArithExp(Exp exp1, Exp exp2, char op) {
        this.exp1 = exp1;
        this.exp2 = exp2;
        this.op = op;
    }

    @Override
    public IValue evaluate(IDict<String, IValue> symTable, IHeap<IValue> heapTable) throws MyException {
        IValue val1, val2;

        val1 = exp1.evaluate(symTable, heapTable);
        if (val1.getType().equals(new IntType())) {

            val2 = exp2.evaluate(symTable, heapTable);
            if (val2.getType().equals(new IntType())) {
                IntValue i1 = (IntValue)val1;
                IntValue i2 = (IntValue)val2;

                int n1, n2;
                n1= i1.getValue();
                n2 = i2.getValue();

                if (op == '+')
                    return new IntValue(n1+n2);
                if (op == '-')
                    return new IntValue(n1-n2);
                if(op == '*')
                    return new IntValue(n1*n2);
                if(op == '/'){
                    if(n2 == 0)
                        throw new MyException("Division by zero!\n");
                    return new IntValue(n1/n2);
                }
                throw new MyException("Invalid operator!");
            } else
                throw new MyException("Second operand is not an integer!");
        } else
            throw new MyException("First operand is not an integer!");
    }

    @Override
    public String toString() {
        return exp1.toString() + op + exp2.toString();
    }

    @Override
    public IType typecheck(IDict<String, IType> typeEnv) throws MyException {
        IType type1, type2;
        type1 = exp1.typecheck(typeEnv);
        type2 = exp2.typecheck(typeEnv);

        if (type1.equals(new IntType())) {
            if (type2.equals(new IntType())) {
                return new IntType();
            } else
                throw new MyException("Typecheck error: ArithExp second operand is not an integer!");
        } else
            throw new MyException("Typecheck error: ArithExp first operand is not an integer!");
    }

    public Exp getExp1() { return exp1; }
    public Exp getExp2() { return exp2; }
    public char getOp() { return op; }
}
