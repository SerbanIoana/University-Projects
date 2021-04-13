package view.ui;

import controller.Controller;
import exceptions.MyException;

public class RunExample extends Command {
    private Controller controller;

    public RunExample(String key, String description, Controller controller) {
        super(key, description);
        this.controller = controller;
    }

    @Override
    public void execute() {
        try
        {
            controller.allStep();
        }
        catch (MyException e) {
            System.out.println(e.getMessage());
        }
    }
}
