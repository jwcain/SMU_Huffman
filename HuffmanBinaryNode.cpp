#include "HuffmanBinaryNode.h"
unsigned int  HuffmanBinaryNode::ID = 0;

//<summary>
// Returns the UID for this node
//</summary>
unsigned int HuffmanBinaryNode::GetID() {
	return id;
}

//<summary>
// Returns if this node is a leaf, containing a bye.
//</summary>
bool HuffmanBinaryNode::IsLeaf(){
	return isLeaf;
}

//<summary>
// Returns the calculated frequency of this bye
//</summary>
unsigned long HuffmanBinaryNode::GetFrequency() const{
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
void HuffmanBinaryNode::SetRight(HuffmanBinaryNode* nodeValue) {
	if (IsLeaf())
		std::cout << "Operation caused a right child node to be set on a leaf\n";
	right = nodeValue;
}
//<summary>
// Sets the  parent node of the node
//</summary>
HuffmanBinaryNode* HuffmanBinaryNode::GetParent() {
	return parent;
}
//<summary>
// Sets the parent node of the node
//</summary>
void HuffmanBinaryNode::SetParent(HuffmanBinaryNode* nodeValue){
	parent = nodeValue;
}

//<summary>
// Constructor.
//</summary>
HuffmanBinaryNode::HuffmanBinaryNode(bool isLeafValue) {
	id = ID++;
	isLeaf = isLeafValue;
	left = 0;
	right = 0;
	parent = 0;
	byte = 0;
	isEOF = false;
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
// Returns if this is the EOF character
//</summary>
bool HuffmanBinaryNode::IsEOF() {
	return isEOF;
}

//<summary>
// Marks this node as representing the EOF character
//</summary>
void HuffmanBinaryNode::MarkEOF() {
	isEOF = true;
}
//<summary>
// Assigns an ID to this node
//</summary>
void HuffmanBinaryNode::OverrideID(unsigned int idValue) {
	id = idValue;
}


//<summary>
// Deconstructor. Deletes the two referenced nodes if they exist
//</summary>
void HuffmanBinaryNode::Print(HuffmanBinaryNode* node) {
	std::cout << "Node " << node->GetID() << "\t(";
	std::cout << "IsLeaf: " << node->IsLeaf();
	std::cout << "\tfreq: " << node->GetFrequency();
	if (node->GetParent())
		std::cout << "\tpar: " << node->GetParent()->GetID();
	if (node->IsLeaf())
		std::cout << "\tbyte: " << (char)node->GetByte();
	else {
		if (node->GetLeft())
			std::cout << "\tleft: " << node->GetLeft()->GetID();
		if (node->GetRight())
			std::cout << "\tright: " << node->GetRight()->GetID();
	}
	std::cout << "\n";
}

//<summary>
// Calls an operation on all nodes in depth first, post order fashion
//</summary>
void HuffmanBinaryNode::PostOrderOperation(HuffmanBinaryNode* head, traversal_operation opr) {
	if (head->IsLeaf() == false) {
		if (head->GetLeft())
			PostOrderOperation(head->GetLeft(), opr);
		if (head->GetRight())
			PostOrderOperation(head->GetRight(), opr);
	}
	opr(head);
}

//<summary>
// Calls an operation on all nodes in depth first, pre order fashion
//</summary>
void HuffmanBinaryNode::PreOrderOperation(HuffmanBinaryNode* head, traversal_operation opr) {
	opr(head);
	if (head->IsLeaf() == false) {
		if (head->GetLeft())
			PostOrderOperation(head->GetLeft(), opr);
		if (head->GetRight())
			PostOrderOperation(head->GetRight(), opr);
	}
}

