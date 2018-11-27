#include <bitset>
#include <vector>
#include "BitwiseIO.h"
#include "HuffmanBinaryNode.h"


//<summary>
// A record used to both track frequency count and a compressed bit representation
//</summary>
struct ByteRecord {
	int count;
	std::vector<bool> compressedRepresentation;
};
//There are 256 unique bytes, so we can count frequency using an array of numbers of this size
ByteRecord frequencyTable[256];
ByteRecord eofRep;
BitwiseIO* reader;
BitwiseIO* writer;

void LogByteStrings(HuffmanBinaryNode* leaf) {
	if (leaf->IsLeaf() == false)
		return;
	
	HuffmanBinaryNode* pNode = 0;
	HuffmanBinaryNode* cNode = leaf;
	while (cNode->GetParent()) {
		//Move up to the parent of the current node and store the current node as the previous node
		pNode = cNode;
		cNode = cNode->GetParent();
		//At the frequency table for the leaf
		frequencyTable[leaf->GetByte()].compressedRepresentation.push_back(cNode->GetLeft() == pNode);
	}
}

void ReverseWriteABoolVector(BitwiseIO* writer, std::vector<bool> vector) { 
	//Iterate through the compressedRepresentation stored in this bytes record
	std::vector<bool>::iterator i = vector.end();
	while (i != vector.begin()) {
		//Move backwards through the iterator
		--i;
		if (*i) {
			//If it is true, print 1
			writer->WriteBit(1);
		}
		else {
			//Otherwise, print 0
			writer->WriteBit(0);
		}
	} 
}


//<summary>
// Returns the binary form of this node
//</summary>
void PackNodeToBits(HuffmanBinaryNode* node){
	//Write out is leaf as a bit
	writer->WriteBit(node->IsLeaf());
	//write out isEOF as a bit
	writer->WriteBit(node->IsEOF());
	//write out ID as a byte
	writer->WriteByte(node->GetID());
	
	//if isLeaf
	if (node->IsLeaf()) 
		//write out byte representation
		writer->WriteByte(node->GetByte());
	else
		//Write out left child's id as a byte
		writer->WriteByte(node->GetLeft()->GetID());
		//Write out right child's id as a byte
		writer->WriteByte(node->GetRight()->GetID());
}

//<summary>
// Recreates an unfinished node from binary save. The links to children need to be restored after all nodes are read
//</summary>
HuffmanBinaryNode::UnfinishedHuffmanBinaryNode* UnpackFromBits() {
	//Make a new unfinished node
	HuffmanBinaryNode::UnfinishedHuffmanBinaryNode* unfinishedNode = new HuffmanBinaryNode::UnfinishedHuffmanBinaryNode();
	//Read out is leaf as a bit and Make a new node of the appropriate type
	HuffmanBinaryNode* newNode = new HuffmanBinaryNode(reader->ReadBit() > 0);
	//Assign the new new node to unfinished node
	unfinishedNode->node = newNode;
	//Read out isEOF as a bit and Mark EOF
	if (reader->ReadBit() > 0)
		newNode->MarkEOF();
	//Read out ID as a byte and override ID
	newNode->OverrideID(reader->ReadByte());
	//if isLeaf
	if (newNode->IsLeaf()) {
		//Read out byte representation and Set byte representation
		newNode->SetByte(reader->ReadByte());
	}
	else {
		//Read out left child's id as a byte and set left ID
		unfinishedNode->leftID = reader->ReadByte();
		//Read out right child's id as a byte and Set right ID
		unfinishedNode->rightID = reader->ReadByte();
	}
	return unfinishedNode;
}


void Decode(std::string inFileName, std::string outFileName) {
	reader = new BitwiseIO(true, 255, inFileName);
	writer = new BitwiseIO(false, 255, outFileName);
	
	//Get the first node from the file
	HuffmanBinaryNode::UnfinishedHuffmanBinaryNode* unfinishedHead = UnpackFromBits();
	//Create a list of all unfinished nodes
	std::vector<HuffmanBinaryNode::UnfinishedHuffmanBinaryNode*> unfinishedNodes;
	//Add head to it
	unfinishedNodes.push_back(unfinishedHead);
	//The amount we need to read is equal to the first node's id. This is because the head (the first one printed) is the second to last node to be created (EOF is last)
	//We have already read in one node, so the total amount is (head->GetID()+1)-1, which is just head's id
	unsigned int amountToRead = unfinishedHead->node->GetID();
	for (unsigned int i = 0; i < amountToRead; i++) {
		HuffmanBinaryNode::UnfinishedHuffmanBinaryNode* newUHead = UnpackFromBits();
		unfinishedNodes.push_back(newUHead);
	}
	//We have now read all of the nodes we have saved.
	//Now we need to rebuild the tree.
	//We do this by looping through all nodes
	for (std::vector<HuffmanBinaryNode::UnfinishedHuffmanBinaryNode*>::iterator it = unfinishedNodes.begin() ; it != unfinishedNodes.end(); ++it) {
			//If it is a leaf it cannot have children, so continue
			if ((*it)->node->IsLeaf())
				continue;
			else
				//Otherwise loop through all nodes
				for (std::vector<HuffmanBinaryNode::UnfinishedHuffmanBinaryNode*>::iterator jt = unfinishedNodes.begin() ; jt != unfinishedNodes.end(); ++jt)
					//If this node's id is what is supposed to the the firsts left child, assign it as such
					if ((*jt)->node->GetID() == (*it)->leftID)
						(*it)->node->SetLeft((*jt)->node);
					//Or this node's id is what is supposed to the the firsts right child, assign it as such
					else if ((*jt)->node->GetID() == (*it)->rightID)
						(*it)->node->SetRight((*jt)->node);
	}
	//Set head to the node in the unfinished head
	HuffmanBinaryNode* head = unfinishedHead->node;
	
	//Free all the Unfinished pointers
	for (std::vector<HuffmanBinaryNode::UnfinishedHuffmanBinaryNode*>::iterator it = unfinishedNodes.begin() ; it != unfinishedNodes.end(); ++it)
		delete (*it);
	
	//Note: We will never have read in a tree of size 1, since the encode procedure also makes an EOF node. So the following loop cannot get stuck on tree size 1
	HuffmanBinaryNode* cNode = head;
	while (reader->CheckEOF() == false) {
		//If we have found a leaf, we need to print a byte
		if (cNode->IsLeaf()) {
			//if we have found the EOF bit string, break our write loop
			if (cNode->IsEOF())
				break;
			//Otherwise, write the byte this string represented
			writer->WriteByte(cNode->GetByte());
			//Start over at the head
			cNode = head;
		}
		else
			//Otherwise we move to the next node by reading a bit
			//Move to right if the bit is positive, move to left if it is 0
			cNode = (reader->ReadBit()) ? cNode->GetRight() : cNode->GetLeft();
	}
	//Close reader/writer
	reader->Close();
	writer->Close();
	delete reader;
	delete writer;
	//Deleting head causes a cascade of all children to be deleted
	delete head;
}


void Encode(std::string inFileName, std::string outFileName) {
	reader = new BitwiseIO(true, 255, inFileName);
	writer = new BitwiseIO(false, 255, outFileName);
	
	//Read the whole file
	while (reader->CheckEOF() == false) { 
		//Increment the count of this byte
		frequencyTable[reader->ReadByte()].count++;
		//std::cout << reader->CheckEOF() << " || "<<(b>0)<<"\n";
		//writer->WriteByte(b);
	}
	//Rewind the position of the reader
	reader->Rewind();
	
	//Build the Tree
	HuffmanNodePQLow nodePQ;
	//std::vector<HuffmanBinaryNode*> leafNodes;
	unsigned long total = 0;
	for (unsigned int i = 0; i < 256; i++) {
		//If this byte appears in our table as non 0
		if (frequencyTable[i].count) {
			//Debug output the frequency table
			//std::cout << (char)i <<" | "<<std::bitset<8>(i) << " | "<< frequencyTable[i] <<"\n" ;
			HuffmanBinaryNode* newNode = new HuffmanBinaryNode(true);
			newNode->SetByte(i);
			newNode->SetFrequency(frequencyTable[i].count);
			nodePQ.push(newNode);
			//leafNodes.push_back(newNode);
			total += frequencyTable[i].count;
		}
	}
	//Add the EOF character. It is the only character with Frequency of 0, so it will get the worst representation
	{
		HuffmanBinaryNode* newNode = new HuffmanBinaryNode(true);
		newNode->SetByte(0);
		newNode->SetFrequency(0);
		nodePQ.push(newNode);
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
		popNode1->SetParent(newNode);
		popNode2->SetParent(newNode);
		nodePQ.push(newNode);
	}
	HuffmanBinaryNode* head = nodePQ.top();
	nodePQ.pop();
	
	//Do a post order operation on the tree to find leaf nodes and compile their bit representation (in reverse order)
	HuffmanBinaryNode::PostOrderOperation(head, 
		[](HuffmanBinaryNode* node) {
			//Only perform this operation on leaf nodes (excluding the special EOF node)
			if (node->IsLeaf() == false)
				return;
			
			HuffmanBinaryNode* pNode = 0;
			HuffmanBinaryNode* cNode = node;
			while (cNode->GetParent()) {
				//Move up to the parent of the current node and store the current node as the previous node
				pNode = cNode;
				cNode = cNode->GetParent();
				//At the frequency table for the leaf
				if (node->IsEOF())
					eofRep.compressedRepresentation.push_back(cNode->GetRight() == pNode);
				else
					frequencyTable[node->GetByte()].compressedRepresentation.push_back(cNode->GetRight() == pNode);
			}
			/*
			//Print out the representation of this bit in reverse order of the vector (so from top to bottom, the correct way)
			std::vector<bool>::iterator i = frequencyTable[node->GetByte()].compressedRepresentation.end();
			std::cout << "("<<
			((node->IsEOF()) ? (char)255 : (char)node->GetByte())
			<<")" <<std::bitset<8>(node->GetByte()) << " -> ";
			while (i != frequencyTable[node->GetByte()].compressedRepresentation.begin()) {
				 --i;
				if (*i)
					std::cout << "1";
				else 
					std::cout << "0";
			} 
			std::cout << "\n";
			*/
		}
	);
	
	//Write out the tree in depth first, pre order fashion. This is done so that we can use the ID of the head node as a count of the total number of nodes to read in during decode
	HuffmanBinaryNode::PreOrderOperation(head, PackNodeToBits);
	
	//Read through the file again, this time writing out the bits we have calculated
	while (reader->CheckEOF() == false) {
		Byte readByte = reader->ReadByte();
		std::cout << (char)readByte;
		ReverseWriteABoolVector(writer, frequencyTable[readByte].compressedRepresentation);
	}
	std::cout << "\n" ;
	//Write the end of file node
	ReverseWriteABoolVector(writer, eofRep.compressedRepresentation);
	
	std::cout << head->GetFrequency() <<"\n" ;
	
	//Close read/writer now that we are done with them
	reader->Close();
	//Pad to the nearest byte boundary
	writer->Pad();
	writer->Close();
	delete reader;
	delete writer;
	//Deleting head causes a cascade of all children to be deleted
	delete head;
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