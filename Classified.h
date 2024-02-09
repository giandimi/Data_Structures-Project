#ifndef CLASSIFIED_H
#define CLASSIFIED_H

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>
#include "Unclassified.h"

using namespace std;

/**the class of the classified array**/

class Classified : public Unclassified
{
  private:
    int n; //the size of the unclassified array
    string *orderArray{}; //the classified array

  public:
    float timeOfOrderArray=0;

    Classified(int num); //constructor with the size of the array as an argument

    ~Classified(); //destructor

    string getword(int num); //returns the content of the given position of the array

    void setword(int num,string word); //sets the given cell with the given word

    void removeClassified(int num); //deletes the content of the given cell

    void OrderClassified(int low,int high); //sorts the elements of the array

    int partition_r(string orderArray[], int low, int high); //picks randomly the pivot

    int Partition(string orderArray[],int low,int high); //devides the array for the sorting

    void swap(int s1,int s2); //swaps the content of the given strings

    void searchClassified(string *Q); //counts and prints the number of impressions of each word from the Q array in the classified array

    using Unclassified::timecount;
};






#endif