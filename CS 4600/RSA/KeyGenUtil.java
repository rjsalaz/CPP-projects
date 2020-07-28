import java.math.BigInteger;
import java.util.Random;

public class KeyGenUtil 
{

	private BigInteger publicKey = new BigInteger("65537"); // e is set to constant value
	private BigInteger primeNumber1 = null;
	private BigInteger primeNumber2 = null;
	private BigInteger modules = null;
	private BigInteger modulesPhi = null;
	private BigInteger privateKey = null;
	
	
	//////// Constructor ////////////////
	
	public KeyGenUtil()
	{
		
		//p
		this.primeNumber1 = GeneratePrimeNumber();
		
		//q
		this.primeNumber2 = GeneratePrimeNumber();
		
		//Check if primes are equal to each other
		while( this.primeNumber1.compareTo(this.primeNumber2) == 0)
		{
			this.primeNumber2 = GeneratePrimeNumber();
		}
	
		//n = p*q
		this.modules = this.primeNumber1.multiply(this.primeNumber2); 
		
		//(n) = (p-1)(p-1)
		this.modulesPhi = calculateModulusPhi(this.primeNumber1 ,this.primeNumber2);
		
		// d = e^(-1) % (n)
		this.privateKey = this.publicKey.modInverse(this.modulesPhi);
	
	}
	
	///////////// Getters ///////////////////
	
	public BigInteger getPublicKey() 
	{
		return publicKey;
	}

	public BigInteger getPrimeNumber1() 
	{
		return primeNumber1;
	}


	public BigInteger getPrimeNumber2() 
	{
		return primeNumber2;
	}


	public BigInteger getModules()
	{
		return modules;
	}

	public BigInteger getModulusPhi() 
	{
		return modulesPhi;
		
	}
	
	public BigInteger getPrivateKey() 
	{
		return privateKey;
	}
	
	
	///////// Methods ////////////////
	
	private  BigInteger calculateModulusPhi(BigInteger prime1, BigInteger prime2)
	{
		// Subtract 1 from both prime numbers to Calculate phi(n)
		prime1 = prime1.subtract(BigInteger.ONE);
		prime2 = prime2.subtract(BigInteger.ONE);
	
		// Return W(n)
		return prime1.multiply(prime2);
		
	}
	 
	 
	private BigInteger GeneratePrimeNumber()
	{
		Random rand;
		BigInteger primeNum = BigInteger.ONE;

		//keep Generating a Number until that Number is within range and Prime
		while( !isPrime(primeNum) & !isWithinBound(primeNum))
		{

			rand = new Random();
			primeNum = BigInteger.ONE;
			
			// Generate a Random prime Number with the 2^513(MSB) bit and LSB set
			// produces odd number
			primeNum = primeNum.or(BigInteger.probablePrime(513, rand));

		}

		return primeNum; 
	}

	
	//Uses Big Integers method to check is @Param is prime
	private Boolean isPrime( BigInteger possiablePrimeNum )
	{

		return possiablePrimeNum.isProbablePrime(1);

	}
	
	// Verify if @Param is within the bounds set by the assignment
	private Boolean isWithinBound( BigInteger possiablePrimeNum)
	{
		
		int maxNumOfBits = 513;
		int minNumOfBits = 511;
		BigInteger upperBound = BigInteger.TWO;
		BigInteger lowerBound = BigInteger.TWO;
	
		try
		{
			//Sets bounds for the generated prime number
			upperBound = upperBound.pow(maxNumOfBits);
			lowerBound = lowerBound.pow(minNumOfBits);
		}
		catch( ArithmeticException e )
		{
			System.out.println("Error: Exponent is Negative.");
			System.out.println("Unable To Calculate Bounds For Prime Number.");
			System.out.println("Exiting Program...");
			System.exit(0);
		}

		if( possiablePrimeNum.compareTo(lowerBound) == 1 & possiablePrimeNum.compareTo(upperBound) == -1 )
		{
			return true; 
		}
		else
		{
			return false; 
		}
		
	}
}
