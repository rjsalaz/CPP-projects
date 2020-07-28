import java.math.BigInteger;

public class RSAGenKey
{
		
	public static void main(String[] args) 
	{
		if( args.length != 1 )
		{
			System.out.println("Error: Invalid number of Arguments");
			System.out.println("Expected Input Format: java RSAGenKey /AbsolutePath/Data.dat ");
			System.out.println("			    or							 ");
			System.out.println("Expected Input Format: java RSAGenKey  RelativePath/Data.dat ");
			System.out.println("Exiting Program...");
			System.exit(0);
		}
		
		// Utility Object that will generate all needed values
		KeyGenUtil keyGenUtil = new KeyGenUtil();
		
		// Utility Object that will handle file I/O
		IOutility fileIO = new IOutility(); 
	
		// Utility Object that will validate user input
		Utility  utility = new Utility();
			
		// Check if given paths are absolute or relative
		String pathToKeyFile;
		pathToKeyFile = utility.CheckIfPathIsAbsolute(args[0]);
		
		//Convert keys to strings
		String data =  "n" + keyGenUtil.getModules().toString() + "e" + keyGenUtil.getPublicKey().toString()  + "d" + keyGenUtil.getPrivateKey().toString();
		
		fileIO.writeDataToFile(pathToKeyFile, data);
		
	}
}
