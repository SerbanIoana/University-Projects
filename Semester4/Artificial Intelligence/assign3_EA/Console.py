# imports
import statistics
from random import seed

import numpy as np
from matplotlib import pyplot
from ui.Gui import *
from controller import *
from repository import *
from domain import *


# create a menu
#   1. map options:
#         a. create random map
#         b. load a map
#         c. save a map
#         d visualise map
#   2. EA options:
#         a. parameters setup
#         b. run the solver
#         c. visualise the statistics
#         d. view the drone moving on a path
#              function gui.movingDrone(currentMap, path, speed, markseen)
#              ATENTION! the function doesn't check if the path passes trough walls


def print_mainMenu():
    print("\n1. DMap options")
    print("2. Algorithm options")
    print("0. EXIT")


def print_mapMenu():
    print("\n1. Create random map")
    print("2. Load map")
    print("3. Save map")
    print("4. Visualise map")
    print("0. BACK")


def print_algMenu():
    print("\n1. Parameters setup")
    print("2. Run solver once, compute execution time, visualise statistics")
    print("3. Compute avg and stddev for more runs")
    print("4. View the drone on a path")
    print("0. BACK")


class Console:
    def __init__(self, controller):
        self.controller = controller
        self.loaded_map = False
        self.params_setup = False
        self.progr_solved = False

    def run_console(self):
        while True:
            print_mainMenu()
            option = input(">>>")

            if option == "1":
                self.run_mapMenu()
            elif option == "2":
                if self.loaded_map:
                    self.run_algMenu()
                else:
                    print("No map was created yet!")
                    continue
            elif option == "0":
                exit(0)
            else:
                print("Invalid choice!")

    def run_mapMenu(self):
        while True:
            print_mapMenu()
            option = input(">>>")

            if option == "1":
                # Create random map
                self.loaded_map = True
                self.controller.repo.createRandomMap()
            elif option == "2":
                # Load map
                self.loaded_map = True
                self.controller.repo.loadMap()
            elif option == "3":
                # Save map
                if self.loaded_map:
                    self.controller.repo.saveMap()
                else:
                    print("No map was created yet!")
            elif option == "4":
                # Visualise map
                if self.loaded_map:
                    mapWithDrone(self.controller.repo.dMap)
                else:
                    print("No map was created yet!")
            elif option == "0":
                break
            else:
                print("Invalid choice!")

    def run_algMenu(self):
        drone_battery = None
        population_size = None
        number_runs = None
        mutation_prob = None
        crossover_prob = None

        solution_path = None
        solution_fitness_avg = None
        solution_fitness_max = None
        solution_fitness = None

        while True:
            print_algMenu()
            option = input(">>>")

            if option == "1":
                # Parameters setup
                # drone battery=individual size, population size, number of runs, mutation prob, crossover prob
                self.params_setup = True
                drone_battery, population_size, mutation_prob, crossover_prob, number_runs = self.setupParameters()

            elif option == "2":
                # Run solver once, compute execution time, visualise statistics
                if not self.params_setup:
                    print("Parameters not set up!")
                    continue
                if self.progr_solved:
                    print("Program already solved!")
                    continue

                # run solver once
                solution_start = time.time()
                solution_path, solution_fitness_avg, solution_fitness_max, solution_fitness = \
                    self.controller.solver(drone_battery, population_size, mutation_prob, crossover_prob, number_runs)
                solution_end = time.time()

                self.progr_solved = True

                # display solution data
                print(f"Algorithm execution time: {solution_end - solution_start} seconds")
                print(f"Solution path length: {len(solution_path) - 1} moves")
                print(f"Solution fitness: {solution_fitness}")

                # create statistics
                pyplot.plot(solution_fitness_avg)
                pyplot.plot(solution_fitness_max)
                pyplot.savefig("oneRun.png")
                pyplot.close()

            elif option == "3":
                # Compute avg and stddev for more runs
                if not self.params_setup:
                    print("Parameters not set up!")
                    continue

                fitness_values = []
                for i in range(30):
                    seed(i)
                    _, _, _, fitness = self.controller.solver(drone_battery, population_size, mutation_prob, crossover_prob, number_runs)
                    fitness_values.append(fitness)

                avg_solutions_fitness = np.average(fitness_values)
                stddev_solutions_fitness = np.std(fitness_values)

                # display avg and stddev of solutions
                print(f"Average solution fitness: {avg_solutions_fitness}")
                print(f"Standard deviation of solution fitness: {stddev_solutions_fitness}")

                # create graph for fitness of solutions
                pyplot.plot(fitness_values)
                pyplot.savefig("multipleRuns.png")
                pyplot.close()

            elif option == "4":
                # View the drone on a path
                if self.progr_solved:
                    movingDrone(self.controller.repo.dMap, solution_path)
                else:
                    print("Program not yet solved!")

            elif option == "0":
                break
            else:
                print("Invalid choice!")

    @staticmethod
    def setupParameters():
        drone_battery = input("battery ~30: ")
        if len(drone_battery) != 0:
            drone_battery = int(drone_battery)
        else:
            drone_battery = 30

        population_size = input("population size ~100:  ")
        if len(population_size) != 0:
            population_size = int(population_size)
        else:
            population_size = 100

        mutation_prob = input("mutation probability ~0.04: ")
        if len(mutation_prob) != 0:
            mutation_prob = float(mutation_prob)
        else:
            mutation_prob = 0.04

        crossover_prob = input("crossover probability ~0.8: ")
        if len(crossover_prob) != 0:
            crossover_prob = float(crossover_prob)
        else:
            crossover_prob = 0.8

        number_runs = input("number of runs ~40: ")
        if len(number_runs) != 0:
            number_runs = int(number_runs)
        else:
            number_runs = 40

        return drone_battery, population_size, mutation_prob, crossover_prob, number_runs

