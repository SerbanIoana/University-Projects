from random import random, randrange

import numpy as np


class DMap:
    def __init__(self, n=20, m=20):
        self.n = n
        self.m = m
        self.droneX = randrange(n)
        self.droneY = randrange(m)
        self.surface = np.zeros((self.n, self.m))

    def randomMap(self, fill=0.2):
        for i in range(self.n):
            for j in range(self.m):
                if random() <= fill:
                    self.surface[i][j] = 1

    def __str__(self):
        string = ""
        for i in range(self.n):
            for j in range(self.m):
                string = string + str(int(self.surface[i][j]))
            string = string + "\n"
        return string

