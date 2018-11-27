#ifndef HUFFMAN_BINARY_NODE_H
#define HUFFMAN_BINARY_NODE_H

#include <vector>
#include <iostream>
#include <queue>



//<summary>
// Represents a node for the Huffman frequency tree calculation.
//</summary>
class HuffmanBinaryNode {
private:
	bool isLeaf;
	unsigned char byte;
	HuffmanBinaryNode* left;
	HuffmanBinaryNode* right;
	unsigned long frequency;
	int id;
	
	static int ID;
public:
	//A traversal operation is a function pointer used to allow for a method to be called on all nodes
	//across a traversal. The method is called per node in order
	typedef void (*traversal_operation)(HuffmanBinaryNode* node);
	int GetID();
	bool IsLeaf();
	unsigned long GetFrequency() const;
	void SetFrequency(unsigned long frequencyValue);
	unsigned char GetByte();
	void SetByte(unsigned char byteValue);
	HuffmanBinaryNode* GetLeft();
	void SetLeft(HuffmanBinaryNode* nodeValue);
	HuffmanBinaryNode* GetRight();
	void SetRight(HuffmanBinaryNode* nodeValue);
	HuffmanBinaryNode(bool isLeafValue);
	~HuffmanBinaryNode();
	
	static void Print(HuffmanBinaryNode* node);
	static std::vector<int> Pack(HuffmanBinaryNode* node);
	static HuffmanBinaryNode* Unpack(std::vector<int> n);
	static void PostOrderOperation(HuffmanBinaryNode* head, traversal_operation opr);
};

//Create a struct that compares HuffmanNodes. Used for sorting in a priority_queue for highest frequency
struct CompareHuffmanBinaryNodeHigh {
	bool operator()(const HuffmanBinaryNode* lhs, const HuffmanBinaryNode* rhs) const {
		return lhs->GetFrequency() < rhs->GetFrequency();
	}
};

//Create a struct that compares HuffmanNodes. Used for sorting in a priority_queue for lowest frequency
struct CompareHuffmanBinaryNodeLow {
	bool operator()(const HuffmanBinaryNode* lhs, const HuffmanBinaryNode* rhs) const {
		return lhs->GetFrequency() > rhs->GetFrequency();
	}
};

//Declare a PQ alias for use in constructing the human tree
typedef std::priority_queue<HuffmanBinaryNode*,std::vector<HuffmanBinaryNode*>,CompareHuffmanBinaryNodeHigh> HuffmanNodePQHigh;
typedef std::priority_queue<HuffmanBinaryNode*,std::vector<HuffmanBinaryNode*>,CompareHuffmanBinaryNodeLow> HuffmanNodePQLow;

#endif