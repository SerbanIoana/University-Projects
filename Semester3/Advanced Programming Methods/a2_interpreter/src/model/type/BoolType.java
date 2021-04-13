package model.type;

public class BoolType implements IType {

    public boolean equals(Object some_object){ return some_object instanceof BoolType; }
    public String toString(){ return "bool"; }
}
