package model.type;

import model.value.BoolValue;
import model.value.IValue;

public class BoolType implements IType {

    public boolean equals(Object some_object){ return some_object instanceof BoolType; }
    public String toString(){ return "bool"; }

    @Override
    public IValue defaultValue() {
        return new BoolValue(false);
    }
}
