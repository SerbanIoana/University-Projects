package controller;

import exceptions.MyException;
import model.PrgState;
import model.adt.IStack;
import model.statement.IStmt;
import repository.IRepository;
import repository.Repository;

public class Controller {
    private IRepository repo;
    private boolean display_flag;

    public Controller(IRepository repo, boolean display_flag) {
        this.repo = repo;
        this.display_flag = display_flag;
    }

    public PrgState oneStep(PrgState state) throws MyException {
        IStack<IStmt> exeStack = state.getExeStack();
        if(exeStack.isEmpty())
            throw new MyException("Program state execution stack is empty!");
        IStmt current_stmt = exeStack.pop();
        return current_stmt.execute(state);
    }

    public void allStep(){
        PrgState prg_state = repo.getCurrentPrg();
        System.out.println("--------INITIAL STATE--------");
        System.out.println(prg_state);

        while (!prg_state.getExeStack().isEmpty()){
            oneStep(prg_state);
            if(display_flag){
                System.out.println("--------NEXT STATE--------");
                System.out.println(prg_state);
            }
        }

        if(!display_flag)
            System.out.println(this.repo.getCurrentPrg().getOut().toString());

        ((Repository) repo).getPrograms_list().clear();
    }

    public void addNewPrg(PrgState new_prg){
        this.repo.addPrg(new_prg);
    }

    public IRepository getRepo() { return repo; }
}
