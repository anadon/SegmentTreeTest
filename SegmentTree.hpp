//GSoC 2018 Coding test for Boost

//Implement a segment tree.

//Assume GPLv3, but this is not high value code.

#pragma once


#ifdef SEGMENT_TREE_DEBUG
#include<iostream>
#endif


////////////////////////////////////////////////////////////////////////////////
//A segment tree is a kind of binary tree.  There are a set numerical range of
//possible keys.  However, if the default value is 0 then an infinite tree can
//be simulated.  For this data structure, it is assumed that the default value
//is 0.  There are two key functions, set value at a key, and get the sum of
//values over a range of keys.
//
//Implemented below is a by default infinite size segment tree (bounds can be
//added), get, and set functions.
//
//NOTE: KeyType and ValueType must be numerical, and be able to be set with 0 .
////////////////////////////////////////////////////////////////////////////////
template<typename KeyType, typename ValueType>
class SegmentTree{

////////////////////////////////////////////////////////////////////////////////
//Private node definition, used for a binary tree.
////////////////////////////////////////////////////////////////////////////////
//  template<typename KeyType_, typename ValueType_>
  class node{
  public:
    KeyType key;
    ValueType value;
    node *left = nullptr, *right = nullptr;

    ~node(){
      if(left  != nullptr) delete left;
      if(right != nullptr) delete right;
    }
  };


  //TODO: add rebalancing
  void setValueInternal(KeyType targetKey, ValueType newValue, node **current);


  ValueType getSumValuesInternal(const KeyType &lowerKey,
                                  const KeyType &upperKey, const node *current);


#ifdef SEGMENT_TREE_DEBUG
  void printTreeInternal(node *current);
#endif


  node *root;
  KeyType *lb, *ub;

public:

  SegmentTree();

  SegmentTree(KeyType lowerBound, KeyType upperBound);

  ~SegmentTree();

  void setValue(KeyType targetKey, ValueType newValue);

  ValueType getSumValues(const KeyType &lowerKey, const KeyType &upperKey);

  ValueType getValue(const KeyType &key);

#ifdef SEGMENT_TREE_DEBUG
  void printTree();
#endif
};


////////////////////////////////////////////////////////////////////////////////
//Take a Key and a Value and set the key in the tree to that value.  Create
//the required node if needed.
////////////////////////////////////////////////////////////////////////////////
template<typename KeyType, typename ValueType>
void SegmentTree<KeyType, ValueType>::setValue(KeyType targetKey,
                                                            ValueType newValue){

  if(lb != nullptr && *lb > targetKey) throw 2;
  if(ub != nullptr && *ub < targetKey) throw 3;
  setValueInternal(targetKey, newValue, &root);
}


////////////////////////////////////////////////////////////////////////////////
//Given a range of keys, return the sum of the values for all nodes which have
//keys in that range.
////////////////////////////////////////////////////////////////////////////////
template<typename KeyType, typename ValueType>
ValueType SegmentTree<KeyType, ValueType>::getSumValues(const KeyType &lowerKey,
                                                       const KeyType &upperKey){
  if(lowerKey > upperKey) throw 1;
  if(lb != nullptr && *lb > lowerKey) throw 2;
  if(ub != nullptr && *ub < upperKey) throw 3;
  return getSumValuesInternal(lowerKey, upperKey, root);
}


////////////////////////////////////////////////////////////////////////////////
//Given a key, find the value for the corresponding node.
////////////////////////////////////////////////////////////////////////////////
template<typename KeyType, typename ValueType>
ValueType SegmentTree<KeyType, ValueType>::getValue(const KeyType &key){
  if(lb != nullptr && *lb > key) throw 2;
  if(ub != nullptr && *ub < key) throw 3;
  return getSumValuesInternal(key, key, root);
}


////////////////////////////////////////////////////////////////////////////////
//Used as the internals to set a node to a value if the node exists, else create
//the node and set its key and value to the given values.
//TODO: add rebalancing
////////////////////////////////////////////////////////////////////////////////
template<typename KeyType, typename ValueType>
void SegmentTree<KeyType, ValueType>::setValueInternal(KeyType targetKey,
                                            ValueType newValue, node **current){

  if(*current == nullptr){
    *current = new node();
    (*current)->key = targetKey;
  }

  if((*current)->key == targetKey){
    (*current)->value = newValue;
  }else if((*current)->key < targetKey){//key is left of current node
    setValueInternal(targetKey, newValue, &((*current)->left));
  }else if((*current)->key > targetKey){//key is right of current node
    setValueInternal(targetKey, newValue, &((*current)->right));
  }
}


////////////////////////////////////////////////////////////////////////////////
//Internals to get the sum of values whose keys fall in a given range.
////////////////////////////////////////////////////////////////////////////////
template<typename KeyType, typename ValueType>
ValueType SegmentTree<KeyType, ValueType>::getSumValuesInternal(
         const KeyType &lowerKey, const KeyType &upperKey, const node *current){

  if(current == nullptr){
    return 0;
  }
  if(lowerKey > current->key){
    return getSumValuesInternal(lowerKey, upperKey, current->left);
  }
  if(current->key > upperKey){
    return getSumValuesInternal(lowerKey, upperKey, current->right);
  }

  return getSumValuesInternal(lowerKey, upperKey, current->left) +
         current->value +
         getSumValuesInternal(lowerKey, upperKey, current->right);
}


//Unbounded constructor
template<typename KeyType, typename ValueType>
SegmentTree<KeyType, ValueType>::SegmentTree(){
  root = nullptr;
  lb = ub = nullptr;
}


//Bounded constructor
template<typename KeyType, typename ValueType>
SegmentTree<KeyType, ValueType>::SegmentTree(KeyType lowerBound,
                                                            KeyType upperBound){
  root = nullptr;

  lb = new KeyType();
  *lb = lowerBound;

  ub = new KeyType();
  *ub = upperBound;
}


//Deconstructor
template<typename KeyType, typename ValueType>
SegmentTree<KeyType, ValueType>::~SegmentTree(){
  if(root != nullptr) delete root;
  if(lb   != nullptr) delete lb;
  if(ub   != nullptr) delete ub;
}


////////////////////////////////////////////////////////////////////////////////
//DEBUGGING FUNCTIONS
////////////////////////////////////////////////////////////////////////////////
#ifdef SEGMENT_TREE_DEBUG
template<typename KeyType, typename ValueType>
void SegmentTree<KeyType, ValueType>::printTree(){
  printTreeInternal(root);
  std::cout << std::endl;
}


template<typename KeyType, typename ValueType>
void SegmentTree<KeyType, ValueType>::printTreeInternal(node *current){
  if(current == nullptr){
    return;
  }

  std::cout << "(";
  printTreeInternal(current->left);
  std::cout << " {" << current->value << "} ";
  printTreeInternal(current->right);
  std::cout << ")";
}
#endif

////////////////////////////////////////////////////////////////////////////////
//END
////////////////////////////////////////////////////////////////////////////////
