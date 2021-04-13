package model.adt;

import exceptions.MyException;

import java.util.HashMap;
import java.util.Map;

public class MyDict<T1,T2> implements IDict<T1,T2>{
    private HashMap<T1, T2> dictionary;

    public MyDict() {
        this.dictionary = new HashMap<T1, T2>();
    }

    @Override
    public void add(T1 key, T2 val) {
        this.dictionary.put(key, val);
    }

    @Override
    public void update(T1 key, T2 val) {
        this.dictionary.put(key, val);
    }

    @Override
    public T2 lookup(T1 key) throws MyException {
        if(dictionary.get(key) != null)
            return dictionary.get(key);
        else
            throw new MyException("Nonexistent ID!\n");
    }

    @Override
    public boolean isDefined(T1 key) {
        return dictionary.containsKey(key);
    }

    @Override
    public String toString() {
        String str="";

        for(T1 key : dictionary.keySet())
            str += key.toString() + "=" + dictionary.get(key).toString() + "\n";

        return str;
    }

    public HashMap<T1,T2> getDictionary() { return dictionary; }
}
