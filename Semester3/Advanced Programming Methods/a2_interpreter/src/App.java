import controller.Controller;
import repository.IRepository;
import repository.Repository;
import view.View;

public class App {
    public static void main(String[] args) {
        IRepository repo = new Repository();
        Controller controller = new Controller(repo, true);
        View view = new View(controller);
        view.run();
    }
}
