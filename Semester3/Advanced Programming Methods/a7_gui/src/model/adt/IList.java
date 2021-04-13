package model.adt;

import java.util.ArrayList;

public interface IList<T> {

    public void add(T elem);
    //public T pop();
    public String toString();
    public ArrayList<T> getList();
}
