#ifndef HUFFMAN_BINARY_NODE_H
#define HUFFMAN_BINARY_NODE_H

#include <vector>
#include <iostream>

class HuffmanBinaryNode {
private:
	bool isLeaf;
	unsigned char byte;
	HuffmanBinaryNode* left;
	HuffmanBinaryNode* right;
	unsigned long frequency;
public:
	//A traversal operation is a function pointer used to allow for a method to be called on all nodes
	//across a traversal. The method is called per node in order
	typedef void (*traversal_operation)(HuffmanBinaryNode* node);

	bool IsLeaf();
	unsigned long GetFrequency();
	void SetFrequency(unsigned long frequencyValue);
	unsigned char GetByte();
	void SetByte(unsigned char byteValue);
	HuffmanBinaryNode* GetLeft();
	void SetLeft(HuffmanBinaryNode* nodeValue);
	HuffmanBinaryNode* GetRight();
	void SetRight(HuffmanBinaryNode* nodeValue);
	//Override the < operation to check frequency
	bool operator<(const HuffmanBinaryNode& rhs) {return this->frequency < rhs.frequency;}
	HuffmanBinaryNode(bool isLeafValue);
	~HuffmanBinaryNode();
	
	static std::vector<int> Pack(HuffmanBinaryNode* node);
	static HuffmanBinaryNode* Unpack(std::vector<int> n);
	static void PostOrderOperation(HuffmanBinaryNode* head, traversal_operation opr);
};




#endif