import numpy as np
from numpy.random import choice

from domain.Individual import Individual


class Population:
    def __init__(self, dMap, population_size=0, individual_size=0, individuals=None):
        self.dMap = dMap
        self.population_size = population_size
        self.individual_size = individual_size      # == battery of the drone

        if individuals is None:
            individuals = [Individual(dMap, individual_size) for _ in range(population_size)]
        self.individuals = individuals
        self.evaluate()

    def evaluate(self):
        # evaluates the population
        for individual in self.individuals:
            individual.computeFitness()

    def selection(self, k=0):
        # perform a selection of k individuals from the population
        # and returns that selection
        fitnesses = [individual.fitness for individual in self.individuals]
        min_fitness = min(fitnesses)
        max_fitness = max(fitnesses)
        scaled_fitness = [(current_fitness - min_fitness)/(max_fitness - min_fitness) for current_fitness in fitnesses]

        total_fitness = sum(scaled_fitness)
        probs_of_selection = [fitness/total_fitness for fitness in scaled_fitness]
        sample = choice(self.individuals, k, p=probs_of_selection)
        return sample
