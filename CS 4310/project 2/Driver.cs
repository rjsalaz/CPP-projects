using System;
using System.Collections.Generic;
using System.Net.Sockets;
using System.Text;


namespace Project2
{
    class Driver
    {
        static void Main()
        {

            String [] fileContent;
            string fCFSPageFaultCount;
            string lRUPageFaultCount;
            string oAPageFaultCount;

            TestCaseGenerator testCaseGenerator = new TestCaseGenerator();
            IOUtility iOUtility = new IOUtility();

            //Declare algorithm objects
            FirstComeFirstServe firstComeFirstServe;
            LeastRecentlyUsed leastRecentlyUsed;
            OptimalAlgorithm optimalAlgorithm;

            //Create Test Data
            testCaseGenerator.CreateData();

            //Read data from file and parse data for pageFrame and refString 
            fileContent = iOUtility.ReadDataFromFile(1);
            fileContent = iOUtility.ParseFileContent(fileContent);

            // Instantiate algorithms with data from file
            firstComeFirstServe = new FirstComeFirstServe(fileContent[0], fileContent[1]);
            leastRecentlyUsed   = new LeastRecentlyUsed(fileContent[0], fileContent[1]);
            optimalAlgorithm    = new OptimalAlgorithm(fileContent[0], fileContent[1]);


            // Run Algorithms with theepriveded data
            fCFSPageFaultCount =  firstComeFirstServe.RunAlgo();
            lRUPageFaultCount  = leastRecentlyUsed.RunAlgo();
            oAPageFaultCount   = optimalAlgorithm.RunAlgo();


            //Display Results 
            iOUtility.Display( fileContent, fCFSPageFaultCount, lRUPageFaultCount, oAPageFaultCount);

        }

    }
}
