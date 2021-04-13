package model.adt;

import exceptions.MyException;

public interface IStack<T> {

    public T pop() throws MyException;
    public void push(T elem);
    public boolean isEmpty();
    public String toString();
}
