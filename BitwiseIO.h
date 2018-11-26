#ifndef BITWISE_IO_H
#define BITWISE_IO_H

#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <string>

class BitwiseIO {
private:
	FILE* openFile = NULL;
	bool ioMode;

	unsigned int bufferMaxSize;
	unsigned short* ioBuffer;
	unsigned int storedBufferSize = 0;
	unsigned int bufferIndex = 0;
	unsigned short currentBitwiseOperationByte = 0;
	int currentBitwiseBytePosition;
	bool IOBreakFlag = false;
	bool IOERRFlag = false;

	const unsigned short US_1 = 1;
	
	void OpenWrite(std::string filename);
	void OpenRead(std::string filename);
public:
	//Read if true, write if false
	BitwiseIO(bool readMode, unsigned int bufferMaxSizeValue, std::string filename);
	~BitwiseIO();
	
	unsigned short readByte();
	unsigned short readBit();
	
	void writeByte(unsigned short byte);
	void writeBit(unsigned short bit);
	
	void EOF();
	void Rewind();
	void Close();
	void Pad();
};


#endif