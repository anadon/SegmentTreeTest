/*Copyright 2016-2017 Josh Marshall************************************/

/***********************************************************************
    This file is part of TF-Cluster.

    TF-Cluster is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    TF-Cluster is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with TF-Cluster.  If not, see <http://www.gnu.org/licenses/>.
***********************************************************************/


////////////////////////////////////////////////////////////////////////
//INCLUDES//////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <unistd.h>
#include <unordered_map>

#include "gtest/gtest.h"
#include "SegmentTree.hpp"


//using std::SegmentTree;

////////////////////////////////////////////////////////////////////////
//TESTS/////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

//*
TEST(SEGMENT_TREE, CREATION_ONE){

  SegmentTree<int, int> *segTree;
  segTree = new SegmentTree<int, int>();
  delete segTree;
}//*/

//*
TEST(SEGMENT_TREE, CREATION_TWO){
  SegmentTree<int, int> segTree;
}//*/

//*
TEST(SEGMENT_TREE, CREATION_THREE){

  SegmentTree<int, int> *segTree;
  segTree = new SegmentTree<int, int>(0, 100);
  delete segTree;
}//*/

//*
TEST(SEGMENT_TREE, CREATION_FOUR){
  SegmentTree<int, int> segTree(0, 100);
}//*/

//*
TEST(SEGMENT_TREE, SET_ONE){
  SegmentTree<int, int> segTree;

  segTree.setValue(50, 4);
}//*/

//*
TEST(SEGMENT_TREE, SET_TWO){
  SegmentTree<int, int> segTree;

  segTree.setValue(50, 4);
  segTree.setValue(26, 4);
}//*/

//*
TEST(SEGMENT_TREE, SET_OVER){
  SegmentTree<int, int> segTree;

  segTree.setValue(50, 4);
  segTree.setValue(50, 5);
}//*/

//*
TEST(SEGMENT_TREE, GET_ONE){
  SegmentTree<int, int> segTree;

  segTree.setValue(50, 4);

  int val = segTree.getValue(50);

  EXPECT_EQ(val, 4);
}//*/

//*
TEST(SEGMENT_TREE, GET_TWO){
  SegmentTree<int, int> segTree(0, 100);

  segTree.setValue(50, 4);

  int val = segTree.getValue(50);

  EXPECT_EQ(val, 4);
}//*/

//*
TEST(SEGMENT_TREE, GET_THREE){
  SegmentTree<int, int> segTree(0, 100);

  segTree.setValue(50, 4);

  int val = segTree.getSumValues(0, 100);

  EXPECT_EQ(val, 4);
}//*/

//*
TEST(SEGMENT_TREE, GET_FOUR){
  SegmentTree<int, int> segTree(0, 100);

  segTree.setValue(50, 4);
  segTree.setValue(26, 5);

  int val = segTree.getSumValues(0, 100);

  EXPECT_EQ(val, 9);
}//*/

//*
TEST(SEGMENT_TREE, GET_EMPTY_ONE){
  SegmentTree<int, int> segTree(0, 100);

  int val = segTree.getValue(0);

  EXPECT_EQ(val, 0);
}//*/

//*
TEST(SEGMENT_TREE, GET_EMPTY_TWO){
  SegmentTree<int, int> segTree(0, 100);

  segTree.setValue(50, 4);
  segTree.setValue(26, 5);

  int val = segTree.getSumValues(27, 49);

  EXPECT_EQ(val, 0);
}//*/

////////////////////////////////////////////////////////////////////////
//END///////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
