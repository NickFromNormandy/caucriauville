import re

class ReadLine:

    def __init__(self):

        self.WordToOccurence = {}
        self.OccurenceToWords = {}
        self.regulare = re.compile("[^A-Z^a-z]+")

    def ConstructWordToOccurence(self):

        self.InputFile = open("toto.txt", "r")
        for line in self.InputFile:
            words=self.regulare.split(line)
            for word in words:
                if word in self.WordToOccurence:
                    self.WordToOccurence[word]+=1
                else:
                    self.WordToOccurence[word]=1
            
    def ConstructOccurenceToWords(self):

        for word,occurence in self.WordToOccurence.iteritems():

            if occurence in self.OccurenceToWords:
                self.OccurenceToWords[occurence].append(word)
            else:
                self.OccurenceToWords[occurence] = [word]

    def printOccurence(self):
        
        print "Word to Occurences"
        for word in self.WordToOccurence:

            print word, self.WordToOccurence[word]


    def printWords(self):
        
        print "Occurence -> List Of Words"
        for occurence in self.OccurenceToWords:

            print occurence, self.OccurenceToWords[occurence]


a = ReadLine()
a.ConstructWordToOccurence()
a.ConstructOccurenceToWords()
a.printOccurence()
a.printWords()

