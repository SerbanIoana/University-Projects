package model.type;

import model.value.IValue;

public interface IType {

    public boolean equals(Object some_object);
    public String toString();
    public IValue defaultValue();
}
