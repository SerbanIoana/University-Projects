package model.adt;

import exceptions.MyException;

import java.util.Stack;

public class MyStack<T> implements IStack<T> {
    private Stack<T> stack;

    public MyStack() {
        this.stack = new Stack<T>();
    }

    @Override
    public T pop() throws MyException {
        if(!stack.isEmpty())
            return stack.pop();
        else
            throw new MyException("Empty stack!");
    }

    @Override
    public void push(T elem) {
        stack.push(elem);
    }

    @Override
    public boolean isEmpty() {
        return stack.isEmpty();
    }

    @Override
    public String toString() {
        T elem;
        String str = "";
        Stack<T> new_stack = (Stack<T>)this.stack.clone();

        while(!new_stack.isEmpty()){
            elem = new_stack.pop();
            str += elem.toString() + "\n";
        }
        return  str;
    }

    public Stack<T> getStack() { return stack; }
}
