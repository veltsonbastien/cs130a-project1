// project1.cpp
// Implements class TST
//Veltson Bastien
//10/16/2020


#include "project1.h"
#include <iostream>
#include <utility>
#include <cstring>
#include <vector>

using namespace std; 
using std::cout;
using std::string;


// default constructor sets up empty tree
TST::TST() : root(0) { }


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
    	if( word.compare(n->keyLeft.first)==0){
        cout<<word<<" found, count = "<<n->keyLeft.second<<endl;
	return;
	}//if it's in the key left
        //or is it found in key right
	else if( word.compare(n->keyRight.first)==0){
       	cout<<word<<" found, count = "<<n->keyRight.second<<endl; 
	return;
    	}

        //first check left and right entries to see if it has a chance at even being in this node - if not, try in another place zibs
    	if( (word.compare(n->keyLeft.first))<0 ) lookup(word,n->left);  //check if it's negative one, (means smaller) ain't boutta be in here
	//next check if there is a keyRight value 
	else if((n->keyRight.second!=0) && (word.compare(n->keyRight.first))>0) lookup(word, n->right); 

	else{
	//now if it passed through all of those, we can throw it into the middle and let it recursively take care of itself 
    	lookup(word, n->middle); 
	}
        
    } //end of NULL NODE check 
    else{
     //if node doesn't exist, you know what to do
     //it's not here, so say that
       cout<<word<<" not found"<<endl;
   } //end of else check for that boi


}//end of lookup function


// insert main function
void TST::insert(string word) {
    // handle special case of empty tree first
    if (!root){
	root = new Node(word);  
	cout<<word<<" inserted, new count = "<<1<<endl;
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
    if( ((word.compare(n->keyLeft.first))==0 )){ n->keyLeft.second++ ; cout<<word<<" inserted, new count = "<<n->keyLeft.second<<endl; return; }
 
    //next check if there is a keyRight value 
	//if there isn't handle it properly
       if(n->keyRight.second == 0){
	   //if the value is less than keyLeft, switch keyLeft and keyRight
	   if((word.compare(n->keyLeft.first))<0 ){ 
	  
	    n->keyRight.first = n->keyLeft.first;
	    n->keyRight.second = n->keyLeft.second; 
	    n->keyLeft.first = word;
	    n->keyLeft.second = 1;  
	   }else{
           //put it in keyRight
	   n->keyRight.first = word;
	   n->keyRight.second = 1; 
	   }//end of else
           cout<<word<<" inserted, new count = "<<1<<endl;
	   return;
	} //end of if keyright is zero

        //cout<<"word test: "<<word<<" , "<<n->keyRight.second<<endl;

       if((word.compare(n->keyRight.first))==0){ n->keyRight.second = (n->keyRight.second)+1; cout<<word<<" inserted, new count = "<<n->keyRight.second<<endl; return; }
       //cout<<"word: "<<word<<" , "<<n->keyRight.second<<endl;


    	//Next we working on checking left and right entries to see if it has a chance at even being in this node - if not, try in another place zibs
       if(( word.compare(n->keyLeft.first))<0 ){
	  if(n->left==nullptr){
	   n->left = new Node(word);
	   n->left->parent = n; 
	   cout<<word<<" inserted, new count = "<<1<<endl;
	   return;
	  } else {
	   return insert(word,n->left); 
	  } //check if it's negative one, (means smaller) ain't boutta be in here
	}//end of smaller than left check

	else if(( word.compare(n->keyRight.first))>0 ){ 
	  //check if it's one, (that means bigger) it ain't boutta be in here  
	  if(n->right==nullptr){
	    n->right = new Node(word);
	    n->right->parent = n;
            cout<<word<<" inserted, new count = "<<1<<endl;
	   return;


	  }else{
	  insert(word, n->right);
	  }	  
	}//end of else if 
	else{
	//now if it passed through all of those, we can throw it into the middle and let it recursively take care of itself 
    	 if(n->middle==nullptr){
	   n->middle = new Node (word);
	   n->middle->parent = n; 
           cout<<word<<" inserted, new count = "<<1<<endl;
	   return;

         } else{
	 insert(word, n->middle); 
	 }
	}

    } //end of NULL NODE check 
    else{
     //if node doesn't exist, you know what to do
     n = new Node(word);  
    } //end of else check for that boi

} //end of check


//go through everything, but only print if it's between the range
void TST::print(Node* n, string word1, string word2) const{
   if(n!=nullptr){
    if(n->left) print(n->left,word1,word2); 
    if( ((n->keyLeft.first.compare(word1))>0 && (n->keyLeft.first.compare(word2))<0 ) || ((n->keyLeft.first.compare(word1))==0 || (n->keyLeft.first.compare(word2))==0 )) cout<<n->keyLeft.first<<endl;
    if(n->middle) print(n->middle,word1,word2);
    if( ((n->keyRight.first.compare(word1))>0 && (n->keyRight.first.compare(word2))<0) || ((n->keyRight.first.compare(word1))==0 || (n->keyRight.first.compare(word2))==0 )) cout<<n->keyRight.first<<endl;
    if(n->right) print(n->right,word1,word2);
 }
}

//do a range search given two words 
void TST::range_search(string word1, string word2){
  print(root,word1,word2); 
}//end of rangeSearch




//the main function and everything we need to actually use this big boi

//split commands gets me a vector with all the commands that were separated by commas
vector<string> TST::splitCommands(string input, string token){
    vector<string> result;
    while(input.length()){
        int index = input.find(token);
        if(index!=string::npos){
            result.push_back(input.substr(0,index));
            input = input.substr(index+token.size());
            if(input.size()==0)result.push_back(input);
        }else{
            result.push_back(input);
            input = "";
        }
    }
    return result;
}


int main(int argc, char *argv[]){
  //instantiate a new tree right at the beginning
  TST tree; 
  //make a temporary commands vector 
  vector<string> commandsVector = tree.splitCommands(std::string(argv[1]),", ");
 
  for (int i = 0; i<commandsVector.size(); i++){
      //temporarily make a vector for the command at hand 
      vector<string> tempCommand;
      string token = " ";     
      while((commandsVector.at(i)).size()){
        int index = (commandsVector.at(i)).find(token);
        if(index!=string::npos){
            tempCommand.push_back((commandsVector.at(i)).substr(0,index));
            commandsVector.at(i) = (commandsVector.at(i)).substr(index+token.size());
            if((commandsVector.at(i)).size()==0)tempCommand.push_back(commandsVector.at(i));
        }else{
            tempCommand.push_back(commandsVector.at(i));
            commandsVector.at(i) = "";
        }//end of else
       } //end of while loop filling the temp vector
      
     //now look at what the command is and do it 
     //if it's lookup, you only need to pass in the next index of the vector as the parameter
     if((tempCommand.at(0)).compare("lookup") == 0){  
       tree.lookup(tempCommand.at(1));
     }
     //if it's insert, you only need to pass in the next one 
     else if((tempCommand.at(0)).compare("insert") == 0){
       tree.insert(tempCommand.at(1));
     }
     else if((tempCommand.at(0)).compare("range_search") ==0){
       //make sure both get turned to chars 
       tree.range_search(tempCommand.at(1), tempCommand.at(3)); 
     }
   }//end of for loop

  return 0; 
  }
