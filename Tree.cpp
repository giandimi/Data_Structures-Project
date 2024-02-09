#include "Tree.h"


using namespace std;
Tree::Tree() : Unclassified(0)// Empty Constructor.
{
  root=NULL; //Set NULL to root.
}

node* Tree::CreateLeaf(string key) //Create a new Node.
{
  node *n= new node; //Make the node.
  n->key=key; //Set the key to the new Node.
  n->left=NULL; //Set NULL to right child.
  n->right=NULL; //Set NULL to left child.
  n->count=1; //Initializes the count to 1 as the key of this node exists once .
  n->height=0; //Initializes height to 0.

  return n;
}

void Tree::addLeaf(string key) //Call the private function.
{
  float start=clock();
  addLeafPriv(key, root);
  timeOfTree+=timecount(start);
}

void Tree::addLeafPriv(string key, node* pointer) //Add a leaf to the tree.
{
  if (pointer==NULL){
    root=CreateLeaf(key); //If the tree is empty set the root first.
  }
  else if (key < pointer->key) //If the key is less than current key of the node.
  {
    if (pointer->left!=NULL) //Check if the left node key is NULL.
    {
      addLeafPriv(key, pointer->left); //If its not go left.
    }
    else{
      pointer->left=CreateLeaf(key); //Otherwise create a new leaf with the key.
    }
  }
  else if (key > pointer->key) //If the key is higher than current key of the node.
  {
    if (pointer->right!=NULL) //Check if the right node key is NULL.
    {
      addLeafPriv(key, pointer->right); //If its not go right.
    }
    else{
      pointer->right=CreateLeaf(key); //Otherwise create a new leaf with the key.
    }
  }
  else //If the key is equal to current key of the node.
  {
    pointer->count+=1; //Increase the number of the current node plus 1.
  }
}

void Tree::searchTree(string *Q) //Call the private function.
{
  string key;
  float begin=clock();
  cout<<endl<<"\t\t\t\t\tTREE"<<endl;
  cout<<"time of creation: "<<timeOfTree<<endl;
  for(int i=0;i<1000;i++)
  {
    key=Q[i];
    node* temp;
    temp=searchTreePriv(key,root);
    
    if (temp!=NULL) //if you want to show the results
      cout<<temp->key<<" "<<temp->count<<endl;
    else
      cout<<"The Word "<<key<<" didn't found in the tree!"<<endl;
  }
  float time=timecount(begin);
  cout<<endl<<"time: "<<time<<endl;
}

node* Tree::searchTreePriv(string key, node* pointer)
{
  if (pointer!=NULL) //If the current node exists
  {
    if (pointer->key==key) //If the key we look is the key we got.
    {
      return pointer; //return the node.
    }
    else //Otherwise.
    {
      if (pointer->key>key) //If the key we look is less than the current key of the node.
      {
        return searchTreePriv(key,pointer->left); //Go left
      }
      else //Otherwise.
      {
        return searchTreePriv(key,pointer->right); //Go right.
      }
    }

  }
  else //If its not
  {
    return NULL;
  }
}

void Tree::DeleteNode(string key) //Call the private function.
{
  DeleteNodePriv(key, root);
}

void Tree::DeleteNodePriv(string key, node* pointer)
{
  if (root!=NULL) //If the tree is not empty;
  {
    //Case 1: Delete Root.
    if (key==root->key) //If key is equal to root's key;
    {
      if (root->count>1) //If the worst exist more than one.
      {
        root->count-=1; //Decrease the count of the node.
      }
      else //Otherwise.
      {
        DeleteRoot(); //Call a helper function.
      }
    }
    // Case 2: Delete another node.
    else if (key<pointer->key && pointer->left!=NULL) //If the key is less than current key and the left child isn't NULL.
    {
      if (pointer->left->key==key) //If the key of the left child is the key we look.
      {
        if (pointer->left->count>1) //If the count is greater than one.
        {
          pointer->left->count-=1; //Reduce it by one.
        }
        else //Otherwise
        {
          DeleteMatch(pointer, pointer->left, true); //Call helper function.
        }
      }
        else //Otherwise.
        {
          DeleteNodePriv(key, pointer->left); //Go left.
        }
    }
    else if (key>pointer->key && pointer->right!=NULL) //If the key is greater than current key and the right child isn't NULL.
    {
      if (pointer->right->key==key) //If the key of the right child is the key we look.
      {
        if (pointer->right->count>1) //If the count is greater than one.
        {
          pointer->right->count-=1; //Reduce it by one.
        }
        else //Otherwise.
        {
          DeleteMatch(pointer, pointer->right, false); //Call helper function.
        }
      }
        else //Otherwise.
        {
          DeleteNodePriv(key, pointer->right); //Go right.
        }
    }
    else //Otherwise the key doesn't exist.
    {
      cout<<"The Word "<<key<<" didn't found in the tree!"<<endl;
    }
  }
  else //Otherwise the tree is empty.
  {
    cout<<"The tree is empty!"<<endl;
  }
}

// Helper Functions For DeleteNodePriv.


node* Tree::FindMin(node* pointer) //Find the min.
{
  if (root!=NULL) //If the tree isn't empty.
  {
    if (pointer->left==NULL) //If the left child is NULL.
    {
      return pointer; //Return the node which is the min node.
    }
    else //Otherwise.
    {
      return FindMin(pointer->left); //Go left.
    }
  }
  else //If it is.
  {
    cout<<"The tree is empty!"<<endl;
    return NULL;
  }
}

void Tree::DeleteRoot() // Delete the root.
{
  node* TempMinPointer; //A temporarily node to say the min node.
  string TempMinKey; //A temporarily variable to save the min key.

  //case 0: 0 Children.
  if (root->left==NULL && root->right==NULL) //If the root don't have children.
  {
    root=NULL; //Set root NULL.
  }
  //case 1: 1 Child.
  else if (root->left!=NULL && root->right==NULL) //If the root have a single left child.
  {
    root=root->left; //The root is the left child.
  }
  else if (root->left==NULL && root->right!=NULL) //If the root have a single right child.
  {
    root=root->right; //The root is the right child.
  }
  //case 2: 2 Children.
  else
  {
    TempMinPointer=FindMin(root->right); //Save the min node.
    TempMinKey=TempMinPointer->key; //Save the key of the min node.
    DeleteNodePriv(TempMinKey, root); //Delete the min node.
    root->key=TempMinKey; //Set the root key to min key.
    root->count=TempMinPointer->count; //Set the root counter to min counter.
  }
}

void Tree::DeleteMatch(node* parent, node* Match, bool left) //Delete a node except root.
{
  node* TempMinPointer; //A temporarily node to say the min node.
  string TempMinKey; //A temporarily variable to save the min key.

  //Case 0: 0 Children.
  if (Match->left==NULL && Match->right==NULL) //If the node don't have children.
  {
    left==true?parent->left=NULL:parent->right=NULL; //If the node is the left child of his parent set the left child of his
    delete Match;   //Delete the node.               //parent to NULL, else set the right child of his parent to NULL.
  }
  //Case 1: 1 Child.
  else if (Match->left!=NULL && Match->right==NULL) //If the node have a single left child.
  {
    left==true?parent->left=Match->left:parent->right=Match->left; //If the node is the left child of his parent set the
    delete Match;  //Delete the node.                              //left child of his parent to left child of match(node),
    //else set the right child of his parent to left child of match(node).
  }
  else if (Match->left==NULL && Match->right!=NULL) ////If the node have a single right child.
  {
    left==true?parent->left=Match->right:parent->right=Match->right; //If the node is the left child of his parent set the
    delete Match;  //Delete the node                                 //left child of his parent to right child of match(node),
  }                                                                    //else set the right child of his parent to right child of match(node).
  //Case 2: 2 Children.
  else
  {
    TempMinPointer=FindMin(Match->right); //Save the min node.
    TempMinKey=TempMinPointer->key; //Save the key of the min node.
    DeleteNodePriv(TempMinKey, Match); //Delete the min node.
    Match->key=TempMinPointer->key; //Set the match(node) key to min key.
    Match->count=TempMinPointer->count; //Set the match(node) counter to min counter.
  }
}

// Tree traversals.

void Tree::InOrder() //Call the private function.
{
  InOrderPriv(root);
}

void Tree::InOrderPriv(node* pointer) //InOrder function.
{
  if (pointer!=NULL) //If the current node isn't NULL.
  {
    if (pointer->left!=NULL)
    {
      InOrderPriv(pointer->left); //Go left.
    }
    cout<<pointer->key<<"["<<pointer->count<<"]"<<endl; //print the node's key, counter.
    if (pointer->right!=NULL)
    {
      InOrderPriv(pointer->right); //Go right.
    }
  }
  else //Otherwise.
  {
    cout<<"The tree is empty!"<<endl;
  }
}

void Tree::PostOrder() //Call the private function.
{
  PostOrderPriv(root);
}

void Tree::PostOrderPriv(node* pointer) //PostOrder function.
{
  if (pointer!=NULL) //If the current node isn't NULL.
  {
    if (pointer->left!=NULL)
    {
      PostOrderPriv(pointer->left); //Go left.
    }
    if (pointer->right!=NULL)
    {
      PostOrderPriv(pointer->right); //Go right.
    }
    cout<<pointer->key<<"["<<pointer->count<<"]"<<endl; //print the node's key, counter.
  }
  else //Otherwise.
  {
    cout<<"The tree is empty!"<<endl;
  }
}

void Tree::PreOrder() //Call the private function.
{
  PreOrderPriv(root);
}

void Tree::PreOrderPriv(node* pointer) //PreOrder function.
{
  if (pointer!=NULL) //If the node isn't NULL.
  {
    cout<<pointer->key<<"["<<pointer->count<<"]"<<endl; //print the node's key, counter.
    if (pointer->left!=NULL)
    {
      PreOrderPriv(pointer->left); //Go left.
    }
    if (pointer->right!=NULL)
    {
      PreOrderPriv(pointer->right); //Go right.
    }
  }
}