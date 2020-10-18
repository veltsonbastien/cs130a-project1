// Veltson B.
// project1.h
// Project 1 Header for Ternary Search Tree Lab 1, CS130A

#ifndef PROJECT1_H
#define PROJECT1_H

#include <iostream>
#include <utility> 

using namespace std;

class TST {

 public:
    // ctor, dtor, insert and one print method already done in project1.cpp:
    TST();                   // constructor
    TST(char* word);        // constructor with a word
    ~TST();                  // destructor

    //Needed functions 
    void lookup(char* word) const; //searches for the string word in the TST
    void insert(char* word); //inserts the string word into the TST
    void remove(char* word); //deletes the string word from the TST 
    void range_search(char* s1, char* s2); //search for strings within this range 
    //Other methods that would be nice to have 

 private:

    struct Node {
	pair <char*,int> keyRight;
	pair <char*,int> keyLeft; 
	Node *left, *right, *middle;

        Node(char* word){
	  *(keyLeft.first)=*word;
	  keyLeft.second = 1;
	  *(keyRight.first)='\0';
	  keyRight.second = 0; 
	  left = 0; 
	  middle = 0; 
	  right = 0; 
	}
    };

    // just one instance variable (pointer to root node):
    Node *root;

    // recursive utility functions for use by public methods above
    void clear(Node* n); 
    void insert(char* word, Node *n); // note overloading names for simplicity
    void print(Node *n) const;
    void lookup(char* word, Node* n) const; //helper for that
    void print(Node* n, char* word1, char* word2) const;       // print tree data in-order to cout, will be helpful for range_search  
    // these should be used by getPredecessor and getSuccessor, and ONE of them should be used by remove
    //Node* getSuccessorNode(string word) const;   // returns the Node containing the successor of the given value
    //Node* getPredecessorNode(string word) const; // returns the Node containing the predecessor of the given value 
};

#endif
