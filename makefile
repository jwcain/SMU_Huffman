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
	rm -f ./Huffman Huffman.o BitwiseIO.o HuffmanBinaryNode.o TESTING_OUTPUT_ENCODE.OUTPUT TESTING_OUTPUT_DECODE.OUTPUT

test : 
	./Huffman encode input/readable.test TESTING_OUTPUT_ENCODE.OUTPUT
	./Huffman decode TESTING_OUTPUT_ENCODE.OUTPUT TESTING_OUTPUT_DECODE.OUTPUT
	diff input/readable.test TESTING_OUTPUT_DECODE.OUTPUT
	rm TESTING_OUTPUT_ENCODE.OUTPUT TESTING_OUTPUT_DECODE.OUTPUT
	
	
testfake : 	
	./Huffman encode notreal.input TESTING_OUTPUT_ENCODE.OUTPUT
	./Huffman decode input/readable.test TESTING_OUTPUT_DECODE.OUTPUT
	rm TESTING_OUTPUT_ENCODE.OUTPUT TESTING_OUTPUT_DECODE.OUTPUT
	
testmore : 
	./Huffman encode input/empty.test TESTING_OUTPUT_ENCODE.OUTPUT
	./Huffman decode TESTING_OUTPUT_ENCODE.OUTPUT TESTING_OUTPUT_DECODE.OUTPUT
	diff input/empty.test TESTING_OUTPUT_DECODE.OUTPUT
	
	./Huffman encode input/1MBData.test TESTING_OUTPUT_ENCODE.OUTPUT
	./Huffman decode TESTING_OUTPUT_ENCODE.OUTPUT TESTING_OUTPUT_DECODE.OUTPUT
	diff input/1MBData.test TESTING_OUTPUT_DECODE.OUTPUT
	
	./Huffman encode input/10MBData.test TESTING_OUTPUT_ENCODE.OUTPUT
	./Huffman decode TESTING_OUTPUT_ENCODE.OUTPUT TESTING_OUTPUT_DECODE.OUTPUT
	diff input/10MBData.test TESTING_OUTPUT_DECODE.OUTPUT
	
	./Huffman encode input/100MBData.test TESTING_OUTPUT_ENCODE.OUTPUT
	./Huffman decode TESTING_OUTPUT_ENCODE.OUTPUT TESTING_OUTPUT_DECODE.OUTPUT
	diff input/100MBData.test TESTING_OUTPUT_DECODE.OUTPUT
	rm TESTING_OUTPUT_ENCODE.OUTPUT TESTING_OUTPUT_DECODE.OUTPUT
	
testlarge : 
	./Huffman encode input/1GBData.test TESTING_OUTPUT_ENCODE.OUTPUT
	./Huffman decode TESTING_OUTPUT_ENCODE.OUTPUT TESTING_OUTPUT_DECODE.OUTPUT
	diff input/1GBData.test TESTING_OUTPUT_DECODE.OUTPUT
	rm TESTING_OUTPUT_ENCODE.OUTPUT TESTING_OUTPUT_DECODE.OUTPUT
	
	