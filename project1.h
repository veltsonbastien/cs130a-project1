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
    ~TST();                  // destructor

    //Needed functions 
    void lookup(string word) const; //searches for the string word in the TST 
    void insert(string word); //inserts the string word into the TST
    void remove(string word); //deletes the string word from the TST 
    void range_search(string s1, string s2); //search for strings within this range

 
    //Other methods that would be nice to have 
    void printInOrder() const;       // print tree data in-order to cout, will be helpful for range_search
    bool contains(string word) const;  // true if word is in the TST, will be helpful for quickly checking if words are in the tree or no
    //string getPredecessor(string word) const;       // returns the predecessor string of the given value or null if there is none
    //string getSuccessor(string word) const;         // returns the successor string of the given value or null if there is none
    


 private:

    struct Node {
	pair <string,int> keyRight;
	pair <string,int> keyLeft; 
	Node *left, *right, *middle;

        Node(string word){
	  keyLeft.first=word;
	  keyLeft.second = 1;
	  keyRight.first ="";
	  keyRight.second = 0; 
	  left = 0; 
	  middle = 0; 
	  right = 0; 
	}
    };

    // just one instance variable (pointer to root node):
    Node *root;

    // recursive utility functions for use by public methods above
    Node* getNodeFor(string word, Node* n) const; // IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
    void clear(Node *n); // for destructor
    void insert(string word, Node *n); // note overloading names for simplicity
    void printInOrder(Node *n) const;

    // these should be used by getPredecessor and getSuccessor, and ONE of them should be used by remove
    //Node* getSuccessorNode(string word) const;   // returns the Node containing the successor of the given value
    //Node* getPredecessorNode(string word) const; // returns the Node containing the predecessor of the given value 
};

#endif
