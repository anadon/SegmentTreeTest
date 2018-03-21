//GSoC 2018 Coding test for Boost

//Implement a segment tree.

//Assume GPLv3, but this is not high value code.

#pragma once

#include<vector>
#include<cstddef>

#ifdef SEGMENT_TREE_DEBUG
#include<iostream>
#endif


////////////////////////////////////////////////////////////////////////////////
// A segment tree is a kind of binary tree used to quickly find the minimum
// value in a range of values.  There are a set numerical range of possible
// keys.  If the default value is infinity, then an infinite tree can be
// simulated.  For this data structure, it is assumed that the default value is
// 0.  There are two key functions, set value at a key, and get the sum of
// values over a range of keys.
//
// Implemented below is a by default infinite size segment tree (bounds can be
// added), get, and set functions.
////////////////////////////////////////////////////////////////////////////////
template<typename ValueType>
class SegmentTree{

////////////////////////////////////////////////////////////////////////////////
// Private node definition, used for a binary tree.
////////////////////////////////////////////////////////////////////////////////
  class node{
  public:
    size_t lowerKey, upperKey;
    ValueType value;
    node *left = nullptr, *right = nullptr;

    ~node(){
      if(left  != nullptr) delete left;
      if(right != nullptr) delete right;
    }
  };

  void setValueInternal(size_t targetKey, ValueType newValue, node **current);

  ValueType getValueInternal(const size_t lowerKey,
              const size_t upperKey, const node *current, bool &usableResult);

#ifdef SEGMENT_TREE_DEBUG
  void printTreeInternal(node *current);
#endif

  ValueType (*segTreeFunc)(ValueType, ValueType);
  node *root;
  size_t maxIndex;

public:

  SegmentTree(std::vector<ValueType> data, ValueType (*userFunc)(ValueType, ValueType)
    = [] (ValueType left, ValueType right)
    -> ValueType { return left < right ? left : right; });

  ~SegmentTree();

  void setValue(size_t targetKey, ValueType newValue);

  ValueType getValue(const size_t lowerKey, const size_t upperKey);

  ValueType getValue(const size_t key);

#ifdef SEGMENT_TREE_DEBUG
  void printTree();
#endif
};


////////////////////////////////////////////////////////////////////////////////
// Take a Key and a Value and set the key in the tree to that value.  Create
// the required node if needed.
////////////////////////////////////////////////////////////////////////////////
template<typename ValueType>
void SegmentTree<ValueType>::setValue(size_t targetKey, ValueType newVal){
  if(maxIndex <= targetKey) return; //throw 3;
  setValueInternal(targetKey, newVal, &root);
}


////////////////////////////////////////////////////////////////////////////////
// Given a range of keys, return the sum of the values for all nodes which have
// keys in that range.
// TODO: these throws should use full and proper exceptions.
////////////////////////////////////////////////////////////////////////////////
template<typename ValueType>
ValueType SegmentTree<ValueType>::getValue(const size_t lowerKey,
                                                    const size_t upperKey){
  if(lowerKey > upperKey) throw 1;
  if(maxIndex <= upperKey) throw 3;
  bool usableResult = false;
  ValueType minVal;
  minVal = getValueInternal(lowerKey, upperKey, root, usableResult);
  if(usableResult){
    return minVal;
  }
  // NOTE: depending on use case, this should be an exception.  Using 127
  // because it is the highest value a signed byte can hold, so everything can
  // use it without wrapping for truncating.
  throw 127;
}


////////////////////////////////////////////////////////////////////////////////
// Given a key, find the value for the corresponding node.
// TODO: these throws should use full and proper exceptions.
////////////////////////////////////////////////////////////////////////////////
template<typename ValueType>
ValueType SegmentTree<ValueType>::getValue(const size_t key){
  return getValue(key, key);
}


////////////////////////////////////////////////////////////////////////////////
// Used as the internals to set a node to a value if the node exists, else
// create the node and set its key and value to the given values.
// TODO: add rebalancing
////////////////////////////////////////////////////////////////////////////////
template<typename ValueType>
void SegmentTree<ValueType>::setValueInternal(size_t targetKey,
                                            ValueType newValue, node **current){
  //insert new node at end, possibly root
  if(*current == nullptr){
    *current = new node();
    (*current)->lowerKey = targetKey;
    (*current)->upperKey = targetKey;
    (*current)->value = newValue;
    return;
  }

  // Else, because of how insertions work, this is either a leaf or a parent
  // with two children.

  if( ((*current)->left != nullptr && (*current)->left == nullptr) ||
      ((*current)->left == nullptr && (*current)->left != nullptr)){
    //should never reach here, this is an error state.
    throw 6;
  }


  //update the value in this node, it is a leaf
  if((*current)->lowerKey == targetKey && (*current)->upperKey == targetKey){
    (*current)->value = newValue;
    return;
  }


  if((*current)->left != nullptr){
    //parent case, pass along
    // figure out which side to send the value.  This means finding the right
    // most node of the left side, or the leftmost node of the right side.
    // NOTE: this has an insertion bias and results is unfull binary trees
    node *rml = (*current)->left;
    while(rml->right != nullptr) rml = rml->right;
    if(targetKey > rml->upperKey){
      setValueInternal(targetKey, newValue, &((*current)->right));
    }else{
      setValueInternal(targetKey, newValue, &((*current)->left));
    }

    if((*current)->upperKey < targetKey){
      (*current)->upperKey = targetKey;
    }else if((*current)->lowerKey > targetKey){
      (*current)->lowerKey = targetKey;
    }

  }else if((*current)->lowerKey > targetKey){
    //this is a leaf which needs to be promoted to a parent with the new values
    //going on the left
    setValueInternal(targetKey, newValue, &((*current)->left));
    setValueInternal((*current)->upperKey, (*current)->value,
                                                          &((*current)->right));
    (*current)->lowerKey = targetKey;
  }else if((*current)->lowerKey < targetKey){
    //this is a leaf which needs to be promoted to a parent with the new values
    //going on the right
    setValueInternal((*current)->lowerKey, (*current)->value,
                                                           &((*current)->left));
    setValueInternal(targetKey, newValue, &((*current)->right));
    (*current)->upperKey = targetKey;
  }

  ValueType leftValue  = (*current)->left->value;
  ValueType rightValue = (*current)->right->value;
  (*current)->value = segTreeFunc(leftValue, rightValue);
}


////////////////////////////////////////////////////////////////////////////////
//Internals to get the sum of values whose keys fall in a given range.
////////////////////////////////////////////////////////////////////////////////
template<typename ValueType>
ValueType SegmentTree<ValueType>::getValueInternal(
    const size_t lowerKey, const size_t upperKey, const node *current,
                                                            bool &usableResult){
  if(current == nullptr){
    usableResult = false;
    return 0;
  }

  //check entirely in range, out of range, or partially in range cases

  //entirely in range
  if(lowerKey <= current->lowerKey && current->upperKey <= upperKey){
    usableResult = true;
    return current->value;
  }

  //outside
  if(upperKey < current->lowerKey || current->upperKey < lowerKey){
    usableResult = false;
    return 0;
  }

  //partially
  if(current->lowerKey <= upperKey || lowerKey <= current->upperKey ){
    bool canUseLeft = true;
    ValueType leftVal;
    leftVal = getValueInternal(lowerKey, upperKey, current->left, canUseLeft);

    bool canUseRight = true;
    ValueType rightVal;
    rightVal = getValueInternal(lowerKey, upperKey, current->right, canUseRight);

    if(canUseLeft && canUseRight){
      usableResult = true;
      return segTreeFunc(leftVal, rightVal);
    }else if(canUseLeft){
      usableResult = true;
      return leftVal;
    }else if(canUseRight){
      usableResult = true;
      return rightVal;
    }else{
      usableResult = false;
      return 0;
    }
  }

  //should never reach here
  usableResult = false;
  throw 127;
}


//Unbounded constructor
template<typename ValueType>
SegmentTree<ValueType>::SegmentTree(std::vector<ValueType> data,
                                   ValueType (*userFunc)(ValueType, ValueType)){
  root = nullptr;
  maxIndex = data.size();
  segTreeFunc = userFunc;

  for(size_t i = 0; i < data.size(); i++)
    setValue(i, data[i]);
}


//Deconstructor
template<typename ValueType>
SegmentTree<ValueType>::~SegmentTree(){
  if(root != nullptr) delete root;
}


////////////////////////////////////////////////////////////////////////////////
// DEBUGGING FUNCTIONS
////////////////////////////////////////////////////////////////////////////////
#ifdef SEGMENT_TREE_DEBUG
template<typename ValueType>
void SegmentTree<ValueType>::printTree(){
  printTreeInternal(root);
  std::cout << std::endl;
}


template<typename ValueType>
void SegmentTree<ValueType>::printTreeInternal(node *current){
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
