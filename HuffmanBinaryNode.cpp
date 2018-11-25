#include "HuffmanBinaryNode.h"

//<summary>
// Returns if this node is a leaf, containing a bye.
//</summary>
bool HuffmanBinaryNode::IsLeaf(){
	return isLeaf;
}

//<summary>
// Returns the calculated frequency of this bye
//</summary>
unsigned long HuffmanBinaryNode::GetFrequency(){
	return frequency;
}

//<summary>
// Sets the calculated frequency of this bye
//</summary>
void HuffmanBinaryNode::SetFrequency(unsigned long frequencyValue) {
	frequency = frequencyValue;
}

//<summary>
// Returns the byte of this node
//</summary>
unsigned char HuffmanBinaryNode::GetByte(){
	if (IsLeaf() == false)
		std::cout << "Operation accessed a byte on a branch node\n";
	return byte;
}

//<summary>
// Sets the byte of this node
//</summary>
void HuffmanBinaryNode::SetByte(unsigned char byteValue){
	if (IsLeaf() == false)
		std::cout << "Operation set a byte on a branch node\n";
	byte = byteValue;
}

//<summary>
// Returns the left child node of the node
//</summary>
HuffmanBinaryNode* HuffmanBinaryNode::GetLeft(){
	if (IsLeaf())
		std::cout << "Operation accessed a left child node t on a leaf\n";
	return left;
}

//<summary>
// Sets the left child node of the node
//</summary>
void HuffmanBinaryNode::SetLeft(HuffmanBinaryNode* nodeValue){
	if (IsLeaf())
		std::cout << "Operation caused a left child node to be set on a leaf\n";
	left = nodeValue;
}

//<summary>
// Returns the right child node of the node
//</summary>
HuffmanBinaryNode* HuffmanBinaryNode::GetRight(){
	if (IsLeaf())
		std::cout << "Operation accessed a right child node t on a leaf\n";
	return right;
}

//<summary>
// Sets the right child node of the node
//</summary>
void HuffmanBinaryNode::SetRight(HuffmanBinaryNode* nodeValue){
	if (IsLeaf())
		std::cout << "Operation caused a right child node to be set on a leaf\n";
	right = nodeValue;
}

//<summary>
// Constructor.
//</summary>
HuffmanBinaryNode::HuffmanBinaryNode(bool isLeafValue) {
	isLeaf = isLeafValue;
	left = 0;
	right = 0;
}

//<summary>
// Deconstructor. Deletes the two referenced nodes if they exist
//</summary>
HuffmanBinaryNode::~HuffmanBinaryNode() {
	if (left)
		delete left;
	if (right)
		delete right;
}

//<summary>
// Returns the binary form of this node
//</summary>
std::vector<int> HuffmanBinaryNode::Pack(HuffmanBinaryNode* node){
	std::vector<int> ret;
	return ret;
}

//<summary>
// Recreates a node from binary save
//</summary>
HuffmanBinaryNode* HuffmanBinaryNode::Unpack(std::vector<int> n){
	return 0;
}

//<summary>
// 
//</summary>
void HuffmanBinaryNode::PostOrderOperation(HuffmanBinaryNode* head, traversal_operation opr){
	
}

