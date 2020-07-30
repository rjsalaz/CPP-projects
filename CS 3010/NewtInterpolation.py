#!/bin/python3
# Randy Salazar
# Assignment 4 - Exercise 3
# 4/20/2020

import sys
import time

def createVectorFromInputFile(inputFromFile, row):
    # convert input from string list into float list
    lineOfStrings = inputFromFile[row].split()
    lineOfFloat = list(map(float, lineOfStrings))
    vector = lineOfFloat

    return vector


# Read input from file and calls function to
# create the needed x and y list
def readFromFileAndCreateMatrixAndVector(inputFile):
    fileContent = open(inputFile, 'r')
    inputFromFile = fileContent.readlines()
    fileContent.close

    #Split file rows into float vectors
    xVector = createVectorFromInputFile(inputFromFile, 0)
    yVector = createVectorFromInputFile(inputFromFile,  1)

    return xVector, yVector

# Coeff
def coeff(xs, ys, cs):

    n = len(xs)

    for i in range(0, n):
        cs[i] = ys[i]


    for j in range(1, n):

        for i in range(n - 1 , j - 1, -1 ):
            cs[i] = (cs[i] - cs[i-1])/(xs[i] - xs[i - j])

    return

# Newton
def evalNewton(xs, cs, z):

    n = len(xs) - 1
    result = cs[n]

    for i in range(n - 1, -1, -1):
        result = result * (z - xs[i]) + cs[i]

    return result

########## MAIN #################


userInput = 0
inputFile = inputFile = sys.argv[len(sys.argv) - 1]
xVector , yVector = readFromFileAndCreateMatrixAndVector(inputFile)

# Initalize vector
coefficantVector = [0] * len(xVector)

print("X Points: " + '[%s]' % ', '.join(map(str, xVector)))
print("Y Points: " + '[%s]' % ', '.join(map(str, yVector)))

print("Enter q to quit the program")
print("\n\n")

userInput = input ("Enter a value to be used to evaluate the polynomial: ") 

while  userInput.lower() != 'q': 
    
    startTime = time.time_ns()

    coeff(xVector, yVector, coefficantVector )
    result = evalNewton(xVector, coefficantVector, float(userInput))

    endTime = time.time_ns() - startTime

    print("The polynomial evaluated at " + str(userInput) + " is " + str(result))
    print("Elapsed Time: " + str(endTime) + " Nanoseconds")

    print("\n")

    userInput = input ("Enter a value to be used to evaluate the polynomial: ")


print("Exiting Program...")
