from NeuralNetUtil import buildExamplesFromCarData,buildExamplesFromPenData
from NeuralNet import buildNeuralNet
import cPickle 
from math import pow, sqrt

def average(argList):
    return sum(argList)/float(len(argList))

def stDeviation(argList):
    mean = average(argList)
    diffSq = [pow((val-mean),2) for val in argList]
    return sqrt(sum(diffSq)/len(argList))

penData = buildExamplesFromPenData() 
def testPenData(hiddenLayers = [24]):
    return buildNeuralNet(penData,maxItr = 200, hiddenLayerList =  hiddenLayers)

carData = buildExamplesFromCarData()
def testCarData(hiddenLayers = [16]):
    return buildNeuralNet(carData,maxItr = 200,hiddenLayerList =  hiddenLayers)

def main():
    penDataAccList = []
    carDataAccList = []
    for i in range(5):
        nnet, accuracy = testPenData()
        nnet, accuracy2 = testCarData()
        penDataAccList.append(accuracy)
        carDataAccList.append(accuracy2)
    penAvg = average(penDataAccList)
    print("PEN DATA AVERAGE:", penAvg)
    carAvg = average(carDataAccList)
    print("CAR DATA AVERAGE:", carAvg)
    print("PEN DATA MAX:", max(penDataAccList))
    print("CAR DATA MAX:", max(carDataAccList))
    print("STD DEV OF PEN DATA:", stDeviation(penDataAccList))
    print("STD DEV OF CAR DATA:", stDeviation(carDataAccList))


def diffHiddenLayers():
    print("Question 6!")
    hiddenLayers = [0]
    while hiddenLayers[0] <= 40:
        print("HIDDEN LAYERS:", hiddenLayers[0])
        penDataAccList = []
        carDataAccList = []
        for i in range(5):
            nnet, accuracy = testPenData(hiddenLayers)
            nnet, accuracy2 = testCarData(hiddenLayers)
            penDataAccList.append(accuracy)
            carDataAccList.append(accuracy2)
        penAvg = average(penDataAccList)
        print("PEN DATA AVERAGE:", penAvg)
        carAvg = average(carDataAccList)
        print("CAR DATA AVERAGE:", carAvg)
        print("PEN DATA MAX:", max(penDataAccList))
        print("CAR DATA MAX:", max(carDataAccList))
        print("STD DEV OF PEN DATA:", stDeviation(penDataAccList))
        print("STD DEV OF CAR DATA:", stDeviation(carDataAccList))
        hiddenLayers[0] += 5



if __name__=='__main__':
    main() #question 5
    diffHiddenLayers() # question 6
