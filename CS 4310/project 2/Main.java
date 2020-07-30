
/*
 @author: Randy Salazar 
 email: rjsalazar@cpp.edu
 Due Date: 5/12/2020
 Description: This project contains my implementation of the 3 paging algorithms First in first out, Least Recently Used, and the optimal algorithm.
 This program is implemented to run through 50 reference string test files. If you want to test it against just one file you'll have to set the totalTestCases variable below to 1.
 You'll also need to edit IOUtility.ReadDataFromFile by giving the location of the file you want to use for testing
 */


public class Main
{

	
	
	public static void main(String[] args)
	{
		
        String [] fileContent;
        
        //Count of page faults from the algorithms
        String fIFOPageFaultCount;
        String lRUPageFaultCount;
        String oAPageFaultCount;
        
        //Running total of page faults
        double fIFOPageFaultRunningTotal = 0;
        double lRUPageFaultRunningTotal = 0;
        double oAPageFaultRunnningTotal = 0;
        
        // number of test cases 
        int totalTestCases = 50;
        
        TestCaseGenerator testCaseGenerator = new TestCaseGenerator();
        IOUtility iOUtility = new IOUtility();

        //Declare algorithm objects
        FirstInFirstOut firstInFirstOut;
        LeastRecentlyUsed leastRecentlyUsed;
        OptimalAlgorithm optimalAlgorithm;

        //Create Test Data
        testCaseGenerator.CreateData();
       
        // Run through all the generated data
        for( int i = 0; i < totalTestCases; i++) 
        {
            //Read data from file and parse data for pageFrame and refString 
            fileContent = iOUtility.ReadDataFromFile(i);
            fileContent = iOUtility.ParseFileContent(fileContent);

            // Instantiate algorithms with data from file
            firstInFirstOut 	= new FirstInFirstOut(fileContent[0], fileContent[1]);
            leastRecentlyUsed   = new LeastRecentlyUsed(fileContent[0], fileContent[1]);
            optimalAlgorithm    = new OptimalAlgorithm(fileContent[0], fileContent[1]);

            // Run Algorithms with the provided data
            fIFOPageFaultCount =  firstInFirstOut.RunAlgo();
            lRUPageFaultCount  = leastRecentlyUsed.RunAlgo();
            oAPageFaultCount   = optimalAlgorithm.RunAlgo();

            //Display Results 
            iOUtility.Display( fileContent, fIFOPageFaultCount, lRUPageFaultCount, oAPageFaultCount);
            
            //Sum up page faults 
            fIFOPageFaultRunningTotal += Integer.parseInt(fIFOPageFaultCount);
            lRUPageFaultRunningTotal  += Integer.parseInt(lRUPageFaultCount);
            oAPageFaultRunnningTotal  += Integer.parseInt(oAPageFaultCount);
            
        }
        
        
        // Display the average of all the running sums
        iOUtility.averageDisplay(fIFOPageFaultRunningTotal/totalTestCases, lRUPageFaultRunningTotal/totalTestCases, oAPageFaultRunnningTotal/totalTestCases);


	}
}
