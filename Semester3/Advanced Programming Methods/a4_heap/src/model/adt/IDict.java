package model.adt;

import exceptions.MyException;

import java.util.HashMap;

public interface IDict<T1,T2> {

    public void add(T1 key, T2 val);
    public void update(T1 key, T2 val);
    public T2 lookup(T1 key) throws MyException;
    public void delete(T1 key) throws MyException;
    public boolean isDefined(T1 key);
    public HashMap<T1,T2> getDictionary();
    public String toString();
}
