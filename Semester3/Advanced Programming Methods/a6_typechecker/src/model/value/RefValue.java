package model.value;

import model.type.IType;
import model.type.RefType;

public class RefValue implements IValue {

    private int address;
    private IType locationType;

    public RefValue(int address, IType locationType) {
        this.address = address;
        this.locationType = locationType;
    }

    @Override
    public boolean equals(Object another){
        if(another instanceof RefValue)
            return ((RefValue) another).getAddress() == this.address;
        return false;
    }

    @Override
    public IType getType() {
        return new RefType(locationType);
    }

    @Override
    public String toString() {
        return "(" + address + ", " + locationType.toString() + ")";
    }

    public int getAddress() {
        return this.address;
    }

    public  IType getLocationType() {
        return this.locationType;
    }
}
