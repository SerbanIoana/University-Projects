
# import the pygame module, so you can use it
import pickle
import sys
from time import sleep
import pygame
from random import random, randint

from DetectedMap import DetectedMap
from Drone import Drone
from Environment import Environment

# Creating some colors
BLUE = (0, 0, 255)
GRAYBLUE = (50, 120, 120)
RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)

# define directions
UP = 0
DOWN = 2
LEFT = 1
RIGHT = 3

# define indexes variations
v = [[-1, 0], [1, 0], [0, 1], [0, -1]]


# define a main function
def main():
    # we create the environment
    environment = Environment()
    environment.loadEnvironment("test2.map")
    # print(str(environment))

    # we create the map
    detectedMap = DetectedMap()

    # initialize the pygame module
    pygame.init()
    # load and set the logo
    logo = pygame.image.load("logo32x32.png")
    pygame.display.set_icon(logo)
    pygame.display.set_caption("drone exploration")

    # we position the drone somewhere in the area
    x = randint(0, 19)
    y = randint(0, 19)

    # cream drona
    drone = Drone(x, y)

    # create a surface on screen that has the size of 800 x 480
    screen = pygame.display.set_mode((800, 400))
    screen.fill(WHITE)
    screen.blit(environment.image(), (0, 0))

    # define a variable to control the main loop
    running = True

    # main loop
    while running:
        # event handling, gets all event from the event queue
        for event in pygame.event.get():
            # only do something if the event is of type QUIT
            if event.type == pygame.QUIT:
                # change the value to False, to exit the main loop
                running = False
            # if event.type == KEYDOWN:
            #     # use this function instead of move
            #     # drone.moveDSF(detectedMap)
            #     drone.move(detectedMap)

        detectedMap.markDetectedWalls(environment, drone.x, drone.y)
        screen.blit(detectedMap.image(drone.x, drone.y), (400, 0))
        pygame.display.flip()

        drone.moveDFS(detectedMap)
        sleep(0.2)

    print("Search ended!")
    pygame.quit()


# run the main function only if this module is executed as the main script
# (if you import this as a module then nothing is executed)
if __name__ == "__main__":
    # call the main function
    main()