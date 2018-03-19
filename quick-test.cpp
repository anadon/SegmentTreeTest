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

  segTreePtr->setValue(4, 1);
  segTreePtr->setValue(2, 2);
  segTreePtr->setValue(1, 3);
  segTreePtr->setValue(3, 4);
  segTreePtr->setValue(6, 5);
  segTreePtr->setValue(5, 6);
  segTreePtr->setValue(7, 7);


  if(segTreePtr->getValue(1) != 3) std::cout << "FAILURE 01" << std::endl;
  if(segTreePtr->getValue(2) != 2) std::cout << "FAILURE 02" << std::endl;
  if(segTreePtr->getValue(3) != 4) std::cout << "FAILURE 03" << std::endl;
  if(segTreePtr->getValue(4) != 1) std::cout << "FAILURE 04" << std::endl;
  if(segTreePtr->getValue(5) != 6) std::cout << "FAILURE 05" << std::endl;
  if(segTreePtr->getValue(6) != 5) std::cout << "FAILURE 06" << std::endl;
  if(segTreePtr->getValue(7) != 7) std::cout << "FAILURE 07" << std::endl;


  if(segTreePtr->getMinValue(1, 2) != 2) std::cout << "FAILURE 08" << std::endl;
  if(segTreePtr->getMinValue(1, 3) != 2) std::cout << "FAILURE 09" << std::endl;
  if(segTreePtr->getMinValue(1, 4) != 1) std::cout << "FAILURE 10" << std::endl;
  if(segTreePtr->getMinValue(1, 5) != 1) std::cout << "FAILURE 11" << std::endl;
  if(segTreePtr->getMinValue(1, 6) != 1) std::cout << "FAILURE 12" << std::endl;
  if(segTreePtr->getMinValue(1, 7) != 1) std::cout << "FAILURE 13" << std::endl;
  if(segTreePtr->getMinValue(2, 3) != 2) std::cout << "FAILURE 14" << std::endl;
  if(segTreePtr->getMinValue(2, 4) != 1) std::cout << "FAILURE 15" << std::endl;
  if(segTreePtr->getMinValue(2, 5) != 1) std::cout << "FAILURE 16" << std::endl;
  if(segTreePtr->getMinValue(2, 6) != 1) std::cout << "FAILURE 17" << std::endl;
  if(segTreePtr->getMinValue(2, 7) != 1) std::cout << "FAILURE 18" << std::endl;
  if(segTreePtr->getMinValue(3, 4) != 1) std::cout << "FAILURE 19" << std::endl;
  if(segTreePtr->getMinValue(3, 5) != 1) std::cout << "FAILURE 20" << std::endl;
  if(segTreePtr->getMinValue(3, 6) != 1) std::cout << "FAILURE 21" << std::endl;
  if(segTreePtr->getMinValue(3, 7) != 1) std::cout << "FAILURE 22" << std::endl;
  if(segTreePtr->getMinValue(4, 5) != 1) std::cout << "FAILURE 23" << std::endl;
  if(segTreePtr->getMinValue(4, 6) != 1) std::cout << "FAILURE 24" << std::endl;
  if(segTreePtr->getMinValue(4, 7) != 1) std::cout << "FAILURE 25" << std::endl;
  if(segTreePtr->getMinValue(5, 6) != 5) std::cout << "FAILURE 26" << std::endl;
  if(segTreePtr->getMinValue(5, 7) != 5) std::cout << "FAILURE 27" << std::endl;

  segTreePtr->printTree();

  delete segTreePtr;


  return 0;
}

////////////////////////////////////////////////////////////////////////
//END///////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
