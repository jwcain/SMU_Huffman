/*
Author:
	Justin Cain
	@AffinityForFun
	jwcain.github.io
*/

#include "BitwiseIO.h"
// <summary>
// Prepares this BitwiseIO for write
// </summary>
void BitwiseIO::OpenWrite(std::string filename) {
	//Attempt to open the file
	openFile = fopen(filename.c_str(), "w+");
	//Check if we opened a file or caused an error
	if (openFile == NULL || ferror(openFile)) {
		//If we did set the IO break and return
		IOBreakFlag = true;
		return;
	}
	//Set the necessary position within the first byte for writing
	currentBitwiseBytePosition = 7;
}

// <summary>
// Prepares this BitwiseIO for read
// </summary>
void BitwiseIO::OpenRead(std::string filename) {
	//Attempt to open the file
	openFile = fopen(filename.c_str(), "r");
	//Check if we opened a file or caused an error
	if (openFile == NULL || ferror(openFile)) {
		IOBreakFlag = true;
		return;
	}
	//Set the necessary position within the first byte for reading
	currentBitwiseBytePosition = -1;
	//Check to see if the file has contents
	fseek(openFile, 0, SEEK_END);
	if (ftell(openFile) == 0)
		//If it doesn't mark IO as complete.
		IOBreakFlag = true;
	else
		//Otherwise, rewind the file back to start so it can be read properly
		rewind(openFile);
}

// <summary>
// Writes the buffer out to the current file
// </summary>
void BitwiseIO::WriteBufferOut() {
	//Do nothing if there is no data in the buffer
	if (bufferIndex == 0)
		return;
	//Invoke fwrite to write the buffer, with data size of 1, count buffer index, to the open file
	fwrite(ioBuffer, 1, bufferIndex, openFile);

	//If we have hit an error
	if (ferror(openFile)) {
		//Report to user
		std::cout << "Error Writing to file\n";
		//Set IO break flag to true
		IOBreakFlag = true;
	}
}

// <summary>
// Constructor. Opens in read mode if bool is true, write mode if false. Takes io buffer size and a file name to operate on
// </summary>
BitwiseIO::BitwiseIO(bool readMode, unsigned int bufferMaxSizeValue, std::string filename) {
	//Set the ioMode
	ioMode = readMode;
	
	//Set the max buffer size
	bufferMaxSize = bufferMaxSizeValue;
	
	//Create a read buffer of the appropriate size
	ioBuffer = static_cast<Byte*>(malloc(sizeof(Byte) * bufferMaxSize));
	
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
	//If we made a buffer, free it
	if (ioBuffer)
		free(ioBuffer);
}

// <summary>
// Reads a whole byte from read bit.
// </summary>
Byte BitwiseIO::ReadByte() {
	if (IOBreakFlag) {
		std::cout << "Read operation called on IOBreak=true\n";
		return 0;
	}
	if (ioMode == false) {
		std::cout << "Read operation called on write IO\n";
		return 0;
	}
	
	//If the read byte hasn't had a bit read, return the whole byte
	if (currentBitwiseBytePosition == 7) {
		Byte retByte = currentBitwiseOperationByte;
		currentBitwiseOperationByte = ioBuffer[bufferIndex++];
		
		//If we have reached the end of the buffer and not the end of the file
		if (bufferIndex == storedBufferSize && !feof(openFile)) {
			
			//Read more in
			storedBufferSize = fread(ioBuffer, 1, bufferMaxSize, openFile);
			if (ferror(openFile)) {
				std::cout << "Error Reading from file\n";
				IOBreakFlag = true;
				return 0;
			}
			
			//Reset the buffer index
			bufferIndex = 0;
		}
		else if(bufferIndex == storedBufferSize  && feof(openFile)) {
			IOBreakFlag = true;
		}
		
		return retByte;
	}

	//Create a returnByte set to all 0s
	Byte retByte = 0;
	//Read bit 8 times to construct a byte;
	for (short i = 7; i >= 0; i--)
		//If the bit is positive
		if (ReadBit() > 0)
			//Our or return byte with 1 shifted over to the proper position
			retByte = retByte | ( US_1 << i);
		
	return retByte;
}

// <summary>
// Reads a bit
// </summary>
Bit BitwiseIO::ReadBit() {
	if (IOBreakFlag) {
		std::cout << "Read operation called on IOBreak=true\n";
		return 0;
	}
	if (ioMode == false) {
		std::cout << "Read operation called on write IO\n";
		return 0;
	}
	
	
	//If our current read byte has been fully used
	if (currentBitwiseBytePosition < 0) {
		//Load a new  byte
		
		//If we have reached the end of the buffer and not the end of the file
		if (bufferIndex == storedBufferSize && !feof(openFile)) {
			
			//Read more in
			storedBufferSize = fread(ioBuffer, 1, bufferMaxSize, openFile);
			if (ferror(openFile)) {
				std::cout << "Error Reading from file\n";
				IOBreakFlag = true;
				return 0;
			}
			
			//Reset the buffer index
			bufferIndex = 0;
		}
		
		
		//Assign the new byte and increment our index
		currentBitwiseOperationByte = ioBuffer[bufferIndex++];
		//Reset the byte position
		currentBitwiseBytePosition = 7;
	}
	
	//Return if there is a bit in the `currentBitwiseBytePosition` by currentBitwiseOperationByte AND a 1 shifted to the correct position 
	Byte retBit = currentBitwiseOperationByte & ( US_1 << currentBitwiseBytePosition);

	//Move the position we are looking at down
	currentBitwiseBytePosition--;
	
	
	
	//If we are returning the last bit, and we have no more bytes left in the buffer and we are at EOF, mark the IOBreak as true,
	if ( currentBitwiseBytePosition < 0 && bufferIndex == storedBufferSize  && feof(openFile)) {
		IOBreakFlag = true;
	}
	
	return retBit;
}

// <summary>
// Writes a whole byte to the buffer
// </summary>
void BitwiseIO::WriteByte(Byte byte) {
	if (ioMode) {
		std::cout << "Write operation called on read IO\n";
		return;
	}
	
	//Loop through this byte.
	for (short i = 7; i >= 0; i--)
		//If the bit is positive at this position
		if (byte & ( US_1 << i))
			//Write a positive bit
			WriteBit(1);
		else
			//Write a negative bit
			WriteBit(0);
}

// <summary>
// Writes a bit
// </summary>
void BitwiseIO::WriteBit(Bit bit) {
	if (ioMode) {
		std::cout << "Write operation called on read IO\n";
		return;
	}
	
	//Check if this bit is supposed to be set to true
	if (bit)
		//Write this bit to the proper position by taking
		//currentBitwiseOperationByte OR 1 shifted to the current write position
		currentBitwiseOperationByte = currentBitwiseOperationByte | ( US_1 << currentBitwiseBytePosition);
		
		
	//Move the current write position down.
	currentBitwiseBytePosition--;
	
	
	//Check if our current byte is full
	if (currentBitwiseBytePosition == -1) {
		//If it is, assign the current byte to our buffer
		ioBuffer[bufferIndex++] = currentBitwiseOperationByte;
		
		//If we have reached the end of the buffer
		if (bufferIndex == bufferMaxSize) {
			//Write the buffer out
			WriteBufferOut();
			//Reset the buffer index
			bufferIndex = 0;
		}
		//Reset the byte
		currentBitwiseOperationByte = 0;
		//Reset the byte position
		currentBitwiseBytePosition = 7;
	}
}

// <summary>
// reads out the 'amount' rightmost bits from input
// </summary>
unsigned short BitwiseIO::FlexRead(short amount) {
	//Compile our result into one vlaue
	unsigned short retValue = 0;
	//Read in this amount of bits
	for (short i = amount; i >= 0; i--)
		//If we have read a positve bit
		if (ReadBit())
			//Or our return value with a 1 shifted to this position
			retValue = retValue | (US_1 << i);
			
	return retValue;
}

// <summary>
// Writs out the 'amount' rightmost bits of the input
// </summary>
void BitwiseIO::FlexWrite(short amount, unsigned short data) {
	//Write in this amount of bits
	for (short i = amount; i >= 0; i--)
		//If there is a positive bit in this position
		if (data & (US_1 << i))
			//Write a positive bit
			WriteBit(1);
		else
			//Write a negative bit
			WriteBit(0);
}


// <summary>
// Checks if we have reached an IOBreakFlag
// </summary>
bool BitwiseIO::CheckEOF() {
	return IOBreakFlag;
}

// <summary>
// Rewinds the open file
// </summary>
void BitwiseIO::Rewind() {
	//Rewind the file
	rewind(openFile);
	
	//Reset the IO break flag
	IOBreakFlag = false;
	
	//Reset the buffer index
	bufferIndex = 0;
	//Reset the stored buffer size
	storedBufferSize = 0;
	//Place the bitwise position in the correct spot for the ioMode
	currentBitwiseBytePosition = (ioMode) ? -1 : 7;
	
	//Check to see if we need to set IO break flag to true because the file is empty
	fseek(openFile, 0, SEEK_END);
	if (ftell(openFile) == 0) 
		IOBreakFlag = true;
	else
		rewind(openFile);
}




// <summary>
// Closes the open file
// </summary>
void BitwiseIO::Close() {
	//If this was a writer
	if (ioMode == false) {
		//And we have extra bits in our current byte that have not been placed into the buffer
		if (currentBitwiseBytePosition != 7) {
			//Pad the byte to 0
			Pad();
			//Write that byte out
			currentBitwiseOperationByte = ioBuffer[bufferIndex++];
		}
		//If we have written a byte to the buffer, but not sent it out to the file
		if (bufferIndex != 0) {
			//Write the buffer to the file
			WriteBufferOut();
		}
		//Flush the file
		fflush(openFile);
	}
	
	//Close the file
	fclose(openFile);
}

// <summary>
// //Pad current bitwise byte with 0 bits until the byte is full
// </summary>
void BitwiseIO::Pad() {
	if (ioMode) {
		std::cout << "Write operation called on read IO\n";
		return;
	}
	//Pad with 0 bits until the current byte is full
	while (currentBitwiseBytePosition != 7) WriteBit(0);
}