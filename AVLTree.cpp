#include "AVLTree.h"
#include <fstream>

using namespace std;

AVLTree::AVLTree() //Empty Constructor , call the AVL constructor.
{
  root=NULL; //Set NULL to root.
}

void AVLTree::addLeaf(string key) //Call the private function.
{
  float start=clock();
  root = addLeafPrivAVL(key,root);
  timeOfAVL+=timecount(start);
}

node* AVLTree::addLeafPrivAVL(string key, node* pointer) //Add a leaf to the AVL tree.
{
  if (pointer == NULL)
  {
    pointer = CreateLeaf(key); //Create a new leaf with the key.
  }
  else if (key < pointer->key) //If the key is less than current key of the node.
  {
    pointer->left = addLeafPrivAVL(key,pointer->left); //Go left.

    if (Height(pointer->left) - Height(pointer->right) == 2) //If the subtraction of height of left and height of right child is equal to two.
    {
      if(key < pointer->left->key) //If the key is less than the left child of the current node.
        pointer = RightRotation(pointer); //Do right rotation.
      else{
        pointer = doubleRightRotation(pointer); //Do double right rotation.
      }
    }

  }
  else if (key > pointer->key) //If the key is higher than current key of the node.
  {
    pointer->right = addLeafPrivAVL(key,pointer->right); //Go right.

    if (Height(pointer->right) - Height(pointer->left) == 2) //If the subtraction of height of right and height of left child is equal to two.
    {
      if (key > pointer->right->key){//If the key is higher than the left child of the current node.
        pointer = LeftRotation(pointer); //Do left rotation.
      }
      else{
        pointer = doubleLeftRotation(pointer); //Do double left rotation.
      }
    }
  }
  else //Otherwise.
  {
    pointer->count += 1; //Increase the number of the current node plus 1.
  }
  pointer->height = max(Height(pointer->left), Height(pointer->right))+1; //Set to the height, the max height of left or right child and add 1.

  return pointer;
}

int AVLTree::Height(node* pointer) //Height function.
{
  if (pointer==NULL) //If the pointer is NULL return -1.
    return -1;
  return pointer->height; //return the height
}


node* AVLTree::RightRotation(node* &pointer) //Right rotation
{
  if (pointer->left != NULL) //If the left child isn't NULL.
  {
    node* x = pointer->left; //Save the left child of the current node to node x.
    pointer->left = x->right; //Set the left child of the current node to right child of  this node.
    x->right = pointer; //Set the right child of the left child to the current node.
    pointer->height = max(Height(pointer->left), Height(pointer->right)) + 1; //Set to the pointer height, the max height of left or right child and add 1.
    x->height = max(Height(x->left), pointer->height) + 1; //Set to the right child(x) of the left child(pointer->left) of the current node(pointer) height,
    return x;                              // the max height of left child of x node and pointer height and add 1.
  }
  return pointer;
}

node* AVLTree::LeftRotation(node* &pointer) //Left rotation.
{
  if (pointer->right != NULL)
  {
    node* x = pointer->right; //Save the right child of the current node to node x.
    pointer->right = x->left; //Set the right child of the current node to left child of this node.
    x->left = pointer; //Set the left child of the left child to the current node.
    pointer->height = max(Height(pointer->left), Height(pointer->right)) + 1; //Set to the pointer height, the max height of left or right child and add 1.
    x->height = max(Height(pointer->right), pointer->height) + 1; //Set to the left child(x) of the right child(pointer->right) of the current node(pointer) height,
    return x;
  }
  return pointer;
}

node* AVLTree::doubleRightRotation(node* &pointer) //Double right rotation
{
  pointer->left = LeftRotation(pointer->left); //Set the left child to left rotation.
  return RightRotation(pointer); //right rotation.
}

node* AVLTree::doubleLeftRotation(node* &pointer) //Double left rotation.
{
  pointer->right = RightRotation(pointer->right); //Set the right child to right rotation.
  return LeftRotation(pointer); //left rotation.
}

int AVLTree::max(int a, int b) //max function.
{
  if (a>b)
    return a;
  return b;
}

void AVLTree::InOrder() //Call the private function.
{
  InOrderPriv(root);
}

void AVLTree::PreOrder() //Call the private function.
{
  PreOrderPriv(root);
}

void AVLTree::PostOrder() //Call the private function.
{
  PostOrderPriv(root);
}

void AVLTree::searchTree(string *Q) //Call the private function.
{
  string key;
  float begin=clock();
  cout<<endl<<"\t\t\t\t\tAVL TREE"<<endl;
  cout<<"time of creation: "<<timeOfAVL<<endl;
  for(int i=0;i<1000;i++){
    key=Q[i];
    node* temp;
    temp=searchTreePriv(key,root);
    if (temp!=NULL){
      cout<<temp->key<<" "<<temp->count<<endl; //if you want to show the results
    }
  }
  float time=timecount(begin);
  cout<<endl<<"time: "<<time<<endl;
}

void AVLTree::DeleteNode(string key) //Call the private function.
{
  root=DeleteNodePrivAVL(key,root);
}

node* AVLTree::DeleteNodePrivAVL(string key, node* pointer) //Delete function.
{
  node* temp; //temporary node.
  bool flag=true; //the variable decide if the count will be reduced by one or the whole node will get deleted.

  if (root==NULL) //If the tree is empty.
  {
    return nullptr;
  }
  else if(key < pointer->key) //If the key is less than current key.
  {
    pointer->left = DeleteNodePrivAVL(key, pointer->left); //Go left.
  }
  else if(key > pointer->key) //If the key is higher than current key.
  {
    pointer->right = DeleteNodePrivAVL(key, pointer->right); //Go right.
  }
  // Element found
  else if (pointer->count>1) //If the word exists more than once.
  {
    pointer->count-=1; //Reduce the count by one.
    flag=false; //Determine if the node will get deleted.
  }
  // With 2 children
  else if (pointer->left!=nullptr && pointer->right!=nullptr)
  {
    temp = min(pointer->right); //save the min node.
    pointer->key = temp->key; //set to pointer key the temp key.
    pointer->count=temp->count; //set to pointer counter the temp counter.
    pointer->right = DeleteNodePrivAVL(pointer->key, pointer->right); //Delete the min key (the delete function will start
  }                                                    //from right child of the root).
  // With one or zero child
  else
  {
    if(pointer->left == nullptr) //if left child is NULL.
      pointer = pointer->right; //the parent becomes the right child.
    else if(pointer->right == nullptr) //if right child is NULL.
      pointer = pointer->left; //the parent becomes the left child.
  }
  if(pointer == nullptr) //If the node is NULL.
  {
    return pointer;
  }

  if (flag) // If the ward exist once.
  {
    pointer->height = max(Height(pointer->left), Height(pointer->right))+1;

    // If node is unbalanced
    // If left node is deleted, right case
    if(Height(pointer->left) - Height(pointer->right) == -2)
    {
      // right right case
      if(Height(pointer->right->right) - Height(pointer->right->left) == 1)
        return LeftRotation(pointer);
      // right left case
      else{
        return doubleLeftRotation(pointer);
      }
    }
    // If right node is deleted, left case
    else if(Height(pointer->right) - Height(pointer->left) == 2)
    {
      // left left case
      if(Height(pointer->left->left) - Height(pointer->left->right) == 1){
        return RightRotation(pointer);
      }
      // left right case
      else{
        return doubleRightRotation(pointer);
      }
    }
  }
  return pointer;
}

node* AVLTree::min(node* pointer) //min function.
{
  if (root!=NULL) //if the tree isn't empty.
  {
    if (pointer->left==NULL) //if the left child  is NULL.
    {
      return pointer; //return the min node.
    }
    else{
      return min(pointer->left); //Go left.
    }
  }
  else
  {
    cout<<"The tree is empty!"<<endl;
    return NULL;
  }
}