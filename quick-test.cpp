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

using std::cout;
using std::endl;

int main(){

  SegmentTree<int, int> *segTreePtr;
  segTreePtr = new SegmentTree<int, int>();

//set initial values
  segTreePtr->setValue(4, 1);
  segTreePtr->setValue(2, 2);
  segTreePtr->setValue(1, 3);
  segTreePtr->setValue(3, 4);
  segTreePtr->setValue(6, 5);
  segTreePtr->setValue(5, 6);
  segTreePtr->setValue(7, 7);

//re-set them in a different order
  segTreePtr->setValue(7, 14);
  segTreePtr->setValue(5, 13);
  segTreePtr->setValue(6, 12);
  segTreePtr->setValue(3, 11);
  segTreePtr->setValue(1, 10);
  segTreePtr->setValue(2, 9);
  segTreePtr->setValue(4, 8);


  if(segTreePtr->getValue(1) != 10) cout << "FAILURE 01" << endl;
  if(segTreePtr->getValue(2) != 9 ) cout << "FAILURE 02" << endl;
  if(segTreePtr->getValue(3) != 11) cout << "FAILURE 03" << endl;
  if(segTreePtr->getValue(4) != 8 ) cout << "FAILURE 04" << endl;
  if(segTreePtr->getValue(5) != 13) cout << "FAILURE 05" << endl;
  if(segTreePtr->getValue(6) != 12) cout << "FAILURE 06" << endl;
  if(segTreePtr->getValue(7) != 14) cout << "FAILURE 07" << endl;


  if(segTreePtr->getValue(1, 2) != 9 ) cout << "FAILURE 08" << endl;
  if(segTreePtr->getValue(1, 3) != 9 ) cout << "FAILURE 09" << endl;
  if(segTreePtr->getValue(1, 4) != 8 ) cout << "FAILURE 10" << endl;
  if(segTreePtr->getValue(1, 5) != 8 ) cout << "FAILURE 11" << endl;
  if(segTreePtr->getValue(1, 6) != 8 ) cout << "FAILURE 12" << endl;
  if(segTreePtr->getValue(1, 7) != 8 ) cout << "FAILURE 13" << endl;
  if(segTreePtr->getValue(2, 3) != 9 ) cout << "FAILURE 14" << endl;
  if(segTreePtr->getValue(2, 4) != 8 ) cout << "FAILURE 15" << endl;
  if(segTreePtr->getValue(2, 5) != 8 ) cout << "FAILURE 16" << endl;
  if(segTreePtr->getValue(2, 6) != 8 ) cout << "FAILURE 17" << endl;
  if(segTreePtr->getValue(2, 7) != 8 ) cout << "FAILURE 18" << endl;
  if(segTreePtr->getValue(3, 4) != 8 ) cout << "FAILURE 19" << endl;
  if(segTreePtr->getValue(3, 5) != 8 ) cout << "FAILURE 20" << endl;
  if(segTreePtr->getValue(3, 6) != 8 ) cout << "FAILURE 21" << endl;
  if(segTreePtr->getValue(3, 7) != 8 ) cout << "FAILURE 22" << endl;
  if(segTreePtr->getValue(4, 5) != 8 ) cout << "FAILURE 23" << endl;
  if(segTreePtr->getValue(4, 6) != 8 ) cout << "FAILURE 24" << endl;
  if(segTreePtr->getValue(4, 7) != 8 ) cout << "FAILURE 25" << endl;
  if(segTreePtr->getValue(5, 6) != 12) cout << "FAILURE 26" << endl;
  if(segTreePtr->getValue(5, 7) != 12) cout << "FAILURE 27" << endl;

  segTreePtr->printTree();

  delete segTreePtr;


  return 0;
}

////////////////////////////////////////////////////////////////////////
//END///////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
