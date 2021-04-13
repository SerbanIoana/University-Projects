package model;

import model.adt.IDict;
import model.adt.IHeap;
import model.adt.IList;
import model.adt.IStack;
import model.statement.IStmt;
import model.value.IValue;

import java.io.BufferedReader;

public class PrgState {
    private IHeap<IValue> heapTable;
    private IStack<IStmt> exeStack;
    private IDict<String, IValue> symTable;
    private IDict<String, BufferedReader> fileTable;
    private IList<IValue> out;
    private IStmt originalProgram;

    public PrgState(IHeap<IValue> heapTable, IStack<IStmt> exeStack, IDict<String, IValue> symTable, IDict<String, BufferedReader> fileTable, IList<IValue> out, IStmt originalProgram) {
        this.heapTable = heapTable;
        this.exeStack = exeStack;
        this.symTable = symTable;
        this.fileTable = fileTable;
        this.out = out;
        this.originalProgram = originalProgram;
        this.exeStack.push(originalProgram);
    }

    @Override
    public String toString() {
        return "Heap:\n" + heapTable.toString() +
                "\nExeStack:\n" + exeStack.toString() +
                "\nSymbol Table:\n" + symTable.toString() +
                "\nFile Table:\n" + fileTable.toString() +
                "\nOutput:\n" + out.toString();
    }

    public IHeap<IValue> getHeapTable() { return heapTable; }
    public void setHeapTable(IHeap<IValue> heapTable) { this.heapTable = heapTable; }

    public IStack<IStmt> getExeStack() { return exeStack; }
    public void setExeStack(IStack<IStmt> exeStack) { this.exeStack = exeStack; }

    public IDict<String, IValue> getSymTable() { return symTable; }
    public void setSymTable(IDict<String, IValue> symTable) { this.symTable = symTable; }

    public IDict<String, BufferedReader> getFileTable() { return fileTable; }
    public void setFileTable(IDict<String, BufferedReader> fileTable) { this.fileTable = fileTable; }

    public IList<IValue> getOut() { return out; }
    public void setOut(IList<IValue> out) { this.out = out; }

    public IStmt getOriginalProgram() { return originalProgram; }
    public void setOriginalProgram(IStmt originalProgram) { this.originalProgram = originalProgram; }
}
