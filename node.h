//
// Created by Case on 6/1/2022.
//

#ifndef HUFFMAN_WRIGHTC9_NODE_H
#define HUFFMAN_WRIGHTC9_NODE_H

#include <string>

using std::string;

// tree node that stores char, frequency, left and right children
class Node {
public:
    Node(string character, int count, Node* left, Node* right);
    Node(string character);

    string GetChar() const;
    int GetCount() const;
    Node* GetLeft() const;
    Node* GetRight() const;

    void SetChar(string character);
    void SetCount(int count);
    void SetLeft(Node* left);
    void SetRight(Node* right);

private:
    string _char;
    int _count;
    Node* _left = nullptr;
    Node* _right = nullptr;
};


#endif //HUFFMAN_WRIGHTC9_NODE_H
