package model.adt;

import java.util.HashMap;
import java.util.Map;

public interface IHeap<V> {
    public void add(V value);
    public void update(int key, V value);
    public void remove(int key);
    public V lookup(Integer address);
    public boolean isDefined(int key);
    public V get(int key);
    public void specificAdd(Integer address, V value);
    public HashMap<Integer, V> getContent();
    public void setContent(Map<Integer, V> newContent);
    public int getFreeLocation();
    public String toString();
}
