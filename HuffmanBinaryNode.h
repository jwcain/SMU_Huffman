/*
Author:
	Justin Cain
	@AffinityForFun
	jwcain.github.io
*/

#ifndef HUFFMAN_BINARY_NODE_H
#define HUFFMAN_BINARY_NODE_H

#include <iostream>
#include <queue>


//<summary>
// Represents a node for the Huffman frequency tree calculation.
//</summary>
class HuffmanBinaryNode {
private:
	//Tracks if this node is a leaf
	bool isLeaf;
	//Tracks if this node is the EOF node
	bool isEOF;
	//Tracks the byte representation of a leaf node
	unsigned char byte;
	//Tracks the left child of a branch node 
	HuffmanBinaryNode* left;
	//Tracks the right child of a branch node 
	HuffmanBinaryNode* right;
	//Tracks the parent of the node
	HuffmanBinaryNode* parent;
	//Tracks the frequency of the node (for a branch, it is the sum of its children)
	unsigned long frequency;
	//The UID of this node, It is automatically assigned during instantiation
	unsigned short id; 
	
	
	//A static tracker for UID assignment. Also serves as total count of nodes
	static unsigned short ID;
public:
	//Create a struct that stores an unfinished recreation of a node from file. It stores the partially set up node and the IDs of nodes it should be linked to 
	struct UnfinishedHuffmanBinaryNode {
		HuffmanBinaryNode* node;
		unsigned short leftID;
		unsigned short rightID;
	};

	//A traversal operation is a function pointer used to allow for a method to be called on all nodes
	//across a traversal. The method is called per node in order
	typedef void (*traversal_operation)(HuffmanBinaryNode* node);
	
	//Method descriptions are maintained in the cpp file
	
	unsigned short GetID();
	bool IsLeaf();
	unsigned long GetFrequency() const;
	void SetFrequency(unsigned long frequencyValue);
	unsigned char GetByte();
	void SetByte(unsigned char byteValue);
	HuffmanBinaryNode* GetLeft();
	void SetLeft(HuffmanBinaryNode* nodeValue);
	HuffmanBinaryNode* GetRight();
	void SetRight(HuffmanBinaryNode* nodeValue);
	HuffmanBinaryNode* GetParent();
	void SetParent(HuffmanBinaryNode* nodeValue);
	HuffmanBinaryNode(bool isLeafValue);
	~HuffmanBinaryNode();
	bool IsEOF();
	void MarkEOF();
	void OverrideID(unsigned short idValue);
	
	static void Print(HuffmanBinaryNode* node);
	static void PostOrderOperation(HuffmanBinaryNode* head, traversal_operation opr);
	static void PreOrderOperation(HuffmanBinaryNode* head, traversal_operation opr);
	static void InOrderOperation(HuffmanBinaryNode* head, traversal_operation opr);
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

//Declare PQ aliases for use in constructing a human tree
typedef std::priority_queue<HuffmanBinaryNode*,std::vector<HuffmanBinaryNode*>,CompareHuffmanBinaryNodeHigh> HuffmanNodePQHigh;
typedef std::priority_queue<HuffmanBinaryNode*,std::vector<HuffmanBinaryNode*>,CompareHuffmanBinaryNodeLow> HuffmanNodePQLow;

#endif