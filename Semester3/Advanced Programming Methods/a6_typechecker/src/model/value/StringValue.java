package model.value;

import model.type.IType;
import model.type.StringType;

public class StringValue implements IValue {
    private String value;

    public StringValue(String value) {
        this.value = value;
    }

    @Override
    public boolean equals(Object another){
        if(another instanceof StringValue)
            return ((StringValue) another).getValue().equals(this.value);
        return false;
    }

    @Override
    public IType getType() {
        return new StringType();
    }

    @Override
    public String toString() {
        return value;
    }

    public String getValue() {
        return value;
    }
}
