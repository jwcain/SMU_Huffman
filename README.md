# SMU Assignment 2 - Huffman Compression/Decompression
## ## [Assingmnent Details](https://www.smu.edu/-/media/Site/guildhallOLD/Documents/Huffman_Exercise.pdf?la=en)
## Author
- Justin W. Cain 
- @AffinityForFun
- https://www.affinityforfun.com
- jwcain@mtu.edu

## Timeline
- Init creation 		- 11/25/18
- Finished with bugs 	- 11/26/18
- Finished		- 11/27/18

## Purpose
This project is assignment 2 for the SMU Masters of Interactive Technology application process. It is a Huffman compression implementation. I attempted this assignment feeling that my portfolio lacked good C++ projects. I decided if this assignment is valuable to SMU Guildhall's application process, then it is a worthwhile addition to my portfolio.
	
## Process
It had been a while since I last attempted Huffman Compression, with this as my first time doing byte-compression instead of text-compression (compressing words into small strings of characters). Generally, I followed this process:

- Gather information.
- Attempt process manually.
- Code a prototype.
- Refactor design based on knowledge gained from the prototype.
- Iterate on the design until it is fully polished.

I utilized the assignment description, my most recent Huffman compression project, and a C assignment I had complete in college that contained code for bit-level IO operations.

(IMAGE MISSING)

You can see in my ever-present programming notebook that I spent time calculating the best way to store the Huffman tree inside the compressed file.

There, I am debating two options; one of which is a mistake. I am remembering a method for saving tree nodes in an array, but I eventually realize the process only works for balanced, binary trees. I decide on a fixed-size format for saving nodes, saving child-IDs or original byte data in the appropriate context.

Now confident with my process, I prioritize creating the data-structures for the program; compression, decompression, and IO operations use these data structures, making them the core coupling point for the program.

When writing my data structures, I assumed that run-time memory usage was non-critical and saved essential data in the smallest possible form.

(IMAGE MISSING)

My next goal was writing a helper class to manage bit-level IO operations, therefore abstracting away complexity from the algorithm.

I think it is worth mentioning a decision I made while testing decompression.  I tested decompression using data-in-memory from compression. Doing this separated the tasks, and inevitable bugs, of decompression and reconstruction of the Huffman tree, allowing me to develop them independently.

Finally, I iterated on commenting, reordering processes to higher-order logic, and restructuring the code for readability and flow.

## Reflection

Overall, I am happy with the results of this task. I believe it demonstrates that I am comfortable with higher-level algorithmic processes. 

On reflection, it seems my knowledge of C++ standard libraries may be lacking; I have a suspicion some of my code may be simplifiable with their help. In these situations, I err towards using the coding practices and techniques with which I am most comfortable; I believe it is better to produce code I understand fully and can explain, rather than sacrifice that integrity for speed or ease of production.

## Structure
Written in c++ standard 11, utilizing standard library string and IO
Included files "BitwiseIO.cpp", "BitwiseIO.h", "Huffman.cpp". "HuffmanBinaryNode.cpp", 
"HuffmanBinaryNode.n" and "makefile"
All code is stored in root directory of project
The main method for execution is located in Huffman.cpp
A Makefile is provided to compile the program.
The program is compiled to "Huffman"
Arguments are taken from the command line, no other user input is taken

## Usage
```
	Huffman <encode/decode> <InputFileName> <OutputFileName>
		Encode/decode selects that mode for execution
		InputFileName is the target file for encoding/decoding
		OutputFileName is the target output file and will be created/truncated
```

## Test Data
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
		
		
