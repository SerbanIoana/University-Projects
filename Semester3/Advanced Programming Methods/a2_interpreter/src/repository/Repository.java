package repository;

import model.PrgState;
import model.adt.MyList;

import java.util.ArrayList;

public class Repository implements IRepository {
    private ArrayList<PrgState> programs_list;
    private int current_index;

    public Repository() {
        this.programs_list = new ArrayList<PrgState>();
        this.current_index = 0;
    }

    @Override
    public PrgState getCurrentPrg() {
        return programs_list.get(current_index);
    }

    @Override
    public void addPrg(PrgState new_prg) {
        this.programs_list.add(new_prg);
    }

    public ArrayList<PrgState> getPrograms_list() { return programs_list; }
}
