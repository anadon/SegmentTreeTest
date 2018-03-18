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

#include "SegmentTree.hpp"


////////////////////////////////////////////////////////////////////////
//TESTS/////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////


int main(){

  SegmentTree<int, int> *segTreePtr;
  segTreePtr = new SegmentTree<int, int>();
  segTreePtr->setValue(0, 1);
  segTreePtr->setValue(1, 1);
  segTreePtr->setValue(0, 2);
  segTreePtr->setValue(1, 2);

  int sum1 = segTreePtr->getValue(0);
  if(sum1 != 2){
    std::cout << "FAILURE ONE" << std::endl;
  }

  int sum2 = segTreePtr->getValue(1);
  if(sum2 != 2){
    std::cout << "FAILURE TWO: " << sum2 << std::endl;
  }

  int sum3 = segTreePtr->getValue(2);
  if(sum3 != 0){
    std::cout << "FAILURE THREE" << std::endl;
  }

  int sum4 = segTreePtr->getSumValues(0, 100);
  if(sum4 != 4){
    std::cout << "FAILURE FOUR" << std::endl;
  }

  segTreePtr->printTree();

  delete segTreePtr;

  SegmentTree<int, int> segTree;
  segTree.setValue(0, 1);
  segTree.setValue(1, 1);
  segTree.setValue(0, 2);
  segTree.setValue(1, 2);

  sum1 = segTree.getValue(0);
  if(sum1 != 2){
    std::cout << "FAILURE FIVE" << std::endl;
  }

  sum2 = segTree.getValue(1);
  if(sum2 != 2){
    std::cout << "FAILURE SIX: " << sum2 << std::endl;
  }

  sum3 = segTree.getValue(2);
  if(sum3 != 0){
    std::cout << "FAILURE SEVEN" << std::endl;
  }

  sum4 = segTree.getSumValues(0, 100);
  if(sum4 != 4){
    std::cout << "FAILURE EIGHT" << std::endl;
  }

  segTree.printTree();

  return 0;
}

////////////////////////////////////////////////////////////////////////
//END///////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
