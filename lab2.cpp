#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// struct which holds a single line of the table
struct TableLine {
    bool valid;
    int tag;
};

// function to check if tag is valid or not
bool checkTag(int curr, int tag, bool validBit) {
    return (curr == tag) && validBit;
}

int main(int argc, char** argv) {
    // usage:
    // ./Lab2 blockSize numBlocks associativity(as a single char) hittime misstime < inputFile
    int blockSize = atoi(argv[1]);
    int numBlocks = atoi(argv[2]);
    char associativity = *argv[3];
    int hitTime = atoi(argv[4]);
    int missTime = atoi(argv[5]);

    int index;
    int tag;
    int offset;

    int totalTime = 0;
    int totalHits = 0;
    int totalAccess = 0;

    string input;
    int inputToInt;

    TableLine table[numBlocks];

// read data from stdin
    while (cin >> input) {
        totalAccess++;

// read input as hex value, calculate offset by modding by blockSize
        inputToInt = stoi(input, 0, 16);
        offset = inputToInt % blockSize;

// basically a bit shift to move over to index
        inputToInt /= blockSize;

// calculate index by modding by numBlocks
        index = inputToInt % numBlocks;

// basically a bit shift to move over to tag
        inputToInt /= numBlocks;
// calculate tag with remaining data
        tag = inputToInt;

// check if hit or not, increment hitTime if so
        if (checkTag(table[index].tag, tag, table[index].valid)) {
            totalTime += hitTime;
            totalHits++;
        }

// if cache miss, load new data into cache location
        else {
            totalTime += missTime;
            table[index].tag = tag;
            table[index].valid = true;
        }        
    }

    float percentage = (float)totalHits/(float)totalAccess * 100;
    float AMAT = (float)totalTime/(float)totalAccess;

// print stats
    cout << "total hits: " << totalHits << "\ntotal accesses: " << totalAccess << "\ntime elapsed: " << totalTime << endl;
    cout << "\nhit rate: " << percentage << "%\nAMAT: " << AMAT << endl;
}