package model.value;

import model.type.IType;

public interface IValue {

    public boolean equals(Object another);
    public IType getType();
    public String toString();
}
