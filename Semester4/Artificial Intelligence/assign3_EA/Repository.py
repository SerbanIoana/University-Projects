import pickle
from domain import *
from domain.DMap import DMap
from domain.Population import Population


class Repository:
    def __init__(self):
        self.population = []
        self.dMap = DMap()
        self.file_name = "test1.map"

    def createPopulation(self, population_size, individual_size):
        # args = [populationSize, individualSize] -- you can add more args
        self.population = Population(self.dMap, population_size, individual_size)

    def setPopulation(self, new_population_list):
        self.population = Population(self.dMap, individuals=new_population_list)

    # TO DO : add the other components for the repository:
    #    load and save from file, etc

    def createRandomMap(self):
        self.dMap.randomMap()

    def saveMap(self):
        with open(self.file_name, 'wb') as f:
            pickle.dump(self.dMap, f)
            f.close()

    def loadMap(self):
        with open(self.file_name, "rb") as f:
            dummy = pickle.load(f)
            self.dMap.n = dummy.n
            self.dMap.m = dummy.m
            self.dMap.surface = dummy.surface
            f.close()
