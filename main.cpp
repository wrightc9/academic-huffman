#include "node.h"
#include "tree.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>

using std::fstream;
using std::ifstream;
using std::ofstream;
using std::vector;
using std::cerr;
using std::endl;
using std::string;
using std::sort;
using std::cout;

vector<Node*> Read(const string& inputFile);
bool compareNodes(Node* first, Node* second);
void EncodeFile(const vector<Encoding*>& table, const string& inputFile, const string& outputFile);
string Find(const vector<Encoding*>& table, const string& character);
void DestroyTree(Node* root);

int main(int argc, char* argv[])
{
    // makes sure there is the correct amount of arguments are given
    if(argc < 3 || argc > 4)
    {
        cerr << "Invalid number of arguments." << endl;
        return 1;
    }

    // creates a vector and reads characters and their frequency into it
    vector<Node*> freqTable = Read(argv[2]);

    // sorts frequency table
    sort(freqTable.begin(), freqTable.end(), compareNodes);

    // generates a tree with the elements from table
    Tree* myTree = new Tree;
    Node* myRoot = myTree->GenerateTree(freqTable);

    // encodes the elements of the tree
    vector<Encoding*> myTable= myTree->Encode(myRoot,"");

    // encodes file
    if(strcmp(argv[1], "-encode") == 0)
    {
        EncodeFile(myTable, argv[2], argv[3]);
    }
    // decodes file
    else if(strcmp(argv[1], "-decode") == 0)
    {
        cerr << "Not implemented yet :)";
        return 1;
    }
    // outputs frequency table
    else if(strcmp(argv[1], "-frequency") == 0)
    {
        for(auto i : freqTable)
        {
            if(i->GetChar() == "LF" || i->GetChar() == "CR")
                cout << "{element: "  << i->GetChar()<< ", frequency: " <<  i->GetCount() << "}" << endl;
            else
                cout << "{element:  "  << i->GetChar()<< ", frequency: " <<  i->GetCount() << "}" << endl;
        }
    }
    // outputs the code for a single char
    else if(strcmp(argv[1], "-single") == 0)
    {
        cout << Find(myTable, argv[3]) << endl;
    }
    // outputs encoding table
    else if(strcmp(argv[1], "-encoding-table") == 0)
    {
        for(auto i : myTable)
        {
            if(i->_character == "LF" || i->_character == "CR")
                cout << "{key: " << i->_character << ", code: " << i->_code << "}" << endl;
            else
                cout << "{key:  " << i->_character << ", code: " << i->_code << "}" << endl;
        }
    }
    else
    {
        cerr << "Invalid argument" << endl;
        return 1;
    }

    // clears memory
    DestroyTree(myRoot);
    delete myTree;
    for(auto i : myTable)
    {
        delete i;
    }

    return 0;
}

// reads through each char in the file, counts, and stores into a vector
vector<Node*> Read(const string& inputFile)
{
    ifstream input;
    vector<Node*> freqTable;

    input.open(inputFile);
    if(!input.is_open())
    {
        cerr << "Unable to open file " << inputFile << endl;

        return freqTable;
    }

    //creates char buffer
    char buf[4096];

    do
    {
        // reads in blocks of 4096
        input.read(buf, 4096);
        for(int i = 0; i < input.gcount(); i++)
        {
            bool found = false;
            string character = string(1, buf[i]);
            if(character == "\n")
            {
                character = "LF";
            }
            if(character == "\r")
            {
                character = "CR";
            }

            for(auto & j : freqTable)
            {
                if(character == j->GetChar())
                {
                    j->SetCount(j->GetCount() + 1);

                    found = true;

                    break;
                }
            }

            if(!found)
            {
                Node* node = new Node(character);
                freqTable.push_back(node);
            }

        }
    }
    while(input);

    input.close();

    return freqTable;
}

// reads through file and changes each char to its corresponding code
void EncodeFile(const vector<Encoding*>& table, const string& inputFile, const string& outputFile)
{
    ifstream input;

    input.open(inputFile);
    if(!input.is_open())
    {
        cerr << "Unable to open file " << inputFile << endl;

        return;
    }

    ofstream output(outputFile);
    if(!output.is_open())
    {
        cerr << "Unable to open file " << outputFile << endl;

        return;
    }

    char buf[4096];
    do
    {
        input.read(buf, 4096);
        for(int i = 0; i < input.gcount(); i++)
        {
            string character = string(1, buf[i]);
            if(character == "\n")
            {
                character = "LF";
            }
            if(character == "\r")
            {
                character = "CR";
            }

            output << Find(table, character);

        }
    }
    while(input);

    input.close();
    output.close();
}

// searches encoding table for matching character
string Find(const vector<Encoding*>& table, const string& character)
{
    for(auto i : table)
    {
        if(i->_character == character)
        {
            return i->_code;
        }
    }

    return "";
}

//comparator for vector sort
bool compareNodes(Node* first, Node* second)
{
    if(first->GetCount() == second->GetCount())
    {
        return first->GetChar() > second->GetChar();
    }

    return first->GetCount() > second->GetCount();
}

// deallocates tree
void DestroyTree(Node* root)
{
    if (root == nullptr)
        return;

    DestroyTree(root->GetLeft());
    DestroyTree(root->GetRight());

    delete root;
}