package repository;

import model.PrgState;

public interface IRepository {

    public PrgState getCurrentPrg();
    void addPrg(PrgState new_prg);
}
