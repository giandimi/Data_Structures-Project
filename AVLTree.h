#ifndef AVLTREE_H
#define AVLTREE_H

#include "Tree.h"

using namespace std;

class AVLTree : public Tree
{
  private:
    node* root;

    node* addLeafPrivAVL(string, node*); // Add a leaf to the tree with specific value.
    // Helper Functions for addLeafPriv
    int Height(node*); //Return the height of a node.
    int max(int, int); //Return the max int variable of 2 int variables.
    node* RightRotation(node* &); //Right rotation of the tree.
    node* LeftRotation(node* &); //Left Rotation of the tree.
    node* doubleRightRotation(node* &); //Double right rotation of the tree.
    node* doubleLeftRotation(node* &); //Double left rotation of the tree.

    node* DeleteNodePrivAVL(string,node*);// Delete a node.
    node* min(node*); // Find the node with the smallest value.
  
  public:
    AVLTree(); //empty constructor

    float timeOfAVL=0;
    
    //these functions call the same private function.
    //They are helpers for passing only the value of node for easier use from main.
    void addLeaf(string)override;
    void searchTree(string*)override;
    void DeleteNode(string)override;

    // Tree traversals.
    void InOrder()override;
    void PreOrder()override;
    void PostOrder()override;

    using Unclassified :: timecount;
};

#endif // AVLTREE_H