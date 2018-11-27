#ifndef BITWISE_IO_H
#define BITWISE_IO_H

#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <string>


using Byte = unsigned char;
using Bit = unsigned char;

class BitwiseIO {
private:
	FILE* openFile = NULL;
	bool ioMode;

	unsigned int bufferMaxSize;
	Byte* ioBuffer;
	unsigned int storedBufferSize = 0;
	unsigned int bufferIndex = 0;
	Byte currentBitwiseOperationByte = 0;
	int currentBitwiseBytePosition;
	bool IOBreakFlag = false;
	bool IOERRFlag = false;

	const Byte US_1 = 1;
	
	void OpenWrite(std::string filename);
	void OpenRead(std::string filename);
	void WriteBufferOut();
public:
	//Read if true, write if false
	BitwiseIO(bool readMode, unsigned int bufferMaxSizeValue, std::string filename);
	~BitwiseIO();
	
	Byte ReadByte();
	Bit ReadBit();
	
	void WriteByte(Byte byte);
	void WriteBit(Bit bit);
	
	bool CheckEOF();
	void Rewind();
	void Close();
	void Pad();
};


#endif