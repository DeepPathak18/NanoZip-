#ifndef HEAP_H
#define HEAP_H

// A node in the Huffman Tree

typedef struct HuffNode 
{
    char data;                 // The character of whatever input one by one
    unsigned freq;             // Frequency of the character to check one by one character
    struct HuffNode *left, *right; // Left and right children for making node in Tree
} HuffNode;

// A Min-Heap which is a collection of Huffman Tree nodes

typedef struct MinHeap 
{
    unsigned size;     // Current size of min heap
    unsigned capacity; // Capacity of min heap
    HuffNode** array;  // Array of HuffNode pointers
} MinHeap;

// Function declarations for our heap operations

HuffNode* createNode(char data, unsigned freq);
MinHeap* createMinHeap(unsigned capacity);
void swapNodes(HuffNode** a, HuffNode** b);
void minHeapify(MinHeap* minHeap, int idx);
HuffNode* extractMin(MinHeap* minHeap);
void insertMinHeap(MinHeap* minHeap, HuffNode* node);
void buildMinHeap(MinHeap* minHeap);

#endif 