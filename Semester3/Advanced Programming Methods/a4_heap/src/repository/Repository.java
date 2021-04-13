package repository;

import exceptions.MyException;
import model.PrgState;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;

public class Repository implements IRepository {
    private ArrayList<PrgState> programs_list;
    private String log_file_path;
    private int current_index;


    public Repository(String log_file_path) {
        this.programs_list = new ArrayList<PrgState>();
        this.current_index = 0;
        this.log_file_path = log_file_path;

        try
        {
            //before we begin the program, we create the file and EMPTY it of possible previous content
            PrintWriter writer = new PrintWriter(this.log_file_path);
            writer.print("");
            writer.close();
        }
        catch (IOException ignored)
        {}
    }

    @Override
    public PrgState getCurrentPrg() {
        return programs_list.get(current_index);
    }

    @Override
    public void addPrg(PrgState new_prg) {
        this.programs_list.add(new_prg);
    }

    @Override
    public void logPrgStateExec() throws MyException {
        try
        {
            PrintWriter logFile = new PrintWriter(new BufferedWriter(new FileWriter(this.log_file_path, true)));
            logFile.write("--------------NEXT STATE------------\n");
            if (this.programs_list.get(0) instanceof PrgState)
            {
                PrgState prgState = (PrgState) this.programs_list.get(0);
                logFile.write(prgState.toString() + "\n");
            }
            logFile.close();
        } catch (IOException e) {
            throw new MyException(e.getMessage());
        }
    }

    public ArrayList<PrgState> getPrograms_list() { return programs_list; }
    public String getLog_file_path() { return log_file_path; }
}
