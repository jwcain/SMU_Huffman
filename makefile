#Author: Justin Cain @AffinityForFun
CC			= g++
FLAGS		= -Wall -std=c++11


final : encode decode

encode : bitwiseio huffmanencode binarynode
	$(CC) $(FLAGS) HuffmanEncode.o BitwiseIO.o HuffmanBinaryNode.o -o HuffmanEncode

decode : bitwiseio huffmandecode binarynode
	$(CC) $(FLAGS) HuffmanDecode.o BitwiseIO.o HuffmanBinaryNode.o -o HuffmanDecode

huffmanencode : 
	$(CC) $(FLAGS) -c HuffmanEncode.cpp
	
huffmandecode : 
	$(CC) $(FLAGS) -c HuffmanDecode.cpp
	
bitwiseio :
	$(CC) $(FLAGS) -c BitwiseIO.cpp
	
binarynode :
	$(CC) $(FLAGS) -c HuffmanBinaryNode.cpp
	
remake : clear final

clear : clean
	clear
	
clean :
	rm -f ./HuffmanDecode ./HuffmanEncode HuffmanEncode.o HuffmanDecode.o BitwiseIO.o HuffmanBinaryNode.o
	

