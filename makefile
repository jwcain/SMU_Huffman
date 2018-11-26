#Author: Justin Cain @AffinityForFun
CC			= g++
FLAGS		= -Wall -std=c++11


final : bitwiseio huffman binarynode
	$(CC) $(FLAGS) Huffman.o BitwiseIO.o HuffmanBinaryNode.o -o Huffman

huffman : 
	$(CC) $(FLAGS) -c Huffman.cpp
	
bitwiseio :
	$(CC) $(FLAGS) -c BitwiseIO.cpp
	
binarynode :
	$(CC) $(FLAGS) -c HuffmanBinaryNode.cpp
	
remake : clear final

clear : clean
	clear
	
clean :
	rm -f ./Huffman Huffman.o BitwiseIO.o HuffmanBinaryNode.o
	

