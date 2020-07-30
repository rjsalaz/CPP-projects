import sys 
# Randy Salazar 
# CS 3010
# Assignment 3 - Exercise 4 

# return the solution of f(argument)
def solveF(vector, argument):
    solution = float(vector[0])
    
    for nums in range(1, len(vector)):
        solution = float(argument) * float(solution) + float(vector[nums])

    return solution
    

# return deriviative of polynomial passed in
def derf(vector):
    
    derivative = [0]*(len(vector)-1)

    for nums in range(0, len(derivative)):
        derivative[nums] = vector[nums] * (len(vector) - 1 - nums)
 
    if derivative[len(derivative) - 1 ] == 0: 
       derivative.pop() 

    return derivative


def bisection( f, a, b, maxIter, eps):


    fa = solveF(f,a)
    fb = solveF(f,b)

    if (fa * fb) >= 0 : 
        print("Inadequate values for a and b")
        return -1 , 0, "Fail" 
    
    error = b - a 
    counter = 0

    for iter in range(0, maxIter):

        error = float(error/2)
        c = a + error 

        fc = solveF(f,c)

        if abs(error) == eps or fc == 0:
            print("Algorithm has converged after %d iterations!" % (counter))
            return c, counter, "Success"

        if (fa * fc) < 0: 
            b = c
            fb = fc 
        else:
            a = c 
            fa = fc 

        counter = counter + 1 

    print("Max iterations reached without convergence...")
    return c, counter, "Fail"
        
### end Bisection


def newton(f, dF, x, maxIter, eps, delta):
   
    fx = solveF(f, x)
    counter = 0
    for iter in range(0, maxIter):
       
        fd = solveF(dF, x)
        
        if abs(fd) < delta: 
            print("Small slope!")
            return x, counter, "Fail"

        d = float(fx / fd) 
        x = x - d
        fx = solveF(f, x)

        if abs(d) == eps : 
            print ("Algorithm has converged after %d iterations!" % (counter))
            return x , counter, "Success"
        counter = counter + 1 
    print("Max iterations reached without convergence...")
    return x , counter, "Fail"

### end newton 


def secant( f, a, b, maxIter, eps): 
    fa = solveF(f, a)
    fb = solveF(f, b)

    if abs(fa) > abs(fb):
        a, b = b, a 
        fa, fb = fb, fa

    counter = 0 

    for iter in range (0, maxIter):

        if abs(fa) > abs(fb):
            a, b = b, a 
            fa, fb = fb, fa
        
        d = float(( b - a ) / (fb - fa))
        
        b = a 
        fb = fa 
        d = d * fa

        if abs(d) == eps: 
            print("Algorithm has converged after %d iterations!" % (counter))
            return a , counter, "Success"

        a = a - d 
        fa = solveF(f, a)

        counter = counter + 1 

    print("Maximum number of iterations reached!")
    return a, counter, "Fail"

### end secant 


def hybrid(f, a, b, maxIter, eps, delta):

    fa = solveF(f,a)
    fb = solveF(f,b)

    counter = 0
    # start with bisection
    for biIter in range(0, maxIter): 
        
        if (fa * fb) >= 0 : 
            print("Inadequate values for a and b")
            return -1 , 0, "Fail" 

        error = b - a
        c = a + (error/2) 
        fc = solveF(f, c)

        if abs(error) == eps or fc == 0:
            print("Algorithm has converged after %d iterations!" % (counter))
            return c, counter, "Success"

        elif abs(error) >= 0.01: 
            break 

        if (fa * fc) < 0: 
            b = c 
            fb = fc 

        else: 
            a = c
            fa = fc 

        counter = counter + 1
    # start newtons method
    for nextIter in range(0, maxIter):

        # check of we passed maxIter
        if counter >= maxIter: 
            break 

        dF = derf(f)
        fd = solveF(dF, c)

        if abs(fd) < delta: 
            break; 

        d = float( fc / fd)
        c = c - d 
        fc = solveF(f, c)

        if abs(d) == eps: 
            print ("Algorithm has converged after %d iterations!" % (counter))
            return c , counter, "Success"

        counter = counter + 1 

    print("Max iterations reached without convergence...")
    return x , counter, "Fail"
    
# End Hybrid 

def createVectorFromInputFile(inputFromFile):
   
    # convert input from string list into float list
    lineOfStrings = inputFromFile[1].split()
    lineOfInput= list(map(float,lineOfStrings))
    vector = lineOfInput

    return vector


def readFromFileAndCreateAndVector(inputFile):

    fileContent = open(inputFile,'r')
    inputFromFile = fileContent.readlines()
    fileContent.close

    vector = createVectorFromInputFile(inputFromFile)

    return vector


def writeAnswerToFile(root, iterations, outcome, inputFile):

    outputFile = inputFile.split('.')[0]
    outputFile = outputFile + ".sol"

    filehandler = open(outputFile, "w+")
    filehandler.write( str(root) + " " + str(iterations)+ " " + outcome )
    filehandler.close


##################### Main Section ########################

# Get input file 
inputFile = sys.argv[len(sys.argv) - 1] 

# defuault settings 
isBisecSet   = True 
isNewtSet    = False
isSecSet     = False
isMaxIterSet = False
isHybridSet  = False 
maxIter      = 10000



# Check for flags passed in 
for x in range (0, len(sys.argv) ): 

    if sys.argv[x] == "-newt":
        isNewtSet= True 
        isBisecSet = False

    if sys.argv[x] == "-sec":
        isSecSet = True 
        isBisecSet = False
    
    if sys.argv[x] == "-hybrid":
        isHybridSet = True
        isBisecSet = False

    if sys.argv[x] == "-maxIter":
        maxIter = int(sys.argv[x+1])
        maxIterPosition = x
        isMaxIterSet = True

# set initP and inItP2 based off flags set 
if isMaxIterSet: 

    initP = sys.argv[maxIterPosition + 2]
    
    if sys.argv[maxIterPosition + 3] != inputFile: 
        initP2 = sys.argv[maxIterPosition + 3]

elif isSecSet or isNewtSet or isHybridSet: 

    initP =  sys.argv[2]

    if sys.argv[3] != inputFile: 
        initP2 = sys.argv[3]
      
else: 

    initP =  sys.argv[1]

    if sys.argv[1] != inputFile: 
        initP2 = sys.argv[2]
      
# get polynomial from input file
vector = readFromFileAndCreateAndVector(inputFile)


if isBisecSet: 

    print("*"*25 + " Using Bisection Method " + "*"*25)
    root, iterations, outcome = bisection(vector, float(initP), float(initP2), maxIter, 0)
            
elif isSecSet: 

    print("*"*25 + " Using Secant Method " + "*"*25)
    root, iterations, outcome = secant(vector, float(initP), float(initP2), maxIter, 0)

elif isNewtSet: 

    print("*"*25 + " Using Newtons Method " + "*"*25)
    derivative = derf(vector)
    root, iterations, outcome = newton(vector, derivative ,float(initP),maxIter, 0, 0)

elif isHybridSet:

    print("*"*25 + " Using Hybrid Method " + "*"*25)
    root, iterations, outcome = hybrid(vector, float(initP), float(initP2),maxIter, 0, 0)

# Write outcomes to file 
writeAnswerToFile(root, iterations, outcome, inputFile)