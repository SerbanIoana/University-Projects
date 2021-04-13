package model.adt;

import exceptions.MyException;

public interface IDict<T1,T2> {

    public void add(T1 key, T2 val);
    public void update(T1 key, T2 val);
    public T2 lookup(T1 key) throws MyException;
    public boolean isDefined(T1 key);
    public String toString();
}
