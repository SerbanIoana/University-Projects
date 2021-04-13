import pygame
from pygame import K_UP, K_DOWN, K_LEFT, K_RIGHT

# define indexes variations
v = [[-1, 0], [1, 0], [0, 1], [0, -1]]


class Drone():
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.visited = []
        self.stack = [(x, y)]

    def move(self, detectedMap):
        pressed_keys = pygame.key.get_pressed()
        if self.x > 0:
            if pressed_keys[K_UP] and detectedMap.surface[self.x - 1][self.y] == 0:
                self.x = self.x - 1
        if self.x < 19:
            if pressed_keys[K_DOWN] and detectedMap.surface[self.x + 1][self.y] == 0:
                self.x = self.x + 1

        if self.y > 0:
            if pressed_keys[K_LEFT] and detectedMap.surface[self.x][self.y - 1] == 0:
                self.y = self.y - 1
        if self.y < 19:
            if pressed_keys[K_RIGHT] and detectedMap.surface[self.x][self.y + 1] == 0:
                self.y = self.y + 1

    def moveDFS(self, detectedMap):
        # TO DO!
        # rewrite this function in such a way that you perform an automatic
        # mapping with DFS

        if len(self.stack) == 0:
            self.x, self.y = None, None
            pygame.quit()

        if (self.x, self.y) != (None, None) and (self.x, self.y) not in self.visited:
            self.visited.append((self.x, self.y))
            for var in v:
                new_x = self.x + var[0]
                new_y = self.y + var[1]
                if 0 <= new_x <= 19 and 0 <= new_y <= 19:
                    if detectedMap.surface[new_x][new_y] != 1:
                        if (new_x, new_y) not in self.visited:
                            self.stack.append((self.x, self.y))
                            self.stack.append((new_x, new_y))

        if len(self.stack) != 0:
            self.x, self.y = self.stack.pop()
        # else:
        #     self.x, self.y = None, None
        #     print("Search ended!")
        #     pygame.quit()