
import java.math.BigInteger;

public class RSADecrypt 
{

	public static void main(String[] args) 
{
		if( args.length != 3  )
		{
			System.out.println("Error: Invalid number of Arguments");
			System.out.println("Expected format: java RSADecrypt /Absolute path/file.enc /Absolute path/dec_file /Absolute path/Data.dat");
			System.out.println("					              or");
			System.out.println("Expected format: java RSADecrypt RelativePath/file.enc RelativePath/dec_file RelativePath/Data.dat");
			System.out.println("Exiting Program...");
			System.exit(0);
		}
	
		// Utility Object that will handle Encryption and Decryption
		CryptUtility cryptUtility 	= new CryptUtility(); 
		
		// Utility Object that will handle file I/O
		IOutility fileIO = new IOutility(); 
	
		// Utility Object that will validate user input
		Utility utility = new Utility();
		
		// Paths To files
		String pathToEncFile; 
		String pathToDecFile; 
		String pathToKeyFile;
		
		// Strings To hold file Content
		String keysAndModules;
		String encFileContent;
		String fileContent;
		
		// Integer representations of file content
		BigInteger modules;
		BigInteger privateKey;
		BigInteger DecFileContent;
		
		// Check if given paths are absolute or relative
		// if relative convert to Absolute
		pathToEncFile = utility.CheckIfPathIsAbsolute(args[0]);
		pathToDecFile = utility.CheckIfPathIsAbsolute(args[1]);
		pathToKeyFile = utility.CheckIfPathIsAbsolute(args[2]);
		
		// Get needed content from files
		keysAndModules = fileIO.getContentFromFile(pathToKeyFile);
		encFileContent = fileIO.getContentFromFile(pathToEncFile);
		
		// Get n and d value from keys file
		modules 	= utility.parseKeysString(keysAndModules, 'n');
		privateKey  = utility.parseKeysString(keysAndModules, 'd');
		
		// Decrypt file and convert file content back to a string
		DecFileContent 	= cryptUtility.decryptFile(privateKey, modules, encFileContent);
        fileContent 	=  new String(DecFileContent.toByteArray()); 
        
        //Write original file content to file 
		fileIO.writeDataToFile( pathToDecFile, fileContent );
	}

}
