package model.adt;

import java.util.ArrayList;

public class MyList<T> implements IList<T> {
    private ArrayList<T> list;

    public MyList() {
        this.list = new ArrayList<T>();
    }

    @Override
    public void add(T elem) {
        list.add(elem);
    }

//    @Override
//    public T pop() {
//        return null;
//    }

    @Override
    public String toString() {
        String str = "";
        for(T elem : list)
            str += elem.toString() + " " + '\n';
        return str;
    }

    public ArrayList<T> getList() { return list; }
}
