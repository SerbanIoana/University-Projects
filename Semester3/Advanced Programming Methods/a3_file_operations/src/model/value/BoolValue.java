package model.value;

import model.type.BoolType;
import model.type.IType;

public class BoolValue implements IValue {
    private boolean value;

    public BoolValue(boolean value) {
        this.value = value;
    }

    @Override
    public boolean equals(Object another){
        if(another instanceof BoolValue)
            return ((BoolValue) another).getValue() == this.value;
        return false;
    }

    @Override
    public IType getType() {
        return new BoolType();
    }

    @Override
    public String toString() {
        return "" + value;
    }

    public boolean getValue() {
        return value;
    }
}
