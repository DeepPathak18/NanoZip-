#include <stdio.h>
#include <string.h>
#include "Huffman.h"

void printUsage() 
{
    printf("Usage: NANOZIP [option] [input_file] [output_file]\n");
    printf("Options:\n");
    printf("  -c\tCompress the input file.\n");
    printf("  -d\tDecompress the input file.\n");
}

int main(int argc, char* argv[]) 
{
    if (argc != 4) 
    {
        printUsage();
        return 1;
    }

    char* option = argv[1];
    char* inputFile = argv[2];
    char* outputFile = argv[3];

    if (strcmp(option, "-c") == 0) 
    {
        printf("Compressing '%s' to '%s'...\n", inputFile, outputFile);
        compressFile(inputFile, outputFile);
    }
    else if (strcmp(option, "-d") == 0) 
    {
        printf("Decompressing '%s' to '%s'...\n", inputFile, outputFile);
        decompressFile(inputFile, outputFile);
    }
    else 
    {
        printf("Error: Invalid option '%s'\n", option);
        printUsage();
        return 1;
    }

    return 0;
}