#include "BitwiseIO.h"
#include "HuffmanBinaryNode.h"


void Encode(std::string inFileName, std::string outFileName) {
	
}


void Decode(std::string inFileName, std::string outFileName) {
	
}



int main(int argc, char** argv) {
	if (argc < 3) {
		//Report to the user that they have incorrect input.
		std::cout << "Malformed input: Huffman <encode/decode> <InputFileName> <OutputFileName>\n";
		return 0;
	}
	//Store the file names for our IO methods.
	std::string mode = argv[1];
	std::string inFileName = argv[2];
	std::string outFileName = argv[2];
	if (mode == "encode")
		Encode(inFileName, outFileName);
	else if (mode == "decode")
		Decode(inFileName, outFileName);
	else
		std::cout << "Malformed input: Huffman <encode/decode> <InputFileName> <OutputFileName>\n";

	
	return 0;
}