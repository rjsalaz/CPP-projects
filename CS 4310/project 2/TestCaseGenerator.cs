using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

// Class will generate test data for the alogorithms


namespace Project2
{
    class TestCaseGenerator
    {

        //Number of Reference Strings to create
        private int numOfReferenceStrings;
        private int lengthOfReferenceString;

        //This Values Changes depending on need test case
        private int numOfPageFrames;

        private int maxNumOfPages;
        private int minNumOfPages;

        private string outputFile;
        private string referenceString;

        //Generate random 
        Random rand = new Random();



        public TestCaseGenerator()
        {
                    //Number of Reference Strings to create
            this.numOfReferenceStrings = 50;
            this.lengthOfReferenceString = 30;

            //This Values Changes depending on need test case
            this.numOfPageFrames = 3;

            this.maxNumOfPages = 8;
            this.minNumOfPages = 0;

            this.referenceString = "";

        }


        public void CreateData()
        {
            for (int counter = 0; counter < numOfReferenceStrings; counter++)
            {

                outputFile = "ReferenceString[" + counter.ToString() + "]" + ".txt";

                // Create reference string of length 30
                for (int i = 0; i < lengthOfReferenceString; i++)
                {
                    //Appned new number netween 0 and 7 on to reference String
                    referenceString += rand.Next(minNumOfPages, maxNumOfPages).ToString();

                }

                // Write jobs to a file
                using StreamWriter sw = new StreamWriter(outputFile);

                sw.WriteLine("NumberOfPageFrame value:");
                sw.WriteLine(numOfPageFrames);
                sw.WriteLine("Reference String:");
                sw.WriteLine(referenceString);

                sw.Close();

                referenceString = "";
            }

        }



    }
}
                

