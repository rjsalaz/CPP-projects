import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;


public class IOUtility 
{

	 public String [] ReadDataFromFile( int fileToReadFrom)
     {	
		 int count = 0; 
		 String fileLines = null; 
		 String[] ReferenceStringText = new String[4]; 
		 String currentReferenceString = "ReferenceString";
		 
		 //Set this variable to the location of your ReferenceString.txt 
         currentReferenceString += "[" + Integer.toString(fileToReadFrom) + "]" + ".txt";

         //Read from file 
         FileReader fileHandler;
		 try 
		 {
			fileHandler = new FileReader(currentReferenceString);
	        BufferedReader fileReader = new BufferedReader(fileHandler);
             
	         try 
	         {
				while( (fileLines = fileReader.readLine()) != null )
				 {
					 ReferenceStringText[count] = fileLines;
					 count++; 
					 
				 }
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

         return ReferenceStringText;
     }

	 
     public String[] ParseFileContent(String[] fileContent)
     {
    	 String[] parseFileContent = {"",""};

         parseFileContent[0] = fileContent[1];
         parseFileContent[1] = fileContent[3];

         return parseFileContent; 
      }


     public void Display(String[] fileContent, String fCFSPageFaultCount, String lRUPageFaultCount, String oAPageFaultCount)
     {
    	 System.out.println("Page Count : " + fileContent[0] + "\t"+ "Reference String: " + fileContent[1] );
    	 System.out.println("Algorithms :\t" + "FCFS\t" + "LRU\t" + "OptimalAlo"  );
    	 System.out.println("Page Faults:\t" + fCFSPageFaultCount + "\t" + lRUPageFaultCount + "\t" + oAPageFaultCount  );

     }
     
     public void averageDisplay(double fCFSPageFaultCount, double lRUPageFaultCount, double oAPageFaultCount)
     {
    	 System.out.println("********************* Average OF 50 Test Cases *********************" );
    	 System.out.println("Algorithm :\t\t" + "FCFS\t" + "LRU\t" + "OptimalAlo"  );
    	 System.out.println("Page Faults Average:\t" + fCFSPageFaultCount + "\t" + lRUPageFaultCount + "\t" + oAPageFaultCount  );

     }


}
