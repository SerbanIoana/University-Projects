import time

import pygame

from domain.utils import *


def printMenu():
    print("\n1. Run Greedy algorithm")
    print("2. Run A* algorithm")
    print("0. BACK")


def initPyGame():
    # init the pygame
    pygame.init()
    logo = pygame.image.load("logo32x32.png")
    pygame.display.set_icon(logo)
    pygame.display.set_caption("Path in simple environment")

    # create a surface on screen that has the size of 800 x 480
    screen = pygame.display.set_mode((400, 400))
    screen.fill(WHITE)
    return screen


def displayWithPath(image, path):
    # initialize font
    myfont = pygame.font.SysFont('Comic Sans MS', 15)

    mark = pygame.Surface((20, 20))
    mark.fill(GREEN)

    counter = 0
    for move in path:
        textsurface = myfont.render(counter.__str__(), False, (0, 0, 0))
        image.blit(mark, (move[1] * 20, move[0] * 20))
        image.blit(textsurface, (move[1] * 20, move[0] * 20))
        counter += 1
    return image


class Console:
    def __init__(self, controller):
        self.controller = controller

    def image(self, colour=BLUE, background=WHITE):
        imagine = pygame.Surface((400, 400))
        brick = pygame.Surface((20, 20))
        brick.fill(BLUE)
        imagine.fill(WHITE)
        map = self.controller.repo.map

        for i in range(map.n):
            for j in range(map.m):
                if map.surface[i][j] == 1:
                    imagine.blit(brick, (j * 20, i * 20))

        return imagine

    def mapWithDrone(self, mapImage, finalX, finalY):
        drone = self.controller.repo.drone

        drona = pygame.image.load("drona.png")

        start = pygame.Surface((20, 20))
        start.fill(GREEN)

        finish = pygame.Surface((20, 20))
        finish.fill(RED)

        mapImage.blit(drona, (drone.y * 20, drone.x * 20))
        # mapImage.blit(start, (self.y * 20, self.y * 20))
        mapImage.blit(finish, (finalY * 20, finalX * 20))

        return mapImage

    def runConsole(self):
        screen = initPyGame()

        while True:
            # event handling, gets all event from the event queue
            for event in pygame.event.get():
                # only do something if the event is of type QUIT
                if event.type == pygame.QUIT:
                    # change the value to False, to exit the main loop
                    pygame.quit()

            screen.blit(self.mapWithDrone(self.image(), self.controller.finalX, self.controller.finalY), (0, 0))
            pygame.display.flip()

            while True:
                printMenu()
                option = input(">>>")

                if option == "1":
                    found, path = self.controller.searchGreedy()
                    # found, path = self.controller.searchAStar()
                    if found:
                        screen.blit(displayWithPath(self.image(), path), (0, 0))
                        pygame.display.flip()
                    else:
                        break

                elif option == "2":
                    found, path = self.controller.searchAStar()
                    if found:
                        screen.blit(displayWithPath(self.image(), path), (0, 0))
                        pygame.display.flip()
                    else:
                        break
                else:
                    break