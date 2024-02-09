#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <fstream>
#include "Unclassified.h"

using namespace std;

struct node
{
  string key; //value of node
  node* left; //left child
  node* right; //right child
  int count; //number of the same word
  int height; //the height of the node (for AVL tree)
};

class Tree : public Unclassified
{
  private:
    node* root; //the root of tree

  protected:
    node* CreateLeaf(string); // Create a leaf.
    void addLeafPriv(string, node*); // Add a leaf to the tree with  specific value.
    node* searchTreePriv(string, node*); // Find a leaf with specific value.

    void DeleteNodePriv(string, node*); // Delete a node.

    // Helper Functions For DeleteNodePriv.
    node* FindMin(node*); // Find the node with the smallest value.
    void DeleteRoot(); // Delete the root.
    void DeleteMatch(node*, node*, bool); // Delete a node except root.
    // bool: It points if a current node is a left(true) or right(false) child.

    // Tree traversals.
    void InOrderPriv(node*); //InOrder traversal.
    void PreOrderPriv(node*); //PreOrder traversal.
    void PostOrderPriv(node*); //PostOrder traversal.

  public:
    Tree();

    float timeOfTree=0;
    //these functions call the same private function.
    //They are helpers for passing only the value of node for easier use from main.
    virtual void addLeaf(string);
    virtual void searchTree(string*);
    virtual void DeleteNode(string);

    // Tree traversals.
    virtual void InOrder();
    virtual void PreOrder();
    virtual void PostOrder();

    using Unclassified::timecount;

};
#endif // TREE_H
