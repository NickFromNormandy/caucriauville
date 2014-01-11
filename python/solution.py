import math

class Adjacent:

    def __init_(self):

        pass

    def PrepareMap2(self, myArray):
        
        self.TheArray=myArray
        self.TheSize = len(myArray);        
        self.mindistance = 10000000

        print "The unordered array", self.TheArray
        self.theIndice = range(0, self.TheSize)
        print "The unordered indice", self.theIndice
        self.TheOrderedArray = sorted(self.TheArray)

        for distance in self.TheOrderedArray:
            
        complexity = 0
        for i in range(0, self.TheSize):
            mymin = self.TheArray[i]
            myindice = i
            
            for j in range(i+1, self.TheSize):

                complexity = complexity +1
                if mymin > self.TheArray[j]:
                    mymin = self.TheArray[j]
                    myindice = j
                    

            tmp = self.TheArray[i]
            self.TheArray[i] = self.TheArray[myindice]
            self.TheArray[myindice] = tmp

            tmpindice = self.theIndice[i]
            self.theIndice[i] = self.theIndice[myindice]
            self.theIndice[myindice] = tmpindice

    def PrepareMap(self, myArray):
        
        self.ordered = sorted(myArray)
        
        self.distance = []
        for i in self.ordered:
            
        print "Size of the list", self.TheSize, "Real complexity", complexity, "Theory", self.TheSize*math.log(self.TheSize)
        
        
        for i in self.theIndice:
            distance = abs(i-self.theIndice[i])
            self.distance.append(distance)
            if self.mindistance > distance:
                self.mindistance = distance
        
        print "The ordered Array", self.TheArray
        print "The ordered indice", self.theIndice
        print "Distance between unordered indice and ordered indice", self.distance

    def solution(self):
        
        if self.TheSize == 0:
            return -2
        if self.mindistance == 100000000:
            return -1
        if self.mindistance < 100000000:
            return self.mindistance
    

            
theArray = [0,3,3,7,5,3,11,1]
#theArray = [5,10,1,3]
myAdjacent = Adjacent()
myAdjacent.PrepareMap(theArray)
result = myAdjacent.solution()
print "Solution:", result
            

        
