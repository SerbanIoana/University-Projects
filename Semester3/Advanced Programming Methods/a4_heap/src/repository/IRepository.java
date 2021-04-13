package repository;

import exceptions.MyException;
import model.PrgState;

public interface IRepository {

    public PrgState getCurrentPrg();
    void addPrg(PrgState new_prg);
    void logPrgStateExec() throws MyException;
}
