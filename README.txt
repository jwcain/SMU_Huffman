SMU Assignment 2 - Huffman encoding
	https://github.com/jwcain/SMU_Huffman
	TIMELINE:
		Init creation 		- 11/25/18
		Finished with bugs  - 11/26/18
		Finished			- 11/27/18

Purpose/Theory:
	Huffman encoding is a well known compression process, this was my third time 
	implementing the algorithm but the first in C++ and the first using bitwise operations.
	
	I first set out creating the HuffmanBinaryNode class, to ensure I understood the layout
	of how I wanted to manage the data before completing anything else.
	
	Then I began work on bitwise operations. I had previously written bitwise IO operations for
	another project in C, so I ported it to a C++ class. It works by reading/writing in chunks 
	to a buffer, and once that buffer is full that buffer is written out or more is read into it.
	The bitwise operations are tracked by keeping a current byte and the position we are within the 
	byte. To get a bit we & with an unsigned one shifted to the correct position, and then change 
	our overall position in the byte. After testing, I improved the class to allow for better reading 
	of whole bytes as large files where processed slowly one byte at a time.
	
	Next came the process of actually handling the encoding/decoding. This mostly followed assignment
	spec except for a few areas. Bitwise representations were calculated by traversing upward from all
	leaf nodes and then reversed. This was done because I had coded functionality to do traversals and
	execute a function passed by pointer on each node. Rather than code something to search down ward,
	it was easer to use these traversal operations and write a function that searched upward to pass
	as argument. 
	The other deviation is I stored my tree in pre order, depth first. This is done because
	the tree head is (essentially, but not technically) the last node created always. As part of my 
	debugging process I assigned each node a unique int id, which was literally the current count
	of nodes at time of instantiation. This effectively served as a node count, and I realized if I could
	store head first I could get a number of nodes to read in by first reading in the head node "in the 
	dark." 
	
	I stored the nodes with the following data:
		1 bit (isLeaf)
		1 bit (isEOFCharacter)
		10 bit node ID
		then
		8 bit for original byte if a leaf
		or
		10 bit for left child ID
		10 bit for right child ID
	
		for a total of 32 bits for branch nodes and 20 bits for leaf nodes. A max total would be
			257 leaf nodes (256 unique bytes and the EOF representation)
			358 branch nodes
			257*20=5140
			358*32=11456
			16596 bits or
			2,074.5 Bytes
			
	The ID's are stored as 10 bits because the maximum number of nodes would be NlogN, where n=256 (for 256 
	unique bytes), this is 615 nodes, the smallest bit string that can represent this number is 1- (2^9 = 512,
	2^10=1024). We can store flexible number of bits because we know by the first bit read (is leaf) how many
	bits we need to read afterwards.
	
	To ensure we know when we have reached the end of the encoded data, a special EOF character is added to the 
	tree on creation with a frequency of 0. This guarantees it gets the longest/worst representation. When this
	representation is read in full decoding data stops. This also allows us to pad to the byte boundary when
	making the encoded file without worry of misrepresenting bytes.
	
	Since we store links by ID's the decoding process takes the extra step to rebuild the tree by looping through
	all nodes and assigning their children pointers to the correct current value in memory using the stored IDs.
	
	
	While not part of the assignment, I have had other thoughts on how to store the tree, and while I disproved
	their validity I have included them as they show why used the methodology I did:
		I have considered the idea of storing only leaf nodes with their frequency and attempting to rebuild the
		tree. The first issue I have with this is that since frequency is stored with a large number (to allow
		for compression of large files) the representation of this number is 32 bits, already tied for our
		current max size without considering other information. The other fault is the case of equal frequency.
		Due to strict weak ordering, we cannot guarantee that the tree will be restructured in the same way.
	
		I have considered the idea of only storing leaf nodes and compressed representation to
		rebuild the tree. While untested, the compressed representation gives the path to find the leaf node and 
		could potentially be used in respect to others to rebuild a representation of the tree. The issue I have 
		with this plan is that in order to have a guaranteed closed form of the compression representation is 
		that the worst case tree has a height of 256s with 257 leaf nodes a 256 bit string for each is way
		larger than storing the whole tree. (8224 bytes)
	
	
	Testing:
		The exact terminal statements I used for testing are stored in the makefile. Doing this allowed me to
		perform consistent testing easily. the commands are `make <test/testfake/testmore/testlarge>`
	The code was tested on:
		Empty file
		Non existent file
		Small text sample from a random wikipedia article
		Random files generated by the Linux command `dd if=/dev/zero of=file.txt count=1024 bs=1024`
			Sizes 1MB, 10 MB, 137MB, 1GB
		Files containing only a single byte
		Files containing every possible byte.
		Differences between beginning and ending files were tested using Linux command `diff`
		Valgrind showed no non-reachable memory on exit
		Decoding on a file not encoded by this process 
			(Does not work, but program does its best to detect this
			there exists the case where a foreign file is precisely laid out that the tree a tree is created properly.
			Since 'valid file checking' is dependent on this tree being correct, this would be a false positive and
			results are undefined. (Will likely crash unless the file also happens to have the correct EOF character))
		Chaining multiple encodings together, and decoding to the original
		
		

CODE STRUCTURE:
	Written in c++ standard 11, utilizing standard library string and IO
	Included files "BitwiseIO.cpp", "BitwiseIO.h", "Huffman.cpp". "HuffmanBinaryNode.cpp", 
	"HuffmanBinaryNode.n" and "makefile"
	All code is stored in root directory of project
	The main method for execution is located in Huffman.cpp
	A Makefile is provided to compile the program.
	The program is compiled to "Huffman"
	Arguments are taken from the command line, no other user input is taken
		
Process:
	Create nodes for the creation of a binary tree first
	Create Bitwise IO manager
	Test Bitwise IO manager operations
		Slightly automate testing with makefile commands
	Started making trees
	made compression PQ
	made
	
	
USAGE:
	Huffman <encode/decode> <InputFileName> <OutputFileName>
		Encode/decode selects that mode for execution
		InputFileName is the target file for encoding/decoding
		OutputFileName is the target output file and will be created/truncated
		
		
Examples:
	Below shows the uncompressed and compressed filesize of a few test cases.
	Sizes are not exact since they are random files I found on my computer of approximate size.
	Deflation is the percentage remaining of original size.
	Empty File:
		Regular:	0
		Compressed:	0 (not ran, execution terminated early due to file size of 0)
		Deflation:	?%
	Small test file:
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
		Deflation:	94.95
	137MB:
		Regular:	143818752
		Compressed:	136353291
		Deflation:	94.81%
		
		
	Thoughts on testing:
		I have tested two rounds of data of the same size.  The first round was files of a single 
		byte, and the compression ratio was really good (12.5% almost across board). The testing
		of this set was accidental, as the set I found was not random as advertised.
		
		The second set (shown above) included binary files I found on my personal computer that 
		had all 256 bytes represented. These had significantly worse compression ratios. The 
		takeaway is I believe the compression algorithm is working as intended, these binary files
		just had a very flat distribution across all bytes so the compression was not as successful.
		
		