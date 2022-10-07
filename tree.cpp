//
// Created by Case on 6/8/2022.
//

#include "tree.h"

bool compareNodesE(Node* first, Node* second);
bool compareEncode(Encoding* first, Encoding* second);

Tree::~Tree()
{

}

// Generates tree by combining each leaf node and creating a parent until there is only one
Node* Tree::GenerateTree(vector<Node*> freqTable)
{
    while(freqTable.size() > 1)
    {
        Node* node1 = freqTable.back();
        freqTable.pop_back();

        Node* node2 = freqTable.back();
        freqTable.pop_back();

        string combChars = node1->GetChar() + node2->GetChar();
        int combCount = node1->GetCount() + node2->GetCount();
        Node* parentNode = new Node(combChars, combCount, node1, node2);

        freqTable.push_back(parentNode);

        sort(freqTable.begin(), freqTable.end(), compareNodesE);
    }

    return freqTable.back();
}

// encodes each element in the tree, assigns it a code, and puts it in a vector to return
vector<Encoding*> Tree::Encode(Node* root, string encoded)
{
    if(root == nullptr)
    {
        return _encodedTable;
    }

    if(root->GetLeft() == nullptr && root->GetRight() == nullptr)
    {
        Encoding* encodeTable = new Encoding;
        encodeTable->_character = root->GetChar();
        encodeTable->_code = encoded;

        _encodedTable.push_back(encodeTable);

    }

    Encode(root->GetLeft(), encoded + '1');

    Encode(root->GetRight(), encoded + '0');

    sort(_encodedTable.begin(), _encodedTable.end(), compareEncode);

    return _encodedTable;
}

// comparator for vector sort
bool compareNodesE(Node* first, Node* second)
{
    if (first->GetCount() == second->GetCount())
    {
        return first->GetChar().at(0) > second->GetChar().at(0);
    }

    return first->GetCount() > second->GetCount();

}

// comparator for vector sort for encoding struct
bool compareEncode(Encoding* first, Encoding* second)
{
    if(first->_code.length() == second->_code.length())
    {
        return first->_code < second->_code;
    }
    return first->_code.length() < second->_code.length();
}

