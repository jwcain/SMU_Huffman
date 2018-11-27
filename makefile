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

test : 
	./Huffman encode input/readable.test TESTING_OUTPUT.OUTPUT
	#diff input/readable.test TESTING_OUTPUT.OUTPUT
	rm TESTING_OUTPUT.OUTPUT
	
testmore : 
	./Huffman encode input/readable.test TESTING_OUTPUT.OUTPUT
	diff input/readable.test TESTING_OUTPUT.OUTPUT
	./Huffman encode input/empty.test TESTING_OUTPUT.OUTPUT
	diff input/empty.test TESTING_OUTPUT.OUTPUT
	./Huffman encode input/10MBData.test TESTING_OUTPUT.OUTPUT
	diff input/100MBData.test TESTING_OUTPUT.OUTPUT
	rm TESTING_OUTPUT.OUTPUT
	