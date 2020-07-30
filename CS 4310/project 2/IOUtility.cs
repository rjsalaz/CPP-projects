using System;
using System.Collections.Generic;
using System.Text;

namespace Project2
{
    class IOUtility
    {

        public string [] ReadDataFromFile( int fileToReadFrom)
        {
            string currentReferenceString = "ReferenceString";

            currentReferenceString += "[" + fileToReadFrom.ToString() + "]" + ".txt";

            // Path to text File that will be read in 
            string[] ReferenceStringText = System.IO.File.ReadAllLines(currentReferenceString);

            return ReferenceStringText;

        }



        public string[] ParseFileContent(string[] fileContent)
        {
            string[] parseFileContent = {"",""};

            parseFileContent[0] = fileContent[1];
            parseFileContent[1] = fileContent[3];

            return parseFileContent; 
         }



        public void Display(String[] fileContent, string fCFSPageFaultCount, string lRUPageFaultCount, string oAPageFaultCount)
        {

        }


    }
}
