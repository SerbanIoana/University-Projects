package model.value;

import model.type.IType;
import model.type.IntType;

public class IntValue implements IValue {
    private int value;

    public IntValue(int value) {
        this.value = value;
    }

    @Override
    public IType getType() {
        return new IntType();
    }

    @Override
    public String toString() {
        return "" + value;
    }

    public int getValue() {
        return value;
    }
}
