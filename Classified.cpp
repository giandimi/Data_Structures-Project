 #include "Classified.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>
#include <bits/stdc++.h>
#include <ctime>
#include "Unclassified.h"


using namespace std;

Classified :: Classified(int num) : Unclassified(num) //constructor
{
  n=num;
  orderArray=new string[n];
}

Classified :: ~Classified() //destructor
{
  delete[] orderArray;
}


string Classified :: getword(int num){ //getter
  return orderArray[num];
}

void Classified :: setword(int num,string word){ //setter
  float start=clock();
  orderArray[num]=word;
  timeOfOrderArray+=timecount(start);
}

void Classified :: removeClassified(int num) //deletes element from the ordered array
{
  orderArray[num]='\0'; //sets the given element to \0;
}

void Classified :: swap (int s1, int s2)//swaps the content of 2 elements of the array
{
  string t=orderArray[s1];
  orderArray[s1]=orderArray[s2];
  orderArray[s2]=t;
}

int Classified  :: Partition (string orderArray[],int low,int high) //devides the array in to smallers to classify them
{
  string pivot = orderArray[high]; //sets the pivot to the value of the last position
  int i = (low - 1); //sets i to first position -1

  for (int j = low; j < high; j++)
  {
    if (orderArray[j].compare(pivot)<0) //if the content of j is smaller than pivot, then swap i,j
    {
      i++;
      swap(i,j); 
    }
  }
  swap(i+1 , high); //swaps the content of i+1 with the content of the last position of array
  return (i + 1);
}

int Classified :: partition_r(string orderArray[], int low, int high) //calls the partition function with a random pivot
{
  srand(time(NULL));
  int random = low + rand() % (high - low);
  swap(random,high);
  return Partition(orderArray, low, high);
}

void Classified :: OrderClassified(int low,int high) //calssifies the elements of the array //low, high: borders of array
{
  if (low < high)
  {
    int pi = partition_r(orderArray, low, high); //calls partition r function and sets the result in to pi

    OrderClassified(low, pi - 1); //calls itself with pi as upper limit of array
    OrderClassified(pi + 1, high); //calls itself with pi as lower limit of array
  }
}

void Classified :: searchClassified (string *Q) //searches all the words of Q array in the main array using binary search and counts the number of impressions of each one
{
  
  OrderClassified(0, this->n-1); //calls the order function to clssify the elements before the search
  
  int L=0,R=n,M,count[1000]; //L, R: the borders of the array of the binary search
  bool D=false; //returns true if it finds the word, false
  for (int j=0;j<1000;j++){
    count[j]=0; //sets the elements of the count array to 0
  }
  float begin =clock(); //starts the clock
  for(int i=0;i<1000;i++)
  {
    while(D==false && L<=R)
    {
      M=(L+R)/2; //sets M to the middle element of the array
      if (orderArray[M]==Q[i]) //compares the Q[i] to all the elements of the array until it finds the word
      {
        D=true;
        
        int p=M+1;
        while(orderArray[M]==Q[i]) //starts serial search to find all the impression after M
        {
          count[i]++;
          M--;
        }
        M=p-1;
        while(orderArray[p]==Q[i]) //starts serial search to find all the impression before M
        {  
          count[i]++;
          p++;             
        } 
      }
      else if (orderArray[M]<Q[i]){
        L=M+1; // picks the right array 
      }
      else{
        R=M-1; //picks the left array
      }
    }
    L=0;
    R=n;
    D=false;
  }
  float time=timecount(begin); // saves the time of function
  cout<<endl<<"\t\t\t\t\tCLASSIFIED"<<endl;
  cout<<"time of creation: "<<timeOfOrderArray<<endl;
  for (int i=0;i<1000;i++)
  {
    cout<<Q[i]<<" "<<count[i]<<endl; //prints the words and their number of impression
  }
  cout<<endl<<"time: "<<time<<endl; //prints the time
  
}