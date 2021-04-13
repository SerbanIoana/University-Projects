package model.adt;

import exceptions.MyException;

import java.util.HashMap;
import java.util.Map;

public class MyHeap<V> implements IHeap<V> {

    private HashMap<Integer,V> heapTable;
    private int nextAddress;
    private int freeLocation;

    public MyHeap() {
        this.heapTable = new HashMap<Integer, V>();
        nextAddress = 1;
        freeLocation = 1;
    }

    @Override
    public void add(V value) {
        this.heapTable.put(freeLocation++, value);
    }

    @Override
    public void update(int key, V value) {
        this.heapTable.put(key, value);
    }

    @Override
    public void remove(int key) {
        this.heapTable.remove(key);
    }

    @Override
    public V lookup(Integer address) {
        return this.heapTable.get(address);
    }

    @Override
    public boolean isDefined(int key) {
        return heapTable.containsKey(key);
    }

    @Override
    public V get(int key) {
        return this.heapTable.get(key);
    }

    @Override
    public void specificAdd(Integer address, V value) {
        if (lookup(address) == null)
            this.heapTable.put(address, value);
        else
            throw new MyException("This address isn't free for the location!");
    }

    @Override
    public HashMap<Integer, V> getContent() {
        return this.heapTable;
    }

    @Override
    public void setContent(Map<Integer, V> newContent) {
        this.heapTable = new HashMap<Integer, V>(newContent);
    }

    @Override
    public int getFreeLocation() {
        nextAddress = freeLocation;
        freeLocation++;
        return this.nextAddress;
    }

    @Override
    public String toString() {
        String str = "";

        for (Integer key : heapTable.keySet())
            str += key.toString() + " -> " + heapTable.get(key).toString() + "\n";

        return str;
    }
}
