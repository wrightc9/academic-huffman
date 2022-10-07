//
// Created by Case on 6/1/2022.
//

#include "node.h"

Node::Node(string character, int count, Node* left, Node* right):_char(character), _count(count), _left(left), _right(right)
{

}

Node::Node(string character) : _char(character), _count(1)
{

}

string Node::GetChar() const
{
    return _char;
}

int Node::GetCount() const
{
    return _count;
}

Node* Node::GetLeft() const
{
    return _left;
}

Node* Node::GetRight() const
{
    return _right;
}

void Node::SetChar(string character)
{
    _char = character;
}

void Node::SetCount(int count)
{
    _count = count;
}

void Node::SetLeft(Node* left)
{
    _left = left;
}

void Node::SetRight(Node* right)
{
    _right = right;
}
