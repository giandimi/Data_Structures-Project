#ifndef UNCLASSIFIED_H
#define UNCLASSIFIED_H

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

/**the class of the unclassified array**/

class Unclassified
{
  private:
    
    int n; //the size of the unclassified array
    string *Array{}; //the unclassified array
 public:
    float timeOfArray=0;

    Unclassified(int num); //constructor with the size of the array as an argument

    ~Unclassified(); //destructor

    string getword(int num); //returns the content of the given position of the array

    void setword(int num,string word); //sets the given cell with the given word

    void removeUnclassified(int num); //deletes the content of the given cell

    void searchUnclassified(string *Q); //counts and prints the number of impressions of each word from the Q array in the unclassified array

    float timecount(float begin); //calculates the time of previous function

};


#endif 