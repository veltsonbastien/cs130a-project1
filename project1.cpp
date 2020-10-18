// project1.cpp
// Implements class TST
//Veltson Bastien
//10/16/2020


#include "project1.h"
#include <iostream>
#include <utility> 

using std::cout;
 
// default constructor sets up empty tree
TST::TST() : root(0) { }

// constructor with a word if you want 
TST::TST(string word){
 root = new Node(word); 
}

// destructor deletes all nodes
TST::~TST() {
    clear(root);
}

// recursive helper for destructor
void TST::clear(Node *n) {
    if (n) {
	clear(n->left);
	clear(n->middle);
	clear(n->right);
	delete n;
    }
}


//search main function
void TST::lookup(string word){
  //handle when there is an empty tree
  if(!root){
   cout<<word<<" not found"<<endl;    
  } else {
    lookup(word, root); 
  }//end of else
}//end of search

void TST::lookup(string word, Node* n){
    //this will basically be similar to insert, but instead of inserting, we show that it is found
    //check if a node is in DAMN existence 
    if(n!=NULL){
	
    	//first check root and what it's got goin' on up there, the only n coming in here should be root's  
    	//but before we move on, check if it equals what's going on, and INTERVENE accordingly
    	if( ( (strcmp(word, n->keyLeft.first))==0){
        cout<<word<<"found, count="<<keyLeft.second<<endl;
	}//if it's in the key left
        //or is it found in key right
	else if(strcmp(word, n->keyRight.first))==0){
       	cout<<word<<"found, count="<<keyRight.second<<endl; 
    	}

        //first check left and right entries to see if it has a chance at even being in this node - if not, try in another place zibs
    	if( (strcmp(word, n->keyLeft.first))==-1 ) lookup(word,n->left);  //check if it's negative one, (means smaller) ain't boutta be in here
	//next check if there is a keyRight value 
	else if((n->keyRight.second!=0) && (strcmp(word, n->keyRight.first))==1 ) lookup(word, n->right); 

	else{
	//now if it passed through all of those, we can throw it into the middle and let it recursively take care of itself 
    	lookup(word, n->middle); 
	}
        
    } //end of NULL NODE check 
    else{
     //if node doesn't exist, you know what to do
     //it's not here, so say that
     count<<word<<" not found"<<endl;
    } //end of else check for that boi


}//end of lookup function


// insert main function
void TST::insert(string word) {
    // handle special case of empty tree first
    if (!root) {
	root = new Node(word);
    }
    // otherwise use recursive helper
    else{ 
        insert(word, root);
    }

}


// recursive helper for insert (assumes n is never 0)
void TST::insert(string word, Node* n) {

    //check if a node is in DAMN existence 
    if(n!=NULL){
	
    //first check root and what it's got goin' on up there, the only n coming in here should be root's  
    //but before we move on, check if it equals what's going on, and INTERVENE accordingly
    if( (strcmp(word, n->keyLeft.first))==0) keyLeft.second++; 
    else if((strcmp(word, n->keyRight.first))==0) keyRight.second++; 

	//next check if there is a keyRight value 
	//if there isn't handle it properly
	if(n->keyRight.second == 0){
	   //if the value is less than keyLeft, switch keyLeft and keyRight
	   if( (strcmp(word, n->keyLeft.first))==-1 ){
            string tempString = keyLeft.first;
	    string tempCount = keyLeft.second;
	    keyLeft.first = word; 
	    keyLeft.second = 1; 
	    keyRight.first = tempString;
	    keyRight.second = tempCount; 
	   }else{
           //put it in keyRight
	   n->keyRight.first = word;
	   n->keyRight.second = 1;
	   }//end of else
	} //end of if keyright is zero
    	//Next we working on checking left and right entries to see if it has a chance at even being in this node - if not, try in another place zibs
	else if( (strcmp(word, n->keyLeft.first))==-1 ){
	  insert(word,n->left);  //check if it's negative one, (means smaller) ain't boutta be in here
	}//end of smaller than left check 
 	else if( (strcmp(word, n->keyRight.first))==1 ){ 
	  //check if it's one, (that means bigger) it ain't boutta be in here  
          insert(word, n->right); 	
	}//end of else if 
	else{
	//now if it passed through all of those, we can throw it into the middle and let it recursively take care of itself 
    	insert(word, n->middle); 
	}

    } //end of NULL NODE check 
    else{
     //if node doesn't exist, you know what to do
     n = new Node(word);  
    } //end of else check for that boi

} //end of check


pair<Node*, int> getNodeInfo(string word){
  //they are going to pass in a word, but we know we wanna compare with root
  getNodeInfo(word, root); 
}

//This acts as a "fixer" in the case that the word (or words) doesn't exist. it gets the successor word and returns that if the first word of the range 
//search doesn't exist. It gets the predecessor word and returns THAT if the second word of the range doesn't exist. 
string getSuccessorWord(Node* n, int rightOrLeftFlag){
     //if n is null, return an empty string 
     if(n==NULL) return "";
     //else use the node position and flag to respond with the word of the successor
     if(rightOrLeftFlag == 1) return n->keyLeft; 
     return n->keyRight; 
}



//helper class for node information, will return pointers and an int acting a flag determining important info on keyLeft and keyRight
pair<Node*, int> getNodeInfo(string word, Node* n){
     pair<Node*, int> nodeInfo; 	
    //first check root and what it's got goin' on up there, the only n coming in here should be root's  
    //but before we move on, check if it equals what's going on, and INTERVENE accordingly
    if( (strcmp(word, n->keyLeft.first))==0){
	//the word equals what's in keyLeft, so we return the pointer to this 
	nodeInfo.first = n; 
	nodeInfo.second = 1; //1 means keyLeft
	return nodeInfo; 
    }
    else if((strcmp(word, n->keyRight.first))==0){
       //the word equals what's in keyRight, so we return the pointer to this 
       nodeInfo.first = n; 
       nodeInfo.second = 2; //2 means keyRight
       return nodeInfo; 
    }

    //now assuming we don't have it, eeeeverything below is to take care of that
    //essentially we eventually return the info with where the unfound thing is closest to

    else if( (strcmp(word, n->keyLeft.first))==-1 ){
       //pre-emptively check the status of the left subtree
	  if(n->left->keyRight.second == 0){
	   //the tree doesn't have a key right, so we stay here and pre-emptively check
	   //if the value is less than keyLeft, that means the info I'll pass in for successor is keyRight flag, but node of n->left 
	   if( (strcmp(word, n->left->keyLeft.first))==-1 ){
            nodeInfo.first = n->left; 
	    nodeInfo.second = 2; //means keyRight
	   }else{
           //i'll pass in 1 for the successor, to say key left, and it'll be of the current node
	    nodeInfo.first = n;
	    nodeInfo.second = 1;
	   }//end of else
	  }//end of if keyRight.second is zero
	  else{
	   //if not, we can get the same word and try in the next tree down on the left
           getNodeInfo(word, n->left); 
	  }//end of else for if the keyRight is zero	
    } //end of smaller than left check 
 	
    
    else if( (strcmp(word, n->keyRight.first))==1 ){ 
	  //pre-emptively check the status of the right subtree
	  if(n->right->keyRight.second == 0){
	   //the tree doesn't have a key right, so we stay here and pre-emptively check, this will actually find PREDECSSEOR
	   //if the value is less than keyLeft, that means the info I'll pass in for PREDECESSOR is keyRight flag, but node of n 
	   if( (strcmp(word, n->right->keyLeft.first))==-1 ){
            nodeInfo.first = n; 
	    nodeInfo.second = 2; //means keyRight
	   }else{
           //i'll pass in 1 for the successor to say left and the current node
	    nodeInfo.first = n->right; 
	    nodeInfo.second = 1;
	   }//end of else
	  }//end of if keyRight.second is zero
	  else{
	   //if not, we can get the same word and try in the next tree down on the left
           getNodeInfo(word, n->right); 
	  }//end of else for if the keyRight is zero	  	
    }//end of else if 

	else{
	 //pre-emptively check the status of the middle subtree
	  if(n->middle->keyRight.second == 0){
	   //the tree doesn't have a key right, so we stay here and pre-emptively check
	   //if the value is less than keyLeft, that means the info I'll pass in for successor is keyRight flag, but node of n->middle 
	   if( (strcmp(word, n->middle->keyLeft.first))==-1 ){
            nodeInfo.first = n->middle; 
	    nodeInfo.second = 2; //means keyRight
	   }else{
           //i'll pass in 2 as the info, because it'll be the keyRight, but the n will be of the current node
	    nodeInfo.first = n; 
	    nodeInfo.second = 2;
	   }//end of else
	  }//end of if keyRight.second is zero
	  else{
	   //if not, we can get the same word and try in the next tree down on the left
           getNodeInfo(word, n->middle); 
	  }//end of else for if the keyRight is zero
	}

    //else, return the info for the getSuccessor, which SHOULD have one of these 
    return getNodeInfo(getSuccessorWord(nodeInfo.first,nodeInfo.second)); 
}//end of getNodeInfo


//go through everything, but only print if it's between the range
void TST::print(Node* n, string word1, string word2) const{
  if(n!=NULL){
    if(n->left) print(n->left,word1,word2); 
    if( (strcmp(n->keyLeft.first, word1))==1 && (strcmp(n->keyLeft.first, word2))=-1 ) cout<<n->keyLeft.first<<endl;
    if(n->middle) print(n->middle,word1,word2);
    if( (strcmp(n->keyRight.first, word1))==1 && (strcmp(n->keyRight.first, word2))=-1 ) cout<<n->keyRight.first<<endl;
    if(n->right) print(n->right,word1,word2);
  }
}

//do a range search given two words 
void TST::range_search(string word1, string word2){
  print(root,word1,word2); 
}//end of rangeSearch


// print tree data in-order, with helper
void IntBST::printInOrder() const {
    printInOrder(root);
}
void IntBST::printInOrder(Node *n) const {
    //check the edge cases first 
    if(n!=NULL){
      if(n->left){
        printInOrder(n->left); 
      }//end of n-left
      if(n->middle){
        printInOrder(n->middle); 
      }
       cout<<n->info<<" "; 
      if(n->right){
        printInOrder(n->right); 
      }//end of n-right
    }//end of null check     
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
TST::Node* TST::getNodeFor(string word, Node* n) const{
    //edge case 
    if(n==NULL) return n; 
    //if they're the same, return root 
    else if(n->info == value) return n;
    //check if we need to continue down the left side  
    else if(value <= n->info) return getNodeFor(value, n->left); 
    //or check if we need to continue down the right side
    else return getNodeFor(value, n->right); 
}

// returns true if value is in the tree; false if not
bool TST::contains(int value) const {
    //edge case
    if(getNodeFor(value, root)!=0){
     return true; 
    } 
    return false; 
}

/*
// returns the Node containing the predecessor of the given value
TST::Node* TST::getPredecessorNode(string word) const{   
	Node* n = getNodeFor(word, root); 
	Node* temp = 0; 
	if(n->left != 0){
          temp = n->left; 
	  while(temp->right != 0){
            temp = temp->right; 
	  }//end of while 
	  return temp; 
	}//end of if
        else{
         Node* temp2 = root;
	 Node* n2 = getNodeFor(value, root); 
	 while(temp2->info != n2->info){
           if(n2->info >= temp2->info){
              temp = temp2;
	      temp2 = temp2->right; 
	   }//end of inner if 
           else{
            temp2 = temp2->left; 
	   }//end of else 
	 }//end of while 
	 return temp;
	}	
	return root; 
}
 

// returns the predecessor 
//value of the given value or 0 if there is none
int IntBST::getPredecessor(int value) const{
    if(getPredecessorNode(value) != NULL){
      int valueToReturn = getPredecessorNode(value)->info;  
      return valueToReturn; 
    }else
    { 
    return 0;
    }
    return getPredecessorNode(value)->info; 
}
*/
/*
// returns the Node containing the successor of the given value
IntBST::Node* IntBST::getSuccessorNode(int value) const{
      Node* n = getNodeFor(value,root); 
      Node* temp = 0; 
      if(n->right != NULL){
        temp = n->right; 
	while(temp->left != NULL){
          temp = temp->left; 
	}//end of while 
	return temp; 
      } else{
        Node* temp2 = root; 
	Node* n2 = getNodeFor(value, root); //512 
	while(temp2->info != n2->info){
         if(n2->info <= temp2->info){
	  temp = temp2; 
	  temp2 = temp2->left; 
	 }//end of if check 
	  else{
           temp2 = temp2->right;
	  }
	}//end of second while 
         return temp; 	
      }
      return root;  
}


// returns the successor value of the given value or 0 if there is none
int IntBST::getSuccessor(int value) const{
    if(getSuccessorNode(value) != NULL){
      int valueToReturn = getSuccessorNode(value)->info; 
      return valueToReturn; 
    } 
    return 0; 
}



/*
// DELETE: deletes the Node containing the given word from the tree
// returns true if the node exists and was deleted or false if the node does not exist
bool TST::remove(string word){
   //check if it's a sole leaf 
   if(root == NULL || getNodeFor(word,root) == NULL ) return false;
   else{
    if(root->left == NULL && root->right == NULL){
       delete root;
       root = NULL;  
       return true;
    }
    else if(root->left == NULL){
       Node* temp = root; 
       root = root->right; 
       delete temp;  
       return true; 
    } else if (root->right == NULL){
       Node* temp = root;
       root = root->left;
       delete temp; 
       return true; 
    } else {
      return true; 
    } 
   }
   return false;
   */ 