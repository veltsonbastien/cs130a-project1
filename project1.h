// Veltson B.
// project1.h
// Project 1 Header for Ternary Search Tree Lab 1, CS130A

#ifndef PROJECT1_H
#define PROJECT1_H

#include <iostream>
#include <utility>
#include <vector>

using namespace std;

class TST {

 public:
    // ctor, dtor, insert and one print method already done in project1.cpp:
    TST();                   // constructor
    ~TST();                  // destructor

    //Needed functions 
    void lookup(string word); //searches for the string word in the TST
    void insert(string word); //inserts the string word into the TST
    void remove(string word); //deletes the string word from the TST 
    void range_search(string s1, string s2); //search for strings within this range 
    //Other methods that would be nice to have 
    vector<string> splitCommands(string input, string token); 
    void parseCommands(vector<string> commandsVector);  

 private:

    struct Node {
	pair <string,int> keyRight;
	pair <string,int> keyLeft; 
	Node *left = nullptr;
	Node *right = nullptr;
	Node *middle = nullptr;
        Node *parent = nullptr;         

        Node(string word){
	  this->keyLeft.first = word; 
	  this->keyLeft.second = 1;
	  this->keyRight.second = 0;  
	}
    };

    // just one instance variable (pointer to root node):
      
    Node *root;
     

    // recursive utility functions for use by public methods above
    void clear(Node* n); 
    void insert(string word, Node *n); // note overloading names for simplicity
    void print(Node *n) const;
    void lookup(string word, Node* n); //helper for that
    void print(Node* n, string word1, string word2) const;       // print tree data in-order to cout, will be helpful for range_search 
    // these should be used by getPredecessor and getSuccessor, and ONE of them should be used by remove
    //Node* getSuccessorNode(string word) const;   // returns the Node containing the successor of the given value
    //Node* getPredecessorNode(string word) const; // returns the Node containing the predecessor of the given value 
};

#endif
