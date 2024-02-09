#include <string>
#include <fstream>
#include "HashTable.h"

HashTable::HashTable()
{
  for(int i = 0; i  < table_size; i++)
  {
    HT[i] = new Element; //allocating each pointer (HT[i]) as an Element type

    HT[i]->word = ""; //initializing each pointer to word with ""

    HT[i]->counter = 0; //initializing each pointer to counter to 0
  }

}

HashTable::~HashTable()
{
  for(int i = 0; i < table_size; i++)
  {
    if(HT[i]->word != "")
      delete HT[i];
  }
  //deleting each pointer that is not null!
}

unsigned int HashTable::HashFunction(std::string key)
{
  unsigned int index = 0;

  int seed = 131; //using a seed parameter to prevent hash collisions for different data

  for(int i = 0; i < (int)key.length(); i++)
  {
    index = (index * seed) + key[i];
  }
  //Hash Function: Each ASCII number of string s is being added with the current index * seed 
  return index % table_size;
}

void HashTable::AddString(std::string key)
{

  float start=clock();
  unsigned int index = HashFunction(key); //call HashFunction to get the index

  if(HT[index]->word == "") //That means that HT[index] is empty
  {
    //occupying index...//
    HT[index]->word = key;
    HT[index]->counter = 1;
  }
  else //That means that HT[index] is already occupied so there are 2 possible cases:
  {
    if (HT[index]->word == key) //if string key is equal to the HT[index]->word then we just increase the counter by 1
      {
        HT[index]->counter += 1;
      }
    else //in the else statement it means that we came up with a collision
    {
      AvoidCollision(index); //call AvoidCollision(index) to update the value of index(see line 74-81)

      //occupying the correct space

      HT[index]->word = key;

      HT[index]->counter = 1;
    }
  }
  timeOfHash+=timecount(start);
}

void HashTable::searchHashTable(string *Q)
{
  string key;
  float begin=clock();
  cout<<endl<<"\t\t\t\t\tHASHTABLE"<<endl;
  cout<<"time of creation: "<<timeOfHash<<endl;
  for(int i=0;i<1000;i++){
    key=Q[i];
    unsigned int index = HashFunction(key); //call HashFunction to get the index of string key
    while (HT[index]->word != key)
     {
      index++;  //update the index until HT[index]->word is equal to key!
    }
    cout<<HT[index]->word<<" "<<HT[index]->counter<<endl;
  }
  float time=timecount(begin);
  cout<<endl<<"time: "<<time<<endl;
}

void HashTable::AvoidCollision(unsigned int & index) //call by reference
{
  while(HT[index]->word != "")
  {
    index++;  //just a linear probing
  }
  index %= table_size; //update index
}