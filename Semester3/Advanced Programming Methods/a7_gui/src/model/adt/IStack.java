package model.adt;

import exceptions.MyException;

import java.util.Stack;

public interface IStack<T> {

    public T pop() throws MyException;
    public void push(T elem);
    public boolean isEmpty();
    public String toString();
    public Stack<T> getStack();
}
