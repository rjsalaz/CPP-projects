/*
@author: Randy Salazar
Class: CS 4600 MW
Program Description: implementation of AES algorithm in C++, A file is passed in at the command line and a key of 32 hex values are prompted for input. File is encrypted using the key.  
Due: 3/27/2020
Turned In: 3/27/2020
*/

// AESEncrypt.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include "aes128_constants.h"

std::string getDstFilePath(std::string srcFilePath)
{
    bool foundPeriod = false;

    //Find txt file extention from given filepath and replace with enc
    for ( size_t i = 0; i < srcFilePath.size(); i++)
    {
        if (foundPeriod)
        {
            srcFilePath[i]   = 'e';
            srcFilePath[i+1] = 'n';
            srcFilePath[i+2] = 'c';
            break; 
        }

        if (srcFilePath[i] == '.')
        {
            foundPeriod = true; 
        }
    }

    // If no file extention found append .enc to the end
    if (foundPeriod == false)
    {
        srcFilePath += ".enc"; 
    }

    return srcFilePath; 
}

std::string getKeyFromUser()
{
    std::string userInput;
    std::string userInputNoSpaces = "";

    std::cout << "Enter a 32 digit Hex Key: ";
    std::getline(std::cin , userInput);
    std::cin.clear();
    std::cout <<std::endl;

    //remove spaces from input string
    for (size_t i = 0; i < userInput.size(); i++)
    {
        if ( userInput[i] != ' ')
        {
            userInputNoSpaces += userInput[i];
        }
    }

    return userInputNoSpaces; 
}

char findIntRepOfChar(char charToFind)
{
    std::map<char, int> charToIntLookUp;
    std::map<char, int>::iterator itr;

    // Map char values to thier hex value
    charToIntLookUp['0'] = 0;
    charToIntLookUp['1'] = 1;
    charToIntLookUp['2'] = 2;
    charToIntLookUp['3'] = 3;
    charToIntLookUp['4'] = 4;
    charToIntLookUp['5'] = 5;
    charToIntLookUp['6'] = 6;
    charToIntLookUp['7'] = 7;
    charToIntLookUp['8'] = 8;
    charToIntLookUp['9'] = 9;

    charToIntLookUp['a'] = 10; 
    charToIntLookUp['b'] = 11;
    charToIntLookUp['c'] = 12;
    charToIntLookUp['d'] = 13;
    charToIntLookUp['e'] = 14;
    charToIntLookUp['f'] = 15;

    charToIntLookUp['A'] = 10;
    charToIntLookUp['B'] = 11;
    charToIntLookUp['C'] = 12;
    charToIntLookUp['D'] = 13;
    charToIntLookUp['E'] = 14;
    charToIntLookUp['F'] = 15;

    // Find key for passed in char value
    itr = charToIntLookUp.find(charToFind);
    return itr->second; 
}

unsigned int charToInt(char highBits, char lowBits )
{
    // Convert two chars into a int value
    unsigned int upperBits  = findIntRepOfChar(highBits);
    unsigned int lowerBits  = findIntRepOfChar(lowBits);

    // Shift bits to line up with integer data type
    unsigned int newUpperBits = upperBits << 4;
    unsigned int returnValue = newUpperBits + lowerBits;
    
    return returnValue; 
}

void convertKeyStringToBytesArray(std::string key, unsigned char* keybytes)
{      
    unsigned int intRepOfTwoChars;
    unsigned char byteValueOfTwoChars; 
    int counter = 0; 

    //Build keybytes array from String Key
    for (size_t i = 0; i < key.size(); i+=2 )
    {
      
       intRepOfTwoChars = charToInt(key[i], key[i + 1]);
       byteValueOfTwoChars = (char)intRepOfTwoChars; 

       keybytes[counter] = byteValueOfTwoChars;
       counter++; 
    }
}

//Convert for hex values into a interger 
unsigned int fourHexsToInts(unsigned char passedABytes, unsigned char passedBBytes, unsigned char passedCBytes, unsigned char passedDBytes)
{
    unsigned int returnValue;

    //Shift bits to line up properly for interger representation
    unsigned int upperByte = (int)(passedABytes << 24);
    unsigned int midUpperByte = (int)(passedBBytes << 16);
    unsigned int midLowerByte = (int)(passedCBytes << 8);
    unsigned int lowerByte    = (int)passedDBytes;

    returnValue = upperByte + midUpperByte + midLowerByte + lowerByte; 
    return returnValue; 
}

unsigned int calculateGBox( unsigned int gBoxInput, int iteration)
{
    unsigned int gBoxOutPut = 0; 
    unsigned char tempVal; 

    //Shift bits to properly align for conversion to char type
    unsigned char val0 = (char)(gBoxInput >> 24);
    unsigned char val1 = (char)(gBoxInput >> 16);
    unsigned char val2 = (char)(gBoxInput >> 8);
    unsigned char val3 = (char)(gBoxInput);

    //Shift left 
    tempVal = val0;

    val0 = val1;
    val1 = val2;
    val2 = val3;
    val3 = tempVal;

    //Sbox look up
    val0 = sbox[val0];
    val1 = sbox[val1];
    val2 = sbox[val2];
    val3 = sbox[val3];

    val0 ^= rcon[iteration]; 

    gBoxOutPut = fourHexsToInts(val0, val1, val2, val3);

    return gBoxOutPut;
}

void getKeySchedule(unsigned char* keyBytes, unsigned int* keySchedule)
{
    int rconIteration = 0; 
    
    // Build first 4 wBlock from key schedule
    keySchedule[0] = fourHexsToInts(keyBytes[0], keyBytes[1], keyBytes[2], keyBytes[3] );
    keySchedule[1] = fourHexsToInts(keyBytes[4], keyBytes[5], keyBytes[6], keyBytes[7]);;
    keySchedule[2] = fourHexsToInts(keyBytes[8], keyBytes[9], keyBytes[10], keyBytes[11]);;
    keySchedule[3] = fourHexsToInts(keyBytes[12], keyBytes[13], keyBytes[14], keyBytes[15]);;

    // Build the rest of the wblock, 43 in total
    for( size_t i = 4 ; i < 44; i+=4)
    {
        rconIteration++;
        keySchedule[i] = keySchedule[i - 4] ^ calculateGBox(keySchedule[i - 1],rconIteration);
        keySchedule[i + 1] = keySchedule[i - 3] ^ keySchedule[ i ]; 
        keySchedule[i + 2] = keySchedule[i - 2] ^ keySchedule[ i + 1 ];
        keySchedule[i + 3] = keySchedule[i - 1] ^ keySchedule[ i + 2 ];
    }
}

// Convert needed round key to char type
void convertRoundKeyToChars(unsigned char*currentKeyBuffer, unsigned int * wBlocks)
{
    int counter = 0;
    for( size_t i = 0; i < 4; i++ )
    {

        for (size_t j = counter;;)
        {
            currentKeyBuffer[j] = (char)(wBlocks[i] >> 24);
            currentKeyBuffer[j + 1] = (char)(wBlocks[i] >> 16);
            currentKeyBuffer[j + 2] = (char)(wBlocks[i] >> 8);
            currentKeyBuffer[j + 3] = (char)(wBlocks[i]);
            break; 
        }

        counter += 4; 
    }
}

void keyAdd(unsigned int *keySchedule, unsigned char* fileBuffer, int index)
{
    unsigned char roundKeyBuffer[16];
    unsigned int wBlocks[4]; 

    // Get needed wBlock to build round key for needed iteration
    wBlocks[0] = keySchedule[index];
    wBlocks[1] = keySchedule[index + 1];
    wBlocks[2] = keySchedule[index + 2];
    wBlocks[3] = keySchedule[index + 3]; 

    convertRoundKeyToChars(roundKeyBuffer, wBlocks);

    //Perfrom key addition
    for(size_t i = 0; i < 16 ; i++)
    {
        fileBuffer[i] ^= roundKeyBuffer[i]; 
    }
}

void subBytes(unsigned char*fileBuffer) 
{
    // byte-substitution layer
    for (size_t i = 0; i < 16; i++)
    {
        fileBuffer[i] = sbox[fileBuffer[i]];
    }

}

void shiftRows(unsigned char* fileBuffer)
{
    // temp array to hold shifted values 
    unsigned char shiftedFileBuffer[16]; 
   
    // shift fileBuffer values 
    shiftedFileBuffer[0]= fileBuffer[0];
    shiftedFileBuffer[1] = fileBuffer[5];
    shiftedFileBuffer[2] = fileBuffer[10];
    shiftedFileBuffer[3] = fileBuffer[15];

    shiftedFileBuffer[4] = fileBuffer[4];
    shiftedFileBuffer[5] = fileBuffer[9];
    shiftedFileBuffer[6] = fileBuffer[14];
    shiftedFileBuffer[7] = fileBuffer[3];
    
    shiftedFileBuffer[8] = fileBuffer[8];
    shiftedFileBuffer[9] = fileBuffer[13];
    shiftedFileBuffer[10] = fileBuffer[2];
    shiftedFileBuffer[11] = fileBuffer[7];
    
    shiftedFileBuffer[12] = fileBuffer[12];
    shiftedFileBuffer[13] = fileBuffer[1];
    shiftedFileBuffer[14] = fileBuffer[6];
    shiftedFileBuffer[15] = fileBuffer[11];


    //overwrite original buffer with shifted buffer
    for (size_t i = 0; i < 16; i++)
    {
        fileBuffer[i] = shiftedFileBuffer[i]; 
    }
}

void  mixColumns(unsigned char* input) 
{
    unsigned char tmp[16];
    int i;
    for (i = 0; i < 4; ++i) 
    {
        tmp[(i << 2) + 0] = (unsigned char)(mul2[input[(i << 2) + 0]] ^ mul_3[input[(i << 2) + 1]] ^ input[(i << 2) + 2] ^ input[(i << 2) + 3]);
        tmp[(i << 2) + 1] = (unsigned char)(input[(i << 2) + 0] ^ mul2[input[(i << 2) + 1]] ^ mul_3[input[(i << 2) + 2]] ^ input[(i << 2) + 3]);
        tmp[(i << 2) + 2] = (unsigned char)(input[(i << 2) + 0] ^ input[(i << 2) + 1] ^ mul2[input[(i << 2) + 2]] ^ mul_3[input[(i << 2) + 3]]);
        tmp[(i << 2) + 3] = (unsigned char)(mul_3[input[(i << 2) + 0]] ^ input[(i << 2) + 1] ^ input[(i << 2) + 2] ^ mul2[input[(i << 2) + 3]]);
    }

    for (i = 0; i < 16; ++i)
        input[i] = tmp[i];
}


void padBuffer(unsigned char* fileBuffer, unsigned int& bufferSizeReadIn )
{
    // Find diffence from expected buffer size
    int differenceFromFullBuffer = 16 - bufferSizeReadIn;

    // Perform PKCS5 Padding
    char padding = char(differenceFromFullBuffer);
    for ( size_t i = bufferSizeReadIn; i < 16 ; i ++)
    {
        fileBuffer[i] = padding; 
    }

    bufferSizeReadIn += differenceFromFullBuffer; 
}

int main(int argc, char* argv[])
{
    std::string srcFilePath;
    std::string dstFilePath;
    std::string key;

    const unsigned int bufferSize = 16;
    const unsigned int keySchedulerBuffer = 44;

    unsigned char keybytes[bufferSize];
    unsigned int keySchedule[keySchedulerBuffer];
    
    char fileBuffer[bufferSize];
    unsigned char bufferReadIn[bufferSize];
    unsigned int sizeOfBufferReadIn;

    std::ifstream srcFile;
    std::ofstream dstFile;

    srcFilePath = argv[argc - 1];
    dstFilePath = getDstFilePath(srcFilePath);


    std::cout << "*************************** AES Encryption Program ***************************" << std::endl << std::endl;
    std::cout << "File to be encrypted: " << srcFilePath << std::endl << std::endl;

    key = getKeyFromUser(); 

    // if key length dose not equal 32, exit program
    if( key.size() != 32)
    {
        std::cout << "Invalid Key length. . . Exiting program" << std::endl;
        exit(1); 
    }

    convertKeyStringToBytesArray(key, keybytes); 

    // Calculate all round-keys
    getKeySchedule(keybytes, keySchedule);     

    // open files for reading and writiing
    srcFile.open(srcFilePath, std::ifstream::binary);
    dstFile.open(dstFilePath, std::ostream::binary);
    
    // if source file can not be open, exit program 
    if(srcFile)
    {
        std::cout << "Encrypting " << srcFilePath << " ...." <<"( May take a while depending on input file size )" << std::endl;
        while (!srcFile.eof())
        {
            srcFile.read(fileBuffer, bufferSize);

            // Actual Size of Buffer Read in from file
            sizeOfBufferReadIn = srcFile.gcount();

            for (size_t i = 0; i < sizeOfBufferReadIn; i++)
            {
                bufferReadIn[i] = fileBuffer[i];
            }

            // sizeOfBufferReadin < 16 pad buffer with dfference from 16 
            if (sizeOfBufferReadIn <= 16)
            {
                padBuffer(bufferReadIn, sizeOfBufferReadIn);
            }

            keyAdd(keySchedule, bufferReadIn, 0);

            for (size_t i = 1; i < 10; i++)
            {
                subBytes(bufferReadIn);
                shiftRows(bufferReadIn);
                mixColumns(bufferReadIn);
                keyAdd(keySchedule, bufferReadIn, 4 * i);
            }

            subBytes(bufferReadIn);
            shiftRows(bufferReadIn);
            keyAdd(keySchedule, bufferReadIn, 40);

            // Write encrypted buffer to destination file
            dstFile.write((char*)bufferReadIn, sizeOfBufferReadIn);
        }

        std::cout << std::endl << "*************************** Encryption Done ***************************" << std::endl << std::endl;
        std::cout << "Encrypted File is located at: " << dstFilePath << std::endl;

        //Close files
        srcFile.close();
        dstFile.close();
    }
    else
    {
        std::cout << "Failed to open input file... Exiting program" << std::endl;
        
    }
}