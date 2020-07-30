#!/bin/python3
# Randy Salazar 
# Assignment 2
# 2/27/2020

import sys 
import time

# Write answer to file
def writeAnswerToFile(solution, inputFile):
    outputFile = inputFile.split('.')[0]
    outputFile = outputFile + ".sol"

    filehandler = open(outputFile, "w+")
    filehandler.write(str(solution))

    filehandler.close

# Read Vector input from file and return vector 
def createVectorFromInputFile(inputFromFile, rows):
   

    # convert input from string list into float list
    lineOfStrings = inputFromFile[rows+1].split()
    lineOfFloat= list(map(float,lineOfStrings))
    vector = lineOfFloat

    
    return vector


# Read Matrix input from file and return matrix
def createMartrixFromInputFile(inputFromFile, rows):
  
    # Declare matrix of size row*row
    matrix = [0]*rows
    
    # Convert input from string list into float list
    for index in range (1, rows+1 ):  
        lineOfStrings = inputFromFile[index].split()
        lineOfFloat= list(map(float,lineOfStrings))
        matrix[index-1] = lineOfFloat

    return matrix

# Read input from file and calls function to 
# create the needed Matrix and Vectors
def readFromFileAndCreateMatrixAndVector(inputFile):

    fileContent = open(inputFile,'r')
    inputFromFile = fileContent.readlines()
    rows = int(inputFromFile[0])

    fileContent.close

    matrix = createMartrixFromInputFile(inputFromFile, rows)
    vector = createVectorFromInputFile(inputFromFile, rows)

    return matrix, vector, rows


def fwdElimination(matrix,vector,rows):
     
    for k in range(0, (rows-1)):
        pos = k + 1
        for i in range(pos, rows):
            
            mult = (matrix[i][k])/(matrix[k][k])

            for j in range(pos, rows):
                matrix[i][j] = matrix[i][j] - (mult * matrix[k][j])  
               
            vector[i] = (vector[i] - (mult * vector[k]))

    return


def backSubstitution(matrix, vector,solution,n):

    solution[n-1] = vector[n-1] / matrix[n-1][n-1]

    for i in range(n-2, -1, -1) :
        sum = vector[i]
        pos = i + 1

        for j in range( pos, n):
            sum = sum - (matrix[i][j] * solution[j])

        solution[i] = sum/matrix[i][i]

    return


def sspFwdElimination(matrix, vector, index, n):
    scaling = [0]*n

    for i in range(0, n):
        smax = 0

        for j in range(0, n):
            smax = max( smax, abs(matrix[i][j] ))

        scaling[i] = smax

    for k in range(0, (n-1)):
        rmax    = 0 
        maxInd  = 0

        for i in range(k, n):
            r = abs( matrix[index[i]][k] / scaling[index[i]])

            if r > rmax:
                rmax   = r 
                maxInd = i
        # SWAP    
        index[maxInd], index[k] = index[k],index[maxInd]

        for i in range((k+1), n ):
            mult = matrix[index[i]][k] / matrix[index[k]][k]

            for j in range((k+1), n):
                matrix[index[i]][j] = matrix[index[i]][j] - ( mult * matrix[index[k]][j] )\
            
            vector[index[i]] = vector[index[i]] - ( mult * vector[index[k]])
    return


def sppBackSub(matrix, vector, solution, index, n):
    
    solution[n-1] = vector[index[n-1]] / matrix[index[n-1]][n-1]

    for i in range((n-1), -1, -1):
        sum = vector[index[i]]
        
        for j in range((i+1), n):
            sum = sum - matrix[index[i]][j] * solution[j]

        solution[i] = sum/matrix[index[i]][i]
    
    return


def sspGaussian(matrix, vector,rows):

    print("*"*50 + " Used Scaled Partial Pivoting Method "+ "*"*50)
    solution =  [0]*rows
    index    =  [0]*rows


    for i in range(0, rows):
        index[i] = i

    sspFwdElimination(matrix,vector,index,rows)
    sppBackSub(matrix,vector,solution,index,rows)

    return solution

def NaiveGaussian(matrix, vector, rows):
    print("*"*50 + " Used Naive Gaussian Elimination Method "+"*"*50)
    solution = [0]*rows
  
    fwdElimination(matrix, vector, rows)
    backSubstitution(matrix, vector, solution, rows)

 
    return solution


#################### Main Section ####################

# file to read from 
inputFile = sys.argv[len(sys.argv) - 1] 

# Initalize spp flag to false
performSpp = False

#check for parital pivioting flag
for x in range (0, len(sys.argv)): 
    if sys.argv[x] == "-spp":
        performSpp = True

# Get matrix, vector, and num of rows for algorithms
matrix, vector, rows = readFromFileAndCreateMatrixAndVector(inputFile)



if performSpp:

    
    solution = sspGaussian(matrix,vector,rows)
    

else:

    
    solution = NaiveGaussian(matrix,vector,rows)
    


writeAnswerToFile(solution, inputFile)