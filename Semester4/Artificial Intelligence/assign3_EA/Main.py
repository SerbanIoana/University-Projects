from controller.Controller import Controller
from repository.Repository import Repository
from ui.Console import Console


def main():
    repository = Repository()
    controller = Controller(repository)
    console = Console(controller)
    console.run_console()


if __name__ == "__main__":
    main()
