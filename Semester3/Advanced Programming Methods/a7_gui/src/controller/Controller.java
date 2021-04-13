package controller;

import exceptions.MyException;
import model.PrgState;
import model.value.IValue;
import model.value.RefValue;
import repository.IRepository;

import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import java.util.Map;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.Collectors;

public class Controller {
    private IRepository repo;
    private ExecutorService executor;
    private boolean display_flag;

    public Controller(IRepository repo, boolean display_flag) {
        this.repo = repo;
        this.executor = Executors.newFixedThreadPool(16);
        this.display_flag = display_flag;
    }

//    //garbage collector
//    public Map<Integer, IValue> unsafeGarbageCollector(List<Integer> symTableAddr, Map<Integer,IValue> heapTable){
//        return heapTable.entrySet().stream()
//                .filter(e->symTableAddr.contains(e.getKey()))
//                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
//    }

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


    private void oneStepForAllPrograms(List<PrgState> prgStates) throws MyException, InterruptedException {

        //RUN concurrently one step for each of the existing PrgStates
        //prepare the list of callables
        List<Callable<PrgState>> callList = prgStates.stream()
                .filter(p -> !p.getExeStack().isEmpty())
                .map((PrgState p) ->
                        (Callable<PrgState>)(() -> {
                                return p.oneStep();
                            })
                ).collect(Collectors.toList());

        //start the execution of the callables
        //returns the list of new created PrgStates (namely threads)
        List<PrgState> newPrgList = executor.invokeAll(callList).stream()
                .map(future -> {
                    try {
                        return future.get();
                    } catch (InterruptedException | ExecutionException e) {
                        throw new MyException(e.getMessage());
                    }
                })
                .filter(p -> (p!=null))
                .collect(Collectors.toList());

        //add the newly created threads to the list of existing threads
        prgStates.addAll(newPrgList);

        //after the execution, print the PrgState List into the log file
        prgStates.forEach(prg ->
            repo.logPrgStateExec(prg)
        );

        //Save the current programs in the repository
        this.repo.setPrograms_list((ArrayList<PrgState>) prgStates);
    }

    private List<PrgState> removeCompletedPrograms(List<PrgState> inPrgList)
    {
        return inPrgList.stream()
                .filter(p -> p.isNotCompleted())
                .collect(Collectors.toList());
    }


    public void oneStep() throws MyException {
        List<PrgState> prgStates = removeCompletedPrograms(repo.getPrograms_list());

        prgStates.forEach(prg -> {
            prg.getHeapTable().setContent( safeGarbageCollector(
                    getAddressesFromSymTable(prg.getSymTable().getDictionary().values()),
                    getAddressesFromHeapTable(prg.getHeapTable().getContent().values()),
                    prg.getHeapTable().getContent()));
        });

        try {
            oneStepForAllPrograms(prgStates);
        } catch (InterruptedException e) {
            throw new MyException(e.getMessage());
        }

        prgStates = removeCompletedPrograms(repo.getPrograms_list());
        repo.setPrograms_list((ArrayList<PrgState>) prgStates);

        if(prgStates.isEmpty())
            executor.shutdownNow();
    }


    public void allStep() throws MyException {
        executor = Executors.newFixedThreadPool(2);
        List<PrgState> prgStates = removeCompletedPrograms(repo.getPrograms_list());

        repo.logPrgStateExec(repo.getPrograms_list().get(0));
        while(prgStates.size() > 0){

            //garbage collector for every prgState
            prgStates.forEach(prg -> {
                prg.getHeapTable().setContent( safeGarbageCollector(
                        getAddressesFromSymTable(prg.getSymTable().getDictionary().values()),
                        getAddressesFromHeapTable(prg.getHeapTable().getContent().values()),
                        prg.getHeapTable().getContent()));
            });

            try {
                oneStepForAllPrograms(prgStates);
            } catch (InterruptedException e) {
                throw new MyException(e.getMessage());
            }

            prgStates = removeCompletedPrograms(repo.getPrograms_list());
        }
        executor.shutdownNow();

        //HERE the repository still contains at least one Completed Prg
        // and its List<PrgState> is not empty. Note that oneStepForAllPrg calls the method
        //setPrgList of repository in order to change the repository

        // update the repository state
        repo.setPrograms_list((ArrayList<PrgState>) prgStates);
    }

    public void addNewPrg(PrgState new_prg){
        this.repo.addPrg(new_prg);
    }

    public IRepository getRepo() { return repo; }
    public List<PrgState> getPrgStatesList(){
        return this.repo.getPrograms_list();
    }

}
