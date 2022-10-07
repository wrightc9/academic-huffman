//
// Created by Case on 6/8/2022.
//

#ifndef HUFFMAN_WRIGHTC9_TREE_H
#define HUFFMAN_WRIGHTC9_TREE_H

#include "node.h"

#include <vector>
#include <algorithm>
#include <fstream>

using std::sort;
using std::vector;
using std::ofstream;

// struct that stores char and code for encoding table
struct Encoding
{
    string _character;
    string _code;
};

// Binary tree for encoding
class Tree {
public:
    ~Tree();
    Node* GenerateTree(vector<Node*> freqTable);
    vector<Encoding*> Encode(Node* root, string encoded);

private:
    vector<Encoding*> _encodedTable;
};


#endif //HUFFMAN_WRIGHTC9_TREE_H
