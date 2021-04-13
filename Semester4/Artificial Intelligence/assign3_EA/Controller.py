import random

import numpy as np

from domain.Population import Population
from repository import *


class Controller:
    def __init__(self, repo):
        self.repo = repo

    def iteration(self, population_size, mutation_prob, crossover_prob):
        # args - list of parameters needed to run one iteration
        new_population_list = []     # will be bigger than current population, will do selection later

        # a iteration:
        # selection of the parents
        current_population = self.repo.population
        for individual in current_population.individuals:
            new_population_list.append(individual)

        parent_selection = self.repo.population.selection(population_size//2)
        # create offsprings by crossover of the parents
        for parent in parent_selection:
            other_parent = random.choice(parent_selection)
            while parent != other_parent:
                other_parent = random.choice(parent_selection)

            offspring1, offspring2 = parent.crossover(other_parent, crossover_prob)
            # apply some mutations
            offspring1.mutate(mutation_prob)
            offspring2.mutate(mutation_prob)

            new_population_list.append(offspring1)
            new_population_list.append(offspring2)

        # selection of the survivors
        new_population = Population(current_population.dMap, len(new_population_list), current_population.individual_size, individuals=new_population_list)
        survivor_selection = new_population.selection(population_size)
        self.repo.setPopulation(survivor_selection)

    def run(self, population_size, mutation_prob, crossover_prob, number_runs):
        # args - list of parameters needed in order to run the algorithm
        list_fitness_avg = []
        list_fitness_max = []
        best_solution = None
        best_path = None

        # until stop condition
        #    perform an iteration
        #    save the information need it for the satistics
        for _ in range(number_runs):
            self.iteration(population_size, mutation_prob, crossover_prob)
            list_fitness_avg.append(
                np.average([individual.fitness for individual in self.repo.population.individuals])
            )
            list_fitness_max.append(
                max([individual.fitness for individual in self.repo.population.individuals])
            )

            for individual in self.repo.population.individuals:
                if best_solution is None or individual.fitness > best_solution.fitness:
                    best_solution = individual

        best_path = best_solution.getPathFromChromosome()

        # return the results and the info for statistics
        return best_path, list_fitness_avg, list_fitness_max, best_solution.fitness

    def solver(self, drone_battery, population_size, mutation_prob, crossover_prob, number_runs):
        # args - list of parameters needed in order to run the solver

        # create the population
        self.repo.createPopulation(population_size, individual_size=drone_battery)
        # run the algorithm
        solution_path, solution_fitness_avg, solution_fitness_max, solution_fitness = self.run(population_size, mutation_prob, crossover_prob, number_runs)
        # return the results and the statistics
        return solution_path, solution_fitness_avg, solution_fitness_max, solution_fitness
        pass
