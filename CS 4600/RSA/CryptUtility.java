import java.math.BigInteger;

public class CryptUtility
{
	
	// Encrypt given file content
	public BigInteger encryptFile(BigInteger publicKey, BigInteger modulus, String fileContent)
	{
		// Turn the bytes of the text file into a big integer
		BigInteger message = new BigInteger(fileContent.getBytes());
			    
		// c = m^(e) % n
		return  message.modPow(publicKey, modulus);
		
	}
	
	//Decrypt given file content
	public BigInteger decryptFile(BigInteger privateKey, BigInteger modulus, String fileContent)
	{
		
		BigInteger encryptedMessage = new BigInteger(fileContent);
		// m = c^(d) % n
		return  encryptedMessage.modPow(privateKey, modulus);
	}
	
}
