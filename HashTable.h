#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <string>
#include <fstream>
#include "Tree.h"

struct Element
{
  int counter; //counter variable is used to save how many times the word is saved in the Hash Table
  std::string word; 
};

class HashTable : public Tree
{
  private:
    static const int table_size = 200000; //static version of the Hash Table

    Element* HT[table_size]; //declaring it as a pointer because in each node both word and counter variables are going to be saved

    unsigned int HashFunction(std::string); //Function that returns the correct Element`s index

    void AvoidCollision(unsigned int&); //if an element should be entered in an index that is occupied then its' index should be changed(I used linear probing to avoid collision)

  public:
    float timeOfHash=0;

    HashTable(); //Base constructor

    ~HashTable(); //Destructor

    void AddString(std::string); //Method that adds elements to the hash table

    void searchHashTable(string*); //Method for searching hash table elements

    using Unclassified :: timecount; //using the time count method from the Unclassified class

};

#endif // HASHTABLE_H
