package model.type;

import model.value.IValue;
import model.value.IntValue;

public class IntType implements IType {

    public boolean equals(Object some_object){ return some_object instanceof IntType; }
    public String toString(){ return "int"; }

    @Override
    public IValue defaultValue() {
        return new IntValue(0);
    }
}
