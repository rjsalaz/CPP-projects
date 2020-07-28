
import java.math.BigInteger;

public class Utility 
{
	
	public void  isModulesIsLessThanEncryptedFile(BigInteger modules, BigInteger encryptedContent)
	{
		
		if(modules.compareTo(encryptedContent) == -1)
		{	
			System.out.println("The Cypertext(c) numerical value is bigger than the calculated modulus(n)");
			System.out.println("The Cypertext(c) numerical value is bigger than the calculated modulus(n)");
			System.out.println("Exiting Program...");
			System.exit(0);
			
		}
	}
	
	
	//Search String for desired content 
	public BigInteger parseKeysString(String keys, char parseIdentifier)
	{
		int startingIndex = keys.indexOf(parseIdentifier); 
		String keyString = "";
		BigInteger key = null; 
	 	
		// Keep copying string until next identifier is found 
		for( int i = startingIndex + 1; i < keys.length(); i++)
		{
			
			if ( keys.charAt(i) == 'e' |  keys.charAt(i) == 'd') 
			{
				break; 
			}
			
			keyString += keys.charAt(i); 
		}
		
		return key = new BigInteger(keyString); 
	}
	
	//Check if given path is absolute, if not change it to absolute.
	public String CheckIfPathIsAbsolute(String path)
	{
		char startOfPath = path.charAt(0);
		
		//If given path is already an absolute path then return it
		//else turn the relative path into one
		if( startOfPath == '/' | startOfPath == 'C')
		{
			return path; 
		}
		else
		{
			//split path string with /
			String[] newPath = path.split("/");		
			//remove overlapping directory from path 
			path = System.getProperty("user.dir") + '/'+ newPath[newPath.length - 1];
			
			return path;
		}
		
	
	}
			
}
