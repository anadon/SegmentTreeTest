//GSoC 2018 Coding test for Boost

//Implement a segment tree.

//Assume GPLv3, but this is not high value code.

#pragma once


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
//
// NOTE: KeyType and ValueType must be numerical, and be able to be set with 0 .
////////////////////////////////////////////////////////////////////////////////
template<typename KeyType, typename ValueType>
class SegmentTree{

////////////////////////////////////////////////////////////////////////////////
// Private node definition, used for a binary tree.
////////////////////////////////////////////////////////////////////////////////
  class node{
  public:
    KeyType lowerKey, upperKey;
    ValueType value;
    node *left = nullptr, *right = nullptr;

    ~node(){
      if(left  != nullptr) delete left;
      if(right != nullptr) delete right;
    }
  };

  void setValueInternal(KeyType targetKey, ValueType newValue, node **current);

  ValueType getValueInternal(const KeyType &lowerKey,
              const KeyType &upperKey, const node *current, bool &usableResult);

#ifdef SEGMENT_TREE_DEBUG
  void printTreeInternal(node *current);
#endif

  ValueType (*segTreeFunc)(ValueType, ValueType);
  node *root;
  KeyType *lb, *ub;

public:

  SegmentTree(ValueType (*userFunc)(ValueType, ValueType)
    = [] (ValueType left, ValueType right)
    -> ValueType { return left < right ? left : right; });

  SegmentTree(KeyType lowerBound, KeyType upperBound,
    ValueType (*userFunc)(ValueType, ValueType)
    = [] (ValueType left, ValueType right)
    -> ValueType { return left < right ? left : right; });

  ~SegmentTree();

  void setValue(KeyType targetKey, ValueType newValue);

  ValueType getValue(const KeyType &lowerKey, const KeyType &upperKey);

  ValueType getValue(const KeyType &key);

#ifdef SEGMENT_TREE_DEBUG
  void printTree();
#endif
};


////////////////////////////////////////////////////////////////////////////////
// Take a Key and a Value and set the key in the tree to that value.  Create
// the required node if needed.
////////////////////////////////////////////////////////////////////////////////
template<typename KeyType, typename ValueType>
void SegmentTree<KeyType, ValueType>::setValue(KeyType targetKey,
                                                            ValueType newValue){

  if(lb != nullptr && *lb > targetKey) throw 2;
  if(ub != nullptr && *ub < targetKey) throw 3;
  setValueInternal(targetKey, newValue, &root);
}


////////////////////////////////////////////////////////////////////////////////
// Given a range of keys, return the sum of the values for all nodes which have
// keys in that range.
// TODO: these throws should use full and proper exceptions.
////////////////////////////////////////////////////////////////////////////////
template<typename KeyType, typename ValueType>
ValueType SegmentTree<KeyType, ValueType>::getValue(const KeyType &lowerKey,
                                                       const KeyType &upperKey){
  if(lowerKey > upperKey) throw 1;
  if(lb != nullptr && *lb > lowerKey) throw 2;
  if(ub != nullptr && *ub < upperKey) throw 3;
  bool usableResult = false;
  ValueType minVal;
  minVal = getValueInternal(lowerKey, upperKey, root, usableResult);
  if(usableResult){
    return minVal;
  }else{
    // NOTE: depending on use case, this should be an exception.  Using 127
    // because it is the highest value a signed byte can hold, so everything can
    // use it without wrapping for truncating.
    return 127;
  }
}


////////////////////////////////////////////////////////////////////////////////
// Given a key, find the value for the corresponding node.
// TODO: these throws should use full and proper exceptions.
////////////////////////////////////////////////////////////////////////////////
template<typename KeyType, typename ValueType>
ValueType SegmentTree<KeyType, ValueType>::getValue(const KeyType &key){
  if(lb != nullptr && *lb > key) throw 2;
  if(ub != nullptr && *ub < key) throw 3;
  bool usableResult = false;
  ValueType minVal = getValueInternal(key, key, root, usableResult);
  if(usableResult){
    return minVal;
  }else{
    // NOTE: depending on use case, this should be an exception.  Using 127
    // because it is the highest value a signed byte can hold, so everything can
    // use it without wrapping for truncating.
    return 127;
  }
}


////////////////////////////////////////////////////////////////////////////////
// Used as the internals to set a node to a value if the node exists, else
// create the node and set its key and value to the given values.
// TODO: add rebalancing
////////////////////////////////////////////////////////////////////////////////
template<typename KeyType, typename ValueType>
void SegmentTree<KeyType, ValueType>::setValueInternal(KeyType targetKey,
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
template<typename KeyType, typename ValueType>
ValueType SegmentTree<KeyType, ValueType>::getValueInternal(
         const KeyType &lowerKey, const KeyType &upperKey, const node *current,
                                                            bool &usableResult){

  if(current == nullptr){
    usableResult = false;
    return 0;
  }

  //check entirely in range, out of range, or partially in range cases

  //entirely
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
    ValueType leftMin;
    leftMin = getValueInternal(lowerKey, upperKey, current->left, canUseLeft);

    bool canUseRight = true;
    ValueType rightMin;
    rightMin = getValueInternal(lowerKey, upperKey, current->right, canUseRight);

    if(canUseLeft && canUseRight){
      usableResult = true;
      return leftMin < rightMin ? leftMin : rightMin;
    }else if(canUseLeft){
      usableResult = true;
      return leftMin;
    }else if(canUseRight){
      usableResult = true;
      return rightMin;
    }else{
      usableResult = false;
      return 0;
    }
  }

  //should never reach here
  usableResult = false;
  return 255;
}


//Unbounded constructor
template<typename KeyType, typename ValueType>
SegmentTree<KeyType, ValueType>::SegmentTree(
                                   ValueType (*userFunc)(ValueType, ValueType)){
  root = nullptr;
  lb = ub = nullptr;
  segTreeFunc = userFunc;
}


//Bounded constructor
template<typename KeyType, typename ValueType>
SegmentTree<KeyType, ValueType>::SegmentTree(KeyType lowerBound,
               KeyType upperBound, ValueType (*userFunc)(ValueType, ValueType)){
  root = nullptr;

  lb = new KeyType();
  *lb = lowerBound;

  ub = new KeyType();
  *ub = upperBound;

  segTreeFunc = userFunc;
}


//Deconstructor
template<typename KeyType, typename ValueType>
SegmentTree<KeyType, ValueType>::~SegmentTree(){
  if(root != nullptr) delete root;
  if(lb   != nullptr) delete lb;
  if(ub   != nullptr) delete ub;
}


////////////////////////////////////////////////////////////////////////////////
// DEBUGGING FUNCTIONS
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
