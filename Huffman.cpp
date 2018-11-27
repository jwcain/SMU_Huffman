#include <bitset>
#include "BitwiseIO.h"
#include "HuffmanBinaryNode.h"

void Encode(std::string inFileName, std::string outFileName) {
	BitwiseIO* reader = new BitwiseIO(true, 255, inFileName);
	BitwiseIO* writer = new BitwiseIO(false, 255, outFileName);
	//There are 256 unique bytes, so we can count frequency using an array of numbers of this size
	unsigned long frequencyTable[256];
	//Initialize the array to 0
	for (unsigned int i = 0; i < 256; i++) {
		frequencyTable[i] = 0;
	}
	
	//Read the whole file
	while (reader->CheckEOF() == false) { 
		//Increment the count of this byte
		frequencyTable[reader->ReadByte()]++;
		//std::cout << reader->CheckEOF() << " || "<<(b>0)<<"\n";
		//writer->WriteByte(b);
	}
	//Rewind the position of the reader
	reader->Rewind();
	
	//Build the Tree
	HuffmanNodePQLow nodePQ;
	unsigned long total = 0;
	for (unsigned int i = 0; i < 256; i++) {
		//If this byte appears in our table as non 0
		if (frequencyTable[i]) {
			//Debug output the frequency table
			//std::cout << std::bitset<8>(i) << " | "<< frequencyTable[i] <<"\n" ;
			HuffmanBinaryNode* newNode = new HuffmanBinaryNode(true);
			newNode->SetByte(i);
			newNode->SetFrequency(frequencyTable[i]);
			nodePQ.push(newNode);
			total += frequencyTable[i];
		}
	}

	while (nodePQ.size() > 1) {
		HuffmanBinaryNode* popNode1 = nodePQ.top();
		nodePQ.pop();
		HuffmanBinaryNode* popNode2 = nodePQ.top();
		nodePQ.pop();
		
		HuffmanBinaryNode* newNode = new HuffmanBinaryNode(false);
		newNode->SetLeft(popNode1);
		newNode->SetRight(popNode2);
		newNode->SetFrequency(popNode1->GetFrequency() + popNode2->GetFrequency());
		nodePQ.push(newNode);
	}
	HuffmanBinaryNode* head = nodePQ.top();
	nodePQ.pop();
	
	//Print out the completed tree
	HuffmanBinaryNode::PostOrderOperation(head, HuffmanBinaryNode::Print);
	
	std::cout << head->GetFrequency() <<"\n" ;
	reader->Close();
	writer->Close();
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
	std::string outFileName = argv[3];
	if (mode == "encode")
		Encode(inFileName, outFileName);
	else if (mode == "decode")
		Decode(inFileName, outFileName);
	else
		std::cout << "Malformed input: Huffman <encode/decode> <InputFileName> <OutputFileName>\n";

	
	return 0;
}