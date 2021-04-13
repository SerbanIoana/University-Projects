package controller;

import exceptions.MyException;
import model.PrgState;
import model.adt.IStack;
import model.statement.IStmt;
import model.value.IValue;
import model.value.RefValue;
import repository.IRepository;
import repository.Repository;

import java.util.Collection;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class Controller {
    private IRepository repo;
    private boolean display_flag;

    public Controller(IRepository repo, boolean display_flag) {
        this.repo = repo;
        this.display_flag = display_flag;
    }

    //garbage collector
    public Map<Integer, IValue> unsafeGarbageCollector(List<Integer> symTableAddr, Map<Integer,IValue> heapTable){
        return heapTable.entrySet().stream()
                .filter(e->symTableAddr.contains(e.getKey()))
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
    }

    public Map<Integer, IValue> safeGarbageCollector(List<Integer> symTableAddr, List<Integer> heapTableAddr, Map<Integer,IValue> heapTable){

        return heapTable.entrySet().stream()
                .filter(e->symTableAddr.contains(e.getKey()) ||
                        heapTableAddr.contains(e.getKey()))
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
    }

    public List<Integer> getAddressesFromSymTable(Collection<IValue> symTableValues){
        return symTableValues.stream()
                .filter(v-> v instanceof RefValue)
                .map(v-> {
                    RefValue v1 = (RefValue)v;
                    return v1.getAddress();
                })
                .collect(Collectors.toList());
    }

    public List<Integer> getAddressesFromHeapTable(Collection<IValue> heapTableValues){
        return heapTableValues.stream()
                .filter(v-> v instanceof RefValue)
                .map(v-> {
                    RefValue v1 = (RefValue)v;
                    return v1.getAddress();
                })
                .collect(Collectors.toList());
    }

    public PrgState oneStep(PrgState state) throws MyException {
        IStack<IStmt> exeStack = state.getExeStack();
        if(exeStack.isEmpty())
            throw new MyException("Program state execution stack is empty!");
        IStmt current_stmt = exeStack.pop();
        return current_stmt.execute(state);
    }

    public void allStep() {
        PrgState prg_state = repo.getCurrentPrg();
        //System.out.println("--------INITIAL STATE--------");
        //System.out.println(prg_state);
//        String log_file_path = ((Repository) this.repo).getLog_file_path();
//        PrintWriter logFile = new PrintWriter(new BufferedWriter(new FileWriter(log_file_path, true)));
        this.repo.logPrgStateExec();

        while (!prg_state.getExeStack().isEmpty()){
            oneStep(prg_state);

            List<Integer> symTableAddresses = this.getAddressesFromSymTable(prg_state.getSymTable().getDictionary().values());
            List<Integer> heapTableAddresses = this.getAddressesFromHeapTable(prg_state.getHeapTable().getContent().values());
            prg_state.getHeapTable().setContent(this.safeGarbageCollector(symTableAddresses,heapTableAddresses,prg_state.getHeapTable().getContent()));

            if(display_flag){
//                System.out.println("--------NEXT STATE--------");
//                System.out.println(prg_state);
                this.repo.logPrgStateExec();
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
