package model;

import model.adt.IDict;
import model.adt.IList;
import model.adt.IStack;
import model.statement.IStmt;
import model.value.IValue;

public class PrgState {
    private IStack<IStmt> exeStack;
    private IDict<String, IValue> symTable;
    private IList<IValue> out;
    private IStmt originalProgram;

    public PrgState(IStack<IStmt> exeStack, IDict<String, IValue> symTable, IList<IValue> out, IStmt originalProgram) {
        this.exeStack = exeStack;
        this.symTable = symTable;
        this.out = out;
        this.originalProgram = originalProgram;
        this.exeStack.push(originalProgram);
    }

    @Override
    public String toString() {
        return "ExeStack:\n" + exeStack.toString() +
                "\nSymbol Table:\n" + symTable.toString() +
                "\nOutput:\n" + out.toString();
    }

    public IStack<IStmt> getExeStack() { return exeStack; }
    public void setExeStack(IStack<IStmt> exeStack) { this.exeStack = exeStack; }

    public IDict<String, IValue> getSymTable() { return symTable; }
    public void setSymTable(IDict<String, IValue> symTable) { this.symTable = symTable; }

    public IList<IValue> getOut() { return out; }
    public void setOut(IList<IValue> out) { this.out = out; }

    public IStmt getOriginalProgram() { return originalProgram; }
    public void setOriginalProgram(IStmt originalProgram) { this.originalProgram = originalProgram; }
}
