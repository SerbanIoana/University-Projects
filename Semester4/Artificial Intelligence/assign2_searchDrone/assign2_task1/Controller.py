from queue import PriorityQueue

from domain.utils import *


class Controller:
    def __init__(self, repo, initialX, initialY, finalX, finalY):
        self.repo = repo
        self.initialX = initialX
        self.initialY = initialY
        self.finalX = finalX
        self.finalY = finalY

    def getPathSearchAStar(self):
        mapM = self.repo.map

        found = False
        visited = []
        previous = {}  # the node to come from in order to reach the current node
        distance = {}  # distance from initial node to current node
        toVisit = PriorityQueue()

        for i in range(0, mapM.n):
            for j in range(0, mapM.m):
                distance[(i, j)] = 99999999

        distance[(self.initialX, self.initialY)] = 0
        toVisit.put((0, (self.initialX, self.initialY)))
        previous[(self.initialX, self.initialY)] = (-1, -1)

        while toVisit.qsize() != 0 and not found:
            if toVisit.empty():
                return False, previous

            currentNode = toVisit.get()[1]
            visited.append(currentNode)

            if currentNode == (self.finalX, self.finalY):
                found = True
            else:
                for direction in v:
                    newX = currentNode[0] + direction[0]
                    newY = currentNode[1] + direction[1]
                    neighbour = (newX, newY)

                    if 0 <= newX <= 19 and 0 <= newY <= 19:
                        if mapM.surface[newX][newY] != 1:
                            newNeighbourDistance = distance[currentNode] + 1

                            if newNeighbourDistance < distance[neighbour]:
                                distance[neighbour] = newNeighbourDistance
                                g = distance[neighbour]
                                h = self.hManhattan(newX, newY, self.finalX, self.finalY)
                                f = g + h
                                toVisit.put((f, neighbour))
                                previous[neighbour] = currentNode
        return True, previous

    def searchAStar(self):
        # returns a list of moves as a list of pairs [x,y]
        found, previous = self.getPathSearchAStar()
        path = []

        if found:
            currentNode = (self.finalX, self.finalY)
            while currentNode != (-1, -1):
                path.append(currentNode)
                currentNode = previous[currentNode]
            path.reverse()
        return found, path

    def searchGreedy(self):
        # returns a list of moves as a list of pairs [x,y]
        mapM = self.repo.map

        found = False
        path = []
        visited = []

        toVisit = PriorityQueue()
        toVisit.put((0, (self.initialX, self.initialY)))

        while toVisit.qsize() != 0 and not found:
            if toVisit.empty():
                return False, path

            node = toVisit.get()[1]
            visited.append(node)
            path.append(node)

            if node == (self.finalX, self.finalY):
                found = True
            else:
                neighbours = PriorityQueue()
                for direction in v:
                    newX = node[0] + direction[0]
                    newY = node[1] + direction[1]
                    neighbour = (newX, newY)

                    if 0 <= newX <= 19 and 0 <= newY <= 19:
                        if mapM.surface[newX][newY] != 1:
                            if neighbour not in visited:
                                h = self.hManhattan(newX, newY, self.finalX, self.finalY)
                                neighbours.put((h, neighbour))
                toVisit.put(neighbours.get())
        return True, path

    def hManhattan(self, newX, newY, finalX, finalY):
        # aprox distance from current cell (newX, newY) to goal cell (finalX, finalY)
        D = 1
        dx = abs(finalX - newX)
        dy = abs(finalY - newY)
        return D * (dx + dy)
