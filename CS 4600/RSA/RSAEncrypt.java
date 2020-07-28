
import java.math.BigInteger;

public class RSAEncrypt 
{
	
	public static void main(String[] args) 
	{
		
		if( args.length != 3  )
		{
			System.out.println("Error: Invalid number of Arguments");
			System.out.println("Expected format: java RSAEncrypt /AbsolutePath/file.txt /AbsolutePath/file.enc /AbsolutePath/Data.dat");
			System.out.println("					 or");
			System.out.println("Expected format: java RSAEncrypt RelativePath/file.txt RelativePath/file.enc RelativePath/key.dat");
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
		String pathToTextFile;
		String pathToEncFile;
		String pathToKeyFile;
		
		// Strings To hold file Content
		String keysAndModules;
		String fileContent;
		
		// Integer representations of file content
		BigInteger modules;
		BigInteger publicKey;
		BigInteger encryptedFileContent ; 
		
		// Check if given paths are absolute or relative
		pathToTextFile 	= utility.CheckIfPathIsAbsolute(args[0]);
		pathToEncFile 	= utility.CheckIfPathIsAbsolute(args[1]);
		pathToKeyFile	= utility.CheckIfPathIsAbsolute(args[2]);
		
		// Get needed content from files
		keysAndModules  = fileIO.getContentFromFile(pathToKeyFile);
		fileContent 	= fileIO.getContentFromFile(pathToTextFile);
		
		// Get n and e value from keys file
		modules   = utility.parseKeysString(keysAndModules, 'n');
		publicKey = utility.parseKeysString(keysAndModules, 'e');
	
		// Encrypt files numeric value and convert it to a big integer
		encryptedFileContent = cryptUtility.encryptFile(publicKey, modules, fileContent); 
		
		// Check if 
		utility.isModulesIsLessThanEncryptedFile(modules, encryptedFileContent);
		
		// Write encrypted file content to file
		fileIO.writeDataToFile(pathToEncFile, encryptedFileContent.toString());
		
	}
}
