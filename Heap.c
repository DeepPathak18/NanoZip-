#include <stdio.h>
#include <stdlib.h>
#include "Heap.h"

// Creates a new Huffman tree node

HuffNode* createNode(char data, unsigned freq) 
{
    HuffNode* node = (HuffNode*)malloc(sizeof(HuffNode));
    node->left = node->right = NULL;
    node->data = data;
    node->freq = freq;
    return node;
}

// Creates a Min-Heap of a given capacity

MinHeap* createMinHeap(unsigned capacity) 
{
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (HuffNode**)malloc(minHeap->capacity * sizeof(HuffNode*));
    return minHeap;
}

// Swaps two Huffman nodes

void swapNodes(HuffNode** a, HuffNode** b) 
{
    HuffNode* t = *a;
    *a = *b;
    *b = t;
}

// The main function to heapify a subtree rooted with node at given index

void minHeapify(MinHeap* minHeap, int idx) 
{
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
    {
        smallest = left;
    }
    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
    {
        smallest = right;
    }
    if (smallest != idx) 
    {
        swapNodes(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

// Extracts the minimum frequency node from the heap

HuffNode* extractMin(MinHeap* minHeap) 
{
    HuffNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

// Inserts a new node to the Min-Heap

void insertMinHeap(MinHeap* minHeap, HuffNode* node) 
{
    ++minHeap->size;
    int i = minHeap->size - 1;
    while (i && node->freq < minHeap->array[(i - 1) / 2]->freq) 
    {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = node;
}

// Builds the complete Min-Heap

void buildMinHeap(MinHeap* minHeap) 
{
    int n = minHeap->size - 1;
    for (int i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}