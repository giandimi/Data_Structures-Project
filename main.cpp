#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>
#include <ctime>
#include "Unclassified.h" 
#include "Classified.h"
#include "Tree.h"
#include "AVLTree.h"
#include "HashTable.h"
#include <chrono>

using namespace std;

/** function that gets as an argument a word 
removes the special characters from it */

string  removePunct(string word) {

  word.erase(remove(word.begin(), word.end(), ':'), word.end());
  word.erase(remove(word.begin(), word.end(), ','), word.end());
  word.erase(remove(word.begin(), word.end(), '-'), word.end());
  word.erase(remove(word.begin(), word.end(), '.'), word.end());
  word.erase(remove(word.begin(), word.end(), '!'), word.end());
  word.erase(remove(word.begin(), word.end(), '?'), word.end());
  word.erase(remove(word.begin(), word.end(), ';'), word.end());
  word.erase(remove(word.begin(), word.end(), '_'), word.end());
  word.erase(remove(word.begin(), word.end(), '='), word.end());
  word.erase(remove(word.begin(), word.end(), '+'), word.end());
  word.erase(remove(word.begin(), word.end(), '/'), word.end());
  word.erase(remove(word.begin(), word.end(), '"'), word.end());
  word.erase(remove(word.begin(), word.end(), '&'), word.end());
  word.erase(remove(word.begin(), word.end(), '%'), word.end());
  word.erase(remove(word.begin(), word.end(), '%'), word.end());
  word.erase(remove(word.begin(), word.end(), '`'), word.end());
  word.erase(remove(word.begin(), word.end(), '^'), word.end());
  word.erase(remove(word.begin(), word.end(), '('), word.end());
  word.erase(remove(word.begin(), word.end(), ')'), word.end());
  word.erase(remove(word.begin(), word.end(), '['), word.end());
  word.erase(remove(word.begin(), word.end(), ']'), word.end());
  word.erase(remove(word.begin(), word.end(), '@'), word.end());
  word.erase(remove(word.begin(), word.end(), '#'), word.end());
  word.erase(remove(word.begin(), word.end(), '*'), word.end());
  word.erase(remove(word.begin(), word.end(), '~'), word.end());
  word.erase(remove(word.begin(), word.end(), '1'), word.end());
  word.erase(remove(word.begin(), word.end(), '2'), word.end());
  word.erase(remove(word.begin(), word.end(), '3'), word.end());
  word.erase(remove(word.begin(), word.end(), '4'), word.end());
  word.erase(remove(word.begin(), word.end(), '5'), word.end());
  word.erase(remove(word.begin(), word.end(), '6'), word.end());
  word.erase(remove(word.begin(), word.end(), '7'), word.end());
  word.erase(remove(word.begin(), word.end(), '8'), word.end());
  word.erase(remove(word.begin(), word.end(), '9'), word.end());
  word.erase(remove(word.begin(), word.end(), '0'), word.end());
  word.erase(remove(word.begin(), word.end(), '\n'), word.end());
  word.erase(remove(word.begin(), word.end(), ' '), word.end());

  return word;
}

/** gets a string as an argument
 and returns it with lower letters*/ 

string LowL(string word){
  transform(word.begin(), word.end(), word.begin(),::tolower);
  return word;
}

/**The main function */

int main() {

  fstream myFile; //new fstream file
  myFile.open("myFile.txt",ios::in); //open file

  if(!myFile) //if it doesn't find it
  {
    cout<<"File not found";
  }
  else
  {
    int num=0; //counter of the content of the file
    string word; //temporary string that saves the words from the file

    while(!myFile.eof()) //while it is not the end of the file->read
    {
      myFile>>word;
      num++;
    }
    cout<<"number of words: "<<num<<endl;

    fstream myFile;
    myFile.open("myFile.txt",ios::in); //new file

    Unclassified Array(num); //create unclassified_array
    Classified arr(num); //create classified array
    Tree tree; //create tree 
    AVLTree avl; //create AVL tree
    HashTable hash; //create hashtable
    

    int i=0;
    while(!myFile.eof() && i<num)
    {
      myFile>>word; //word reads from file

      word=LowL(word); //Lowl lowers the letters of "word"
      word=removePunct(word); //removePunct removes special characters from "word"
      if (word.length()>0) /*if word is not "" is been added to all of following the structures*/
      {
        arr.setword(i,word);
        tree.addLeaf(word);
        avl.addLeaf(word);
        hash.AddString(word);
        i++;
      }
    }

    string Q[1000]; //array that conteins 1000 random string from file
    int w=0;
    while (w<1000)
    {
      Q[w]=Array.getword(rand() % (num-1));//random strings from file are being added to Q array
      if(Q[w].length()>0){
        w++; //if the cell is not empty then increase w
      }
    }
    Array.searchUnclassified(Q); //calls serial search for unclassified array
    arr.searchClassified(Q); //calls binary search for classified array
    tree.searchTree(Q); //calls search for binary tree
    avl.searchTree(Q); // calls search for AVL tree
    hash.searchHashTable(Q); //calls for hashtable
    /*the fuctions print the number of impressions of every string from Q array and the time they spent to do it*/
  }
  myFile.close(); //close file

  return 0;
}