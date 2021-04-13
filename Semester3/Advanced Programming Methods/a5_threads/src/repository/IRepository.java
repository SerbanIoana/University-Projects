package repository;

import exceptions.MyException;
import model.PrgState;

import java.util.ArrayList;

public interface IRepository {

    public PrgState getCurrentPrg();
    void addPrg(PrgState new_prg);
    void logPrgStateExec(PrgState prgState) throws MyException;

    public ArrayList<PrgState> getPrograms_list();
    public void setPrograms_list(ArrayList<PrgState> new_programs_list);
}
