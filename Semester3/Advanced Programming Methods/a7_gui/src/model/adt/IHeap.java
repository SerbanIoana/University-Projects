package model.adt;

import java.util.HashMap;
import java.util.Map;
import java.util.Stack;

public interface IHeap<T> {
    public void add(T value);
    public void update(int key, T value);
    public void remove(int key);
    public T lookup(Integer address);
    public boolean isDefined(int key);
    public T get(int key);
    public void specificAdd(Integer address, T value);
    public HashMap<Integer, T> getContent();
    public void setContent(Map<Integer, T> newContent);
    public int getFreeLocation();
    public String toString();
}
