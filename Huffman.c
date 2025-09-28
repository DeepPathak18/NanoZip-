#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Huffman.h"
#include "Heap.h"
#define MAX_TREE_HT 256

// Builds the Huffman Tree and returns the root

HuffNode* buildHuffmanTree(char data[], int freq[], int size) 
{
    HuffNode *left, *right, *top;
    MinHeap* minHeap = createMinHeap(size);

    for (int i = 0; i < size; ++i)
    {
        insertMinHeap(minHeap, createNode(data[i], freq[i]));
    }
    while (minHeap->size != 1) 
    {
        left = extractMin(minHeap);
        right = extractMin(minHeap);
        top = createNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertMinHeap(minHeap, top);
    }
    return extractMin(minHeap);
}

// Recursively generates codes and stores them in the codes array

void generateCodes(HuffNode* root, int arr[], int top, char codes[MAX_TREE_HT][MAX_TREE_HT]) 
{
    if (root->left) 
    {
        arr[top] = 0;
        generateCodes(root->left, arr, top + 1, codes);
    }
    if (root->right) 
    {
        arr[top] = 1;
        generateCodes(root->right, arr, top + 1, codes);
    }
    if (!root->left && !root->right) 
    {
        char code_str[MAX_TREE_HT];
        int i;
        for (i = 0; i < top; i++) 
        {
            code_str[i] = arr[i] + '0';
        }
        code_str[i] = '\0';
        strcpy(codes[(unsigned char)root->data], code_str);
    }
}

// --- --------------------------------         Main Compression and Decompression Functions ----------------------------------------------

void compressFile(const char* inputPath, const char* outputPath) 
{
    // 1. Count character frequencies

    unsigned freq[256] = {0};
    FILE* inFile = fopen(inputPath, "rb");
    if (!inFile) 
    {
        perror("Error opening input file");
        return;
    }
    int c;
    long long file_len = 0;
    while ((c = fgetc(inFile)) != EOF) 
    {
        freq[c]++;
        file_len++;
    }
    rewind(inFile);

    // 2. Prepare data for Huffman Tree alloting frequency according to data

    char data[256];
    int unique_freq[256];
    int size = 0;
    for (int i = 0; i < 256; i++) 
    {
        if (freq[i] > 0) 
        {
            data[size] = (char)i;
            unique_freq[size] = freq[i];
            size++;
        }
    }

    // 3. Build the Huffman Tree

    HuffNode* root = buildHuffmanTree(data, unique_freq, size);

    // 4. Generate Huffman codes

    char codes[256][MAX_TREE_HT];
    int arr[MAX_TREE_HT], top = 0;
    generateCodes(root, arr, top, codes);

    // 5. Write header and compressed data to output file

    FILE* outFile = fopen(outputPath, "wb");
    if (!outFile) 
    {
        perror("Error opening output file");
        fclose(inFile);
        return;
    }

    // Write header: size of frequency table, then the table itself

    fwrite(&size, sizeof(int), 1, outFile);
    fwrite(data, sizeof(char), size, outFile);
    fwrite(unique_freq, sizeof(int), size, outFile);
    fwrite(&file_len, sizeof(long long), 1, outFile); // Write original file length

    // Write compressed data
    unsigned char buffer = 0;
    int bit_count = 0;
    while ((c = fgetc(inFile)) != EOF) 
    {
        char* code = codes[c];
        for (int i = 0; code[i] != '\0'; i++) 
        {
            buffer <<= 1;
            if (code[i] == '1') 
            {
                buffer |= 1;
            }
            bit_count++;
            if (bit_count == 8) 
            {
                fwrite(&buffer, 1, 1, outFile);
                buffer = 0;
                bit_count = 0;
            }
        }
    }

    // Write any remaining bits
    if (bit_count > 0) 
    {
        buffer <<= (8 - bit_count);
        fwrite(&buffer, 1, 1, outFile);
    }

    printf("File compressed successfully!\n");
    fclose(inFile);
    fclose(outFile);
    // Free memory (important but omitted here for brevity)
}

void decompressFile(const char* inputPath, const char* outputPath) 
{
    FILE* inFile = fopen(inputPath, "rb");
    if (!inFile) 
    {
        perror("Error opening input file");
        return;
    }

    // 1. Read the header

    int size;
    fread(&size, sizeof(int), 1, inFile);

    char data[size];
    int freq[size];
    fread(data, sizeof(char), size, inFile);
    fread(freq, sizeof(int), size, inFile);

    long long original_len;
    fread(&original_len, sizeof(long long), 1, inFile);

    // 2. Rebuild the Huffman Tree

    HuffNode* root = buildHuffmanTree(data, freq, size);

    // 3. Decode the data

    FILE* outFile = fopen(outputPath, "wb");
    if (!outFile) 
    {
        perror("Error opening output file");
        fclose(inFile);
        return;
    }

    unsigned char buffer;
    
    HuffNode* currentNode = root;
    long long written_bytes = 0;
    
    while (fread(&buffer, 1, 1, inFile) == 1 && written_bytes < original_len) 
    {
        for (int i = 7; i >= 0; i--) 
        {
            int bit = (buffer >> i) & 1;
            if (bit == 0) 
            {
                currentNode = currentNode->left;
            } 
            else 
            {
                currentNode = currentNode->right;
            }
            if (!currentNode->left && !currentNode->right) 
            {
                fputc(currentNode->data, outFile);
                written_bytes++;
                if (written_bytes == original_len) 
                {
                    break;
                }
                currentNode = root;
            }
        }
    }
    printf("File decompressed successfully!\n");
    fclose(inFile);
    fclose(outFile);
   
}