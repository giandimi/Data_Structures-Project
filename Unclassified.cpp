#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>
#include <bits/stdc++.h>
#include <ctime>
#include "Unclassified.h"

using namespace std;


Unclassified :: Unclassified(int num)
{
  n=num;
  Array=new string[n];
}

Unclassified :: ~Unclassified()
{
  delete[] Array;
}

void Unclassified :: removeUnclassified(int num)
{
  Array[num]=Array[n-1]; //copies the content of the last element to the given position
  Array[n-1]='\0'; //sets the last element to \0;
}
void Unclassified :: setword(int num,string word){
  float start=clock();
  Array[num]=word;
  timeOfArray+=timecount(start);
}

string Unclassified :: getword(int num){
  return Array[num];
}

void Unclassified :: searchUnclassified(string *Q)
{
  int count[1000]; //array with the number of impressions of every word from the Q array

  for(int c=0;c<1000;c++){ //sets all the elements of the count array to 0
    count[c]=0;
  }

  float begin=clock(); //the begining time 

  for(int w=0;w<1000;w++){ 
    for (int i=0;i<n;i++)
    {
      if (Array[i].compare(Q[w])==0){ //serial search
        count[w]++; 
      }
    }
  }
  float time=timecount(begin); // end of time

  cout<<endl<<"\t\t\t\t\tUNCLASSIFIED"<<endl;
  cout<<"time of creation: "<<timeOfArray<<endl;

   for (int i=0;i<1000;i++)
    {
      cout<<Q[i]<<" "<<count[i]<<endl; // prints the words of Q array and the number of their impressions
    }
    cout<<endl<<"time: "<<time<<endl; //prints the calculated time of the serial search
}


float Unclassified :: timecount(float begin) 
{
  return float(clock()-begin)/CLOCKS_PER_SEC; //calculates the time of the serial search
}
