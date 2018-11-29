/*
Author:
	Justin Cain
	@AffinityForFun
	jwcain.github.io
*/

#ifndef BITWISE_IO_H
#define BITWISE_IO_H

#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <string>

//Create aliases for Byte and Bit to allow for better clarity during operations
using Byte = unsigned char;
using Bit = unsigned char;

// <summary>
// A class that opens a file and manages bitwise IO operations
// </summary>
class BitwiseIO {
private:
	//The current open file
	FILE* openFile = NULL;
	//The ioMode this was instantiated as (true for read)
	bool ioMode;

	//The buffer size used for IO operations
	unsigned int bufferMaxSize;
	//The stored buffer of bytes
	Byte* ioBuffer;
	//The actual amount of bytes stored in the buffer
	unsigned int storedBufferSize = 0;
	//The current index within the buffer
	unsigned int bufferIndex = 0;
	//The current byte being consumed by bytewise operations
	Byte currentBitwiseOperationByte = 0;
	//The position within the byte being consumed by bitwise operations
	int currentBitwiseBytePosition;
	//A flag set when we have reached end of operation
	bool IOBreakFlag = false;

	//A constant reference to the number 1, used in shifting operations
	const Byte US_1 = 1;
	
	//Method definitions are maintained in the .cpp file
	void OpenWrite(std::string filename);
	void OpenRead(std::string filename);
	void WriteBufferOut();
public:
	
	BitwiseIO(bool readMode, unsigned int bufferMaxSizeValue, std::string filename);
	~BitwiseIO();
	
	Byte ReadByte();
	Bit ReadBit();
	
	void WriteByte(Byte byte);
	void WriteBit(Bit bit);
	
	unsigned short FlexRead(short amount);
	void FlexWrite(short amount, unsigned short data);
	
	bool CheckEOF();
	void Rewind();
	void Close();
	void Pad();
};


#endif