#### ***## Project Overview: What I Build?***

I'm going to build a program that takes a file as input and creates a new, smaller file containing the same information.

I'm also build the functionality to take this new compressed file and restore it to its original form. Think of it like a digital suitcase: you're packing your data more efficiently to save space.

This tool will run entirely from the command line, just like standard system utilities such as cp (copy) or mv (move). For example:

To compress: $./mycompress -c report.txt compressed\_report.huff

To decompress: $./mycompress -d compressed\_report.huff original\_report.txt

The core of this project is implementing the Huffman Coding algorithm, a clever method for lossless data compression.



#### ***## Technology and Tools :***


The beauty of this project is its simplicity and focus. You don't need fancy frameworks or external dependencies.

Language: C. That's it. We'll be using standard C features.

Compiler: A standard C compiler like GCC (GNU Compiler Collection) or Clang. If you're on Windows, you can use MinGW or WSL (Windows Subsystem for Linux) to get GCC.

Core Libraries: You'll only need the C Standard Library. No external downloads are required. The key header files you'll use are:

stdio.h: For all file input/output operations (fopen, fgetc, fwrite, printf, etc.).

stdlib.h: For dynamic memory allocation (malloc, free, exit).

string.h: For string manipulation if needed (strcpy, strlen).

Text Editor/IDE: Any you prefer, such as VS Code, Sublime Text, Vim, or a simple editor like Notepad++.

Terminal/Command Line: You will compile and run your program from here.




#### ***## The Core Logic: Huffman Coding Explained Simply***



Imagine you have the text "go go gophers".

The standard way to store this (ASCII) uses 8 bits for every character. But some characters appear more often than others. The idea behind Huffman Coding is: give shorter codes to frequent characters and longer codes to rare characters.

Analyze Frequencies: First, count how many times each character appears.

g: 3
o: 3
 : 2 (space)
p: 1
h: 1
e: 1
r: 1
s: 1

Build a Tree: You then build a special binary tree based on these frequencies. The characters with the lowest frequencies end up at the bottom, furthest from the root.

This tree structure automatically generates the optimal codes. To find a character's code, you just trace the path from the root, recording a 0 for a left turn and a 1 for a right turn.

Generate Codes \& Encode: Based on a possible tree for our example, the codes might look like this:

g: 11 (frequent, short code)
o: 10 (frequent, short code)
 : 00
...and so on for the others, which would get longer codes.

Now, instead of writing 8 bits for each character, you write its shorter Huffman code. This is where the file size reduction comes from.



###### ***Huffman Algorithm Understanding*** : https://www.youtube.com/watch?v=uDS8AkTAcIU


#### ***## The Complete Project Workflow***

Here's a high-level workflow from start to finish. We'll build this modularly.


##### ***Phase 1: Compression***

Command-Line Argument Parsing:

Your main function will check argc and argv to see if the user wants to compress (-c) or decompress (-d) and to get the input/output file names.

Frequency Counting:

Open the input file in binary read mode ("rb").

Create an array long long frequencies\[256] = {0};

Read the file one byte at a time (fgetc) and increment the count for that byte's value in your array (e.g., frequencies\[byte\_value]++;).

Building the Huffman Tree:

This is the most complex part. You'll need two main data structures:

A struct for the tree nodes (e.g., HuffNode).

A priority queue (specifically a min-heap) to store the nodes. You will likely have to implement this data structure yourself, which is fantastic practice.

The Algorithm:

a. Create a leaf node for each character that has a frequency > 0.

b. Insert all these leaf nodes into your min-heap.

c. While the heap has more than one node:

i. Extract the two nodes with the smallest frequencies.

ii. Create a new internal node. Make the two extracted nodes its left and right children.

iii. Set the new node's frequency to the sum of its children's frequencies.

iv. Insert this new internal node back into the heap.

The single node left in the heap at the end is the root of your Huffman Tree.

Generating the Huffman Codes:

Traverse the tree recursively from the root.

Pass down a string or an array that builds the code (0 for left, 1 for right).

When you reach a leaf node, you have the full code for that character. Store these codes in a lookup table (e.g., char\* huffman\_codes\[256];).

Encoding the File:

Open the output file in binary write mode ("wb").

Write the Header: This is crucial! The decompressor needs to know the structure of the tree. A simple way is to write the frequency table to the start of the file.

Write the Data:

a. Go back to the beginning of the input file (rewind).

b. Read one character at a time.

c. Look up its Huffman code from your table.

d. Write the bits of that code to the output file. You can't write single bits, so you'll need to use bitwise operators to pack 8 bits into a buffer byte and then write the full byte to the file.



##### ***Phase 2: Decompression***

Read the Header:

Open the compressed file (.huff).

Read the frequency table from the header.

Rebuild the Tree:

Using the frequency table you just read, repeat the exact same tree-building process from Step 3 above. You will get the identical Huffman Tree.

Decode the Data:

Start reading the rest of the file one byte at a time.

For each byte, read it bit by bit.

For each bit, traverse the Huffman tree from the root (0 = go left, 1 = go right).

When you reach a leaf node, you've decoded a character. Write this character to the final output file.

Reset your traversal back to the root of the tree and continue with the next bit.

You'll need a way to know when to stop (e.g., the header could also store the total number of characters in the original file).






#### ***##  Project Setup and File Structure***

--> main.c: The entry point of our program. It will handle command-line arguments and call the appropriate functions.

--> huffman.h: The header file for our Huffman logic. It will contain function declarations and structure definitions that other files can see.

--> huffman.c: The implementation file for the Huffman logic. It will contain the actual code for compression and decompression.

--> heap.h: The header file for our min-heap data structure, which is essential for building the Huffman tree efficiently.

--> heap.c: The implementation of the min-heap.

Makefile: A special file to make compilation of our multi-file project easy. Instead of typing a long gcc command every time, we'll just type make.



#### ***## To Execute The Program***


To Compile the Program : gcc -o NanoZip.exe main.c Huffman.c Heap.c -Wall -g

To Compress the Program : NanoZip -c Sample.txt compressed.huff

--> here Sample.txt is main file after running above command it will compressed and make compressed.huff file (we can change our compressed file name also)   

To Decompress the Program : NanoZip -d compressed.huff original.txt

--> here compressed.huff is main file after running above command it will Decompressed and make original.txt file (we can change our Decompressed file name also)

