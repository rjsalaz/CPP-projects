This ReadMe describes how to compile and run my AESEncryption128.cpp program on a Linux machine from the terminal with g++. 

Step 1. Enter the below command into the terminal to compile the program. The file aes128_constants.h is assumed to be in the same directory as AESEncryption128.cpp. 
    
    	g++ -o AESEncrypt128 AESEncrypt128.cpp   
            or
    	g++ -o AESEncrypt128 AESEncrypt128.cpp aes128_constants.h

Step 2. Enter the below command into the terminal to execute the program. This program assumes the absolute file path will have 0 periods(.) with no extension or 1 period(.) with a 3 letter extension(See example). 
	
./AESEncrypt128 [absolute_path_to_file_to_be_encrypted.txt]  
    
	Example File) text.txt
	Example File) book

	Example Input) ./AESEncrypt128 /root/Documents/book
	Example Input) ./AESEncrypt128 /root/Documents/text.txt
    
Step 3. After executing the program you will be prompted to enter 32 hex values to be used as the key. The key can have spaces with numbers, lower case letters, and upper case letters.

    	Enter a 32 digit Hex Key: [32 hex Values]

   	Example Input) Enter a 32 digit Hex Key: cb d4 77 90 9d 12 66 2b 4c 6a 9e 1b 06 06 45 4a
    	Example Input) Enter a 32 digit Hex Key: 8fd6 174 f9468 889a 006e8f fca8e 8926 d
    	Example Input) Enter a 32 digit Hex Key: 362C0BE7A3653E2B1C4925F2D82D2fAE
    	Example Input) Enter a 32 digit Hex Key: F35 d4C 000 2D4 EAE 024 8b5 050 942 70c Fa

Step 4. After entering the key, the entered text file will be encrypted and stored in the same directory as the entered text file with the same name and the extension enc. 
    
    	Example Ouput) /root/Documents/book.enc
    	Example Ouput) /root/Documents/text.enc

step 5. To test the AES encryption program by decrypting it the method provided by the professor can be used in a Linux terminal. 
    
    	openssl enc -nosalt -aes-128-ecb -d -in [encrypted filename] -out [output filename] -K [the encryption key in hex--no spaces]

    	Example Input) openssl enc -nosalt -aes-128-ecb -d -in text.enc -out textDec.txt -K F35d4C0002d4EAE0248b505094270cFa

If you have any questions you can email me at rjsalazar@cpp.edu