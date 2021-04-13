package model.adt;

import javafx.beans.property.SimpleStringProperty;
import model.value.IValue;

public class HeapTableViewEntry {
    private final SimpleStringProperty address;
    private final SimpleStringProperty val;

    public HeapTableViewEntry(Integer address, IValue value) {
        this.address = new SimpleStringProperty(address.toString());
        this.val = new SimpleStringProperty(value.toString());
    }

    public String getAddress() {
        return this.address.get();
    }
    public String getVal() {
        return this.val.get();
    }
}
