🗜️ NanoZip — A Lightweight Huffman Compression Tool (in C)

NanoZip is a command-line based lossless file compression & decompression utility built entirely in C, using the Huffman Coding Algorithm.
Think of it as a tiny version of ZIP/GZIP — but handcrafted from scratch with no external libraries.

🚀 Features

⚡ Fast file compression using Huffman Coding

🔄 Full decompression support (restores original file)

🧠 Custom-built Min-Heap and Huffman Tree

🛠️ Implemented using only standard C library

🎯 Clean modular code structure

💻 Works on Linux, Windows (MinGW), and macOS

📂 Project Structure
NanoZip/
│
├── main.c          # Entry point — argument parsing, routing
├── huffman.c       # Huffman compression & decompression logic
├── huffman.h
│
├── heap.c          # Min-heap for building Huffman Tree
├── heap.h
│
├── Makefile        # To build project easily
└── README.md

🔍 How It Works (Short Explanation)

NanoZip uses Huffman Coding, a classic algorithm for lossless compression:

Counts frequency of every byte in the input file

Builds a Huffman Tree using a custom min-heap

Creates variable-length binary codes (short codes for common characters, long for rare ones)

Encodes the file bit-by-bit into a compressed .huff file

Stores the frequency table in the file header

During decompression, rebuilds the exact same Huffman Tree and restores the original file

🧵 Build Instructions
🔧 Compile

Use GCC or any standard C compiler:

gcc -o NanoZip.exe main.c huffman.c heap.c -Wall -g


Or simply run:

make

🗜️ Usage
1️⃣ Compress a File
./NanoZip -c input.txt compressed.huff

2️⃣ Decompress a File
./NanoZip -d compressed.huff output.txt


📌 The program supports any file type: .txt, .bin, .jpg, .mp4, etc.

🧩 Core Components Explained
🟦 main.c

Parses -c (compress) and -d (decompress)

Opens input/output files

Calls Huffman functions

🟩 huffman.c / huffman.h

Contains:

Frequency counting

Huffman tree construction

Code generation

Bit-level file writing

Decompression logic

🟨 heap.c / heap.h

Implements a min-heap priority queue

Used to efficiently build the Huffman Tree

📝 Example

Original (Sample.txt):

go go gophers


Compressed using Huffman Codes → much smaller binary file
Decompressed → exact same original content

Lossless. Efficient. Simple.

❤️ Why This Project?

This project is a great demonstration of:

Data compression fundamentals

Binary tree construction

Bitwise operations

Implementing a real-world algorithm from scratch

Writing modular C programs

📜 License

This project is open-source. You may modify or use it freely.
