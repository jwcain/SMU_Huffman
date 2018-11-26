#include "BitwiseIO.h"
// <summary>
// Prepares this BitwiseIO for write
// </summary>
void BitwiseIO::OpenWrite(std::string filename) {
	openFile = fopen(filename, "w+");
	currentBitwiseBytePosition = 7;
}

// <summary>
// Prepares this BitwiseIO for read
// </summary>
void BitwiseIO::OpenRead(std::string filename) {
	openFile = fopen(filename, "r");
	currentBitwiseBytePosition = -1;
	//Check to see if the file has contents, and if it doesn't mark IO as complete. Otherwise, rewind the file back to start so it can be read properly
	fseek(openFile, 0, SEEK_END);
	if (ftell(openFile) > 0) 
		IOBreakFlag = true;
	else
		rewind(openFile);
}

// <summary>
// Constructor. Opens in read mode if bool is true, write mode if false. Takes io buffer size and a file name to operate on
// </summary>
BitwiseIO::BitwiseIO(bool readMode, unsigned int bufferMaxSizeValue, std::string filename) {
	ioMode = readMode;
	bufferMaxSize = bufferMaxSizeValue;
	//Create a read buffer of the appropriate size
	ioBuffer = malloc(sizeof(unsigned short) * bufferMaxSize); //sizeof is unnecessary since sizeof unsigned short is 1, but it is there for clarity
	
	//Open the file in the proper mode
	if (ioMode)
		OpenRead(filename);
	else
		OpenWrite(filename);
}

// <summary>
// Deconstructor
// </summary>
BitwiseIO::~BitwiseIO() {
	if (readBuffer)
		free(readBuffer);
}

// <summary>
// Reads a whole byte from read bit. If the stored byte has been untouched yet, it just returns that.
// </summary>
unsigned short BitwiseIO::readByte() {
	if (IOBreakFlag)
		return 0;
	if (ioMode == false) {
		std::cout << "Read operation called on write IO\n";
		return 0;
	}
	//If we are about to return the last byte and we have reached EOF, mark IOBreak as true.
	//In the case of the first read, index 0 will be compared to -1 and this flag will not be set,
	//We do not have to worry about the case of an empty file since that is handled on open.
	if (bufferIndex == storedBufferSize - 1 && feof (openFile))
		IOBreakFlag = true;
	
	//If our current read byte has been fully used
	if (currentBitwiseBytePosition == -1) {
		//Load a new  byte
		
		//If we have reached the end of the buffer
		if (bufferIndex == storedBufferSize) {
			//Read more in
			storedBufferSize = fread((void*)ioBuffer, 1, bufferMaxSize, openFile);
			//Reset the buffer index
			bufferIndex = 0;
		}
		//Assign the new byte and increment our index
		currentBitwiseOperationByte = ioBuffer[bufferIndex++];
		//Reset the byte position
		currentBitwiseBytePosition = 7;
	}
	//If our Bitwise byte is a full byte
	if (currentBitwiseBytePosition == 7) {
		//Mark it as fully consumed
		currentBitwiseBytePosition = -1
		//And return it
		return currentBitwiseOperationByte;
	}
	
	unsigned short retByte = 0;
	//If we have made it this far, we have to readbit 8 times to construct a byte;
	for (short i = 7; i >= 0; i--)
		//If the bit is positive
		if (readBit() > 0)
			//Our or return byte with 1 shifted over to the proper position
			retByte = retByte | ( US_1 << i);
		
	
	
	return retByte;
}

// <summary>
// Reads a bit
// </summary>
unsigned short BitwiseIO::readBit() {
	if (IOBreakFlag)
		return 0;
	if (ioMode == false) {
		std::cout << "Read operation called on write IO\n";
		return 0;
	}
	//If our current stored bitwise byte is empty, get a new byte
	if (currentBitwiseBytePosition = -1)
		currentBitwiseOperationByte = readByte();
	
	//Return if there is a bit in the `currentBitwiseBytePosition` by currentBitwiseOperationByte AND a 1 shifted to the correct position 
	unsigned short retBit = currentBitwiseOperationByte & ( US_1 << currentBitwiseBytePosition);
	//Move the position we are looking at down
	currentBitwiseBytePosition--;
	return retBit;
}

// <summary>
// Writes a whole byte to the buffer
// </summary>
void BitwiseIO::writeByte(unsigned short byte) {
	if (ioMode) {
		std::cout << "Write operation called on read IO\n";
		return;
	}
	//Loop through this byte.
	for (short i = 7; i >= 0; i--)
		//If the bit is positive at this position
		if (byte & ( US_1 << i))
			//Write a positive bit
			writeBit(1);
		else
			//Write a negative bit
			writeBit(0);
}

// <summary>
// Writes a bit
// </summary>
void BitwiseIO::writeBit(unsigned short bit) {
	if (ioMode) {
		std::cout << "Write operation called on read IO\n";
		return;
	}
	//Check if our current byte is full
	if (currentBitwiseBytePosition == -1) {
		//If it is, assign the current byte to our buffer
		ioBuffer[bufferIndex++] = currentBitwiseOperationByte;
		
		//If we have reached the end of the buffer
		if (bufferIndex == bufferMaxSize) {
			//Write the buffer out
			fwrite((void*)ioBuffer, 1, bufferIndex, openFile);
			//Reset the buffer index
			bufferIndex = 0;
		}
		
		//Reset the byte
		currentBitwiseOperationByte = 0;
		//Reset the byte position
		currentBitwiseBytePosition = 7;
	}
	//Write this bit to the proper position by taking
	//currentBitwiseOperationByte OR 1 shifted to the current write position
	currentBitwiseOperationByte = currentBitwiseOperationByte | ( US_1 << currentBitwiseBytePosition);
	//Move the current write position down.
	currentBitwiseBytePosition--;
}

void BitwiseIO::EOF() {
	return IOBreakFlag || IOERRFlag;
}

// <summary>
// Rewinds the open file
// </summary>
void BitwiseIO::Rewind() {
	rewind(openFile);
}

// <summary>
// Closes the open file
// </summary>
void BitwiseIO::Close() {
	fclose(rewind);
}

// <summary>
// //Pad current bitwise byte with 0 bits until the byte is full
// </summary>
void BitwiseIO::Pad() {
	if (ioMode) {
		std::cout << "Write operation called on read IO\n";
		return 0;
	}
	//Pad with 0 bits until the current byte is full
	while (currentBitwiseBytePosition != 7) writeBit(1);
}