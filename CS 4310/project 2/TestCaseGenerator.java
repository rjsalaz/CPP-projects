import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.util.Random;

public class TestCaseGenerator 
{
    //Number of Reference Strings to create
    private int numOfReferenceStrings;
    private int lengthOfReferenceString;

    //This Values Changes depending on need test case
    private int numOfPageFrames;

    private int maxNumOfPages;
    private int minNumOfPages;

    private String outputFile;
    private String referenceString;

    //Generate random 
    Random rand = new Random();

    public TestCaseGenerator()
    {
        //Number of Reference Strings to create
        this.numOfReferenceStrings = 50;
        this.lengthOfReferenceString = 30;

        //This Values Changes depending on need test case
        this.numOfPageFrames = 6;

        this.maxNumOfPages = 8;
        this.minNumOfPages = 0;

        this.referenceString = "";

    }


    public void CreateData()
    {
        for (int counter = 0; counter < numOfReferenceStrings; counter++)
        {

            outputFile = "ReferenceString[" + counter + "]" + ".txt";

            // Create reference string of length 30
            for (int i = 0; i < lengthOfReferenceString; i++)
            {
                //Append new number between 0 and 7 on to reference String
                referenceString += Integer.toString(rand.nextInt(maxNumOfPages) + minNumOfPages);

            }

            // Write jobs to a file
            File fileHandler = new File(outputFile);
         
			try 
			{
				
				FileOutputStream fileWriter = new FileOutputStream(fileHandler);
	        	OutputStreamWriter fileOutputWriter = new OutputStreamWriter(fileWriter);

	        	try
	        	{
					fileOutputWriter.write("NumberOfPageFrame value:\n");
		        	fileOutputWriter.write(numOfPageFrames + "\n");
		        	fileOutputWriter.write("Reference String:\n");
		        	fileOutputWriter.write(referenceString);

		        	fileOutputWriter.close();
		        	
				} 
	        	catch (IOException e) 
	        	{
					// TODO Auto-generated catch block
					e.printStackTrace();
				}

				
			} 
			catch (FileNotFoundException e) 
			{
				
				// TODO Auto-generated catch block
				e.printStackTrace();
				
			}
            
            referenceString = "";
            
        }

    }

	
}
