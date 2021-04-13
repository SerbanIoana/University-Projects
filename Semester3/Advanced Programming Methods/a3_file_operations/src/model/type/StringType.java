package model.type;

import model.value.IValue;
import model.value.StringValue;

public class StringType implements IType {

    public boolean equals(Object some_object){ return some_object instanceof StringType; }
    public String toString(){ return "string"; }

    @Override
    public IValue defaultValue() {
        return new StringValue("");
    }
}
