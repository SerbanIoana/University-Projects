from random import random, randint

import numpy as np

from domain.utils import DIRECTIONS


class Individual:
    def __init__(self, dMap, size=0, chromosome=None):
        self.dMap = dMap
        self.size = size    # == battery of the drone
        if chromosome is None:
            chromosome = [randint(0, 3) for _ in range(self.size)]
        self.chromosome = chromosome

        self.fitness = None

    def getPathFromChromosome(self):
        current_position = (self.dMap.droneX, self.dMap.droneY)
        drone_path = [current_position]

        for move in self.chromosome:
            direction_x = DIRECTIONS[move][0]
            direction_y = DIRECTIONS[move][1]

            next_position = (current_position[0] + direction_x, current_position[1] + direction_y)

            drone_path.append(next_position)
            current_position = next_position
        return drone_path

    def computeFitness(self):
        # compute the fitness for the individual
        # and save it in self.__f
        fitness = 0
        path = self.getPathFromChromosome()
        discovered = np.zeros((self.dMap.n, self.dMap.m))

        for cell in path:
            if 0 <= cell[0] <= 19 and 0 <= cell[1] <= 19 and self.dMap.surface[cell[0]][cell[1]] != 1:
                discovered[cell[0]][cell[1]] = 1
                for direction in DIRECTIONS:
                    new_x = cell[0] + direction[0]
                    new_y = cell[1] + direction[1]
                    neighbour = (new_x, new_y)

                    if 0 <= new_x <= 19 and 0 <= new_y <= 19:
                        if self.dMap.surface[new_x][new_y] != 1:
                            discovered[new_x][new_y] = 1
                fitness += 30
            else:
                fitness -= 20

        fitness += sum([sum(row) for row in discovered])    # sum of values in the matrix
        self.fitness = fitness

    def mutate(self, mutate_probability=0.04):
        # perform a mutation with respect to the representation
        # random resetting mutation
        for i in range(self.size):
            if random() < mutate_probability:
                self.chromosome[i] = randint(0, 3)

    def crossover(self, other_parent, crossover_probability=0.8):
        # 1 cutting-point crossover
        if random() < crossover_probability:
            # perform the crossover between the self and the otherParent
            cutting_point = randint(0, self.size)

            chromosome1 = [self.chromosome[i] if i < cutting_point else other_parent.chromosome[i] for i in range(self.size)]
            offspring1 = Individual(self.dMap, self.size, chromosome=chromosome1)

            chromosome2 = [other_parent.chromosome[i] if i < cutting_point else self.chromosome[i] for i in range(self.size)]
            offspring2 = Individual(self.dMap, self.size, chromosome=chromosome2)
        else:
            offspring1, offspring2 = Individual(self.dMap, self.size, chromosome=self.chromosome),\
                                     Individual(self.dMap, self.size, chromosome=other_parent.chromosome)
        return offspring1, offspring2
