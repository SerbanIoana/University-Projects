import pickle


class Repository:
    def __init__(self, map, drone):
        self.map = map
        self.drone = drone
        self.loadMap("test1.map")

    def saveMap(self, numFile="test.map"):
        with open(numFile, 'wb') as f:
            pickle.dump(self.map, f)
            f.close()

    def loadMap(self, numfile):
        with open(numfile, "rb") as f:
            dummy = pickle.load(f)
            self.map.n = dummy.n
            self.map.m = dummy.m
            self.map.surface = dummy.surface
            f.close()

    # TO DO : add the other components for the repository:
    #    load and save from file, etc
