package model.adt;

import javafx.beans.property.SimpleStringProperty;
import model.value.IValue;

public class SymbolTableViewEntry {
    private final SimpleStringProperty name;
    private final SimpleStringProperty val;

    public SymbolTableViewEntry(String var_name, IValue value) {
        this.name = new SimpleStringProperty(var_name);
        this.val = new SimpleStringProperty(value.toString());
    }

    public String getName() {
        return this.name.get();
    }
    public String getVal() {
        return this.val.get();
    }
}
