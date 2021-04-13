package model.type;

public class IntType implements IType {

    public boolean equals(Object some_object){ return some_object instanceof IntType; }
    public String toString(){ return "int"; }
}
