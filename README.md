# SMU Assignment 2 - Huffman encoding
## AUTHOR
- Justin W. Cain 
- @AffinityForFun
- https://www.affinityforfun.com
- jwcain@mtu.edu

## TIMELINE
- Init creation 		- 11/25/18
- Finished with bugs 	- 11/26/18
- Finished		- 11/27/18

## PURPOSE
This project is assignment 2 for the SMU Masters of Interactive Technology application process. It is a Huffman compression implementation. I attempted this assignment feeling that my portfolio lacked good C++ projects. I decided if this assignment is valuable to SMU Guildhall's application process, then it is a worthwhile addition to my portfolio.
	
## PROCESS
It had been a while since I last attempted Huffman Compression, with this as my first time doing byte-compression instead of text-compression (compressing words into small strings of characters). Generally, I followed this process:

- Gather information.
- Attempt process manually.
- Code a prototype.
- Refactor design based on knowledge gained from the prototype.
- Iterate on the design until it is fully polished.

I utilized the assignment description, my most recent Huffman compression project, and a C assignment I had complete in college that contained code for bit-level IO operations.

20190624_221043.jpg
You can see in my ever-present programming notebook that I spent time calculating the best way to store the Huffman tree inside the compressed file.

There, I am debating two options; one of which is a mistake. I am remembering a method for saving tree nodes in an array, but I eventually realize the process only works for balanced, binary trees. I decide on a fixed-size format for saving nodes, saving child-IDs or original byte data in the appropriate context.

Now confident with my process, I prioritize creating the data-structures for the program; compression, decompression, and IO operations use these data structures, making them the core coupling point for the program.

## PROJECT STRUCTURE
Written in c++ standard 11, utilizing standard library string and IO
Included files "BitwiseIO.cpp", "BitwiseIO.h", "Huffman.cpp". "HuffmanBinaryNode.cpp", 
"HuffmanBinaryNode.n" and "makefile"
All code is stored in root directory of project
The main method for execution is located in Huffman.cpp
A Makefile is provided to compile the program.
The program is compiled to "Huffman"
Arguments are taken from the command line, no other user input is taken

## USAGE
```
	Huffman <encode/decode> <InputFileName> <OutputFileName>
		Encode/decode selects that mode for execution
		InputFileName is the target file for encoding/decoding
		OutputFileName is the target output file and will be created/truncated
```

## TEST DATA
	Deflation is the percentage remaining of original size.
	Empty File:
		Regular:	0
		Compressed:	0 (not ran, execution terminated early due to file size of 0)
		Deflation:	?%
	Small text file:
		Regular:	744
		Compressed:	650
		Deflation:	87.37%
	1MB:
		Regular:	1572864
		Compressed:	1521367
		Deflation:	96.72%
	10MB:
		Regular:	11567104
		Compressed:	10982516
		Deflation:	94.95%
	137MB:
		Regular:	143818752
		Compressed:	136353291
		Deflation:	94.81%
		
		
