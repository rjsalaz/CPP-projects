
#!/bin/python3
# Randy Salazar
# Assignment 4 - Exercise 4
# 4/20/2020

import random

def writeDataSetToFile( outputFile, xPoints, ypoints):

    xPointsString = ' '.join(map(str, xPoints))
    ypointsString = ' '.join(map(str, yPoints))

    dataSet = xPointsString + "\n" + ypointsString

    filehandler = open(outputFile, "w")
    filehandler.write(dataSet)

    filehandler.close


def generateXYPoints( numberOfPoints):
    
    xList = []
    yList = []

    # set max for y points
    maxYValue = 600

    # range of values for x points 
    startingPoint = int( -numberOfPoints/2)
    endingPoint = int( numberOfPoints/2)

    for i in range( startingPoint, endingPoint ):

       xList.append(float(i))

       # Random y points  
       randomValue = float(random.randrange(0, maxYValue) - random.randrange(0, maxYValue))
       yList.append(randomValue)

    # radomize the x points
    random.shuffle(xList)

    return xList, yList

############# MAIN #############

userInput = input ("How many data points would you like to be generated: ")
userOutputFile = input ("What file would you the data set to be wriiten to: ")

xPoints, yPoints = generateXYPoints(int(userInput))
writeDataSetToFile(userOutputFile, xPoints, yPoints)

print("The Data set of " + userInput +" points " + "was written to " + userOutputFile )
