import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;

public class IOutility 
{

	// write given content to given file 
	public void writeDataToFile(String fileToWriteToo, String data )
	{
		
		if(fileToWriteToo == null)
		{
			System.out.println("Invalid path to File: Path Given To Ouput File Is NULL" );
			System.out.println("Exiting Program..." );
			System.exit(0);
		}

		File fileHandler = new File(fileToWriteToo);
		
		try( FileOutputStream fileOutputHandler= new FileOutputStream(fileHandler))
		{
		
			fileOutputHandler.write(data.getBytes());
			
			System.out.println("Program Ouput has been written to " + fileToWriteToo);
			
			fileOutputHandler.close();
		} 
		catch (FileNotFoundException e) 
		{
			System.out.println("The Output File " + fileToWriteToo + " could not be Found.");
			System.out.println("Writing Content To "+ fileToWriteToo + " Was Not Succesful");
			System.out.println("Exiting Program...");
			System.exit(0);
			
		} 
		catch (IOException e) 
		{
			
			System.out.println("Error: Encounter Error During Writing Output To File \"" + fileToWriteToo + "\".");
			System.out.println("Writing Content To "+ fileToWriteToo + " Was Not Succesful");
			System.out.println("Exiting Program...");
			System.exit(0);
		}
		
	}
	

	//Read content from given file 
	public String getContentFromFile(String pathToInputFile)
	{
		byte[] bytesFromFile;
		String keyString ="";
		
		if(pathToInputFile == null)
		{
			System.out.println("Invalid path to File: Path Given To Input File Is NULL" );
			System.out.println("Exiting Program..." );
			System.exit(0);
		}

		File fileHandler = new File(pathToInputFile);
	
		try(InputStream fileInputHandler = new FileInputStream(fileHandler))
		{
			// Ready bytes from file and convert it to a string
			bytesFromFile = fileInputHandler.readAllBytes();	
			keyString = new String(bytesFromFile);
			
			fileInputHandler.close();
			
		} 
		catch (FileNotFoundException e) 
		{
			System.out.println("Error: The File " + pathToInputFile + " Could Not Be Found.");
			System.out.println("Reading Content From The Input File"+ pathToInputFile + " Was Not Succesful");
			System.out.println("Exiting Program...");
			System.exit(0);
		} 
		catch (IOException e) 
		{
			System.out.println("Error: Encounterd Error During Output To \"" + pathToInputFile + "\".");
			System.out.println("Reading Content from "+ pathToInputFile + " was not succesful");
			System.out.println("Exiting Program...");
			System.exit(0);
		}
		
		return keyString;
	}
	
}
