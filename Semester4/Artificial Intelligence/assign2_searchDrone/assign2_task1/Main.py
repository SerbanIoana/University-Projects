# import the pygame module, so you can use it
from queue import PriorityQueue
from random import randint

import pygame
import time
from pygame.locals import *

# Creating some colors
from controller.Controller import Controller
from domain.Drone import Drone
from domain.Map import Map
from domain.utils import *
from repository.Repository import Repository
from ui.Console import Console


# define a main function
def main():
    initialX = randint(0, 19)
    initialY = randint(0, 19)
    # initialX = 5
    # initialY = 6
    finalX = randint(0, 19)
    finalY = randint(0, 19)
    # finalX = 13
    # finalY = 15

    map = Map()
    drone = Drone(initialX, initialY)

    repo = Repository(map, drone)
    controller = Controller(repo, initialX, initialY, finalX, finalY)
    console = Console(controller)

    console.runConsole()


if __name__ == "__main__":
    main()
