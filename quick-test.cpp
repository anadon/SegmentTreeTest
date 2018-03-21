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

#include <cstdlib>
#include <unistd.h>
#include <vector>

#include "SegmentTree.hpp"
#include <iostream>


////////////////////////////////////////////////////////////////////////
//TESTS/////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

using std::cout;
using std::endl;

int main(){

  std::vector<int> testData = {3, 2, 1, 6, 5, 7, 0};

  SegmentTree<int> *segTreePtr;
  segTreePtr = new SegmentTree<int>(testData);

//re-set them in a different order
  try{
    segTreePtr->setValue(0, 14);
    segTreePtr->setValue(1, 13);
    segTreePtr->setValue(2, 12);
    segTreePtr->setValue(3, 11);
    segTreePtr->setValue(4, 10);
    segTreePtr->setValue(5, 9);
    segTreePtr->setValue(6, 8);
  }catch(...){
    cout << "exception caught during setup; terminating" << endl;
    return 1;
  }

  try{
    if(segTreePtr->getValue(0) != 14){
      cout << "FAILURE 01" << endl;
    }
  }catch(...){
    cout << "EXCEPTION 01" << endl;
  }

  try{
    if(segTreePtr->getValue(1) != 13 ){
      cout << "FAILURE 02" << endl;
    }
  }catch(...){
    cout << "EXCEPTION 02" << endl;
  }

  try{
    if(segTreePtr->getValue(2) != 12){
      cout << "FAILURE 03" << endl;
    }
  }catch(...){
    cout << "EXCEPTION 03" << endl;
  }

  try{
    if(segTreePtr->getValue(3) != 11){
      cout << "FAILURE 04" << endl;
    }
  }catch(...){
    cout << "EXCEPTION 04" << endl;
  }

  try{
    if(segTreePtr->getValue(4) != 10){
      cout << "FAILURE 05" << endl;
    }
  }catch(...){
    cout << "EXCEPTION 05" << endl;
  }

  try{
    if(segTreePtr->getValue(5) != 9 ){
      cout << "FAILURE 05" << endl;
    }
  }catch(...){
    cout << "EXCEPTION 05" << endl;
  }

  try{
    if(segTreePtr->getValue(6) != 8 ){
      cout << "FAILURE 06" << endl;
    }
  }catch(...){
    cout << "EXCEPTION 06" << endl;
  }


  try{
    if(segTreePtr->getValue(0, 1) != 13 ){
      cout << "FAILURE 08" << endl;
    }
  }catch(...){
    cout << "EXCEPTION 08" << endl;
  }


  try{
    if(segTreePtr->getValue(0, 2) != 12 ){
      cout << "FAILURE 08" << endl;
    }
  }catch(...){
    cout << "EXCEPTION 08" << endl;
  }


  try{
    if(segTreePtr->getValue(0, 3) != 11){
      cout << "FAILURE 08" << endl;
    }
  }catch(...){
    cout << "EXCEPTION 08" << endl;
  }


  try{
    if(segTreePtr->getValue(0, 4) != 10){
      cout << "FAILURE 08" << endl;
    }
  }catch(...){
    cout << "EXCEPTION 08" << endl;
  }


  try{
    if(segTreePtr->getValue(0, 5) != 9 ){
      cout << "FAILURE 08" << endl;
    }
  }catch(...){
    cout << "EXCEPTION 08" << endl;
  }


  try{
    if(segTreePtr->getValue(0, 6) != 8 ){
      cout << "FAILURE 08" << endl;
    }
  }catch(...){
    cout << "EXCEPTION 08" << endl;
  }


  try{
    if(segTreePtr->getValue(1, 2) != 12 ){
      cout << "FAILURE 08" << endl;
    }
  }catch(...){
    cout << "EXCEPTION 08" << endl;
  }

  try{
    if(segTreePtr->getValue(1, 3) != 11 ){
      cout << "FAILURE 09" << endl;
    }
  }catch(...){
    cout << "EXCEPTION 09" << endl;
  }

  try{
    if(segTreePtr->getValue(1, 4) != 10 ){
      cout << "FAILURE 10" << endl;
    }
  }catch(...){
    cout << "EXCEPTION 10" << endl;
  }

  try{
    if(segTreePtr->getValue(1, 5) != 9 ){
      cout << "FAILURE 11" << endl;
    }
  }catch(...){
    cout << "EXCEPTION 11" << endl;
  }

  try{
    if(segTreePtr->getValue(1, 6) != 8 ){
      cout << "FAILURE 12" << endl;
    }
  }catch(...){
    cout << "EXCEPTION 12" << endl;
  }

  try{
    if(segTreePtr->getValue(2, 3) != 11){
      cout << "FAILURE 14" << endl;
    }
  }catch(...){
    cout << "EXCEPTION 14" << endl;
  }

  try{
    if(segTreePtr->getValue(2, 4) != 10){
      cout << "FAILURE 15" << endl;
    }
  }catch(...){
    cout << "EXCEPTION 15" << endl;
  }

  try{
    if(segTreePtr->getValue(2, 5) != 9 ){
      cout << "FAILURE 16" << endl;
    }
  }catch(...){
    cout << "EXCEPTION 16" << endl;
  }

  try{
    if(segTreePtr->getValue(2, 6) != 8 ){
      cout << "FAILURE 17" << endl;
    }
  }catch(...){
    cout << "EXCEPTION 17" << endl;
  }

  try{
    if(segTreePtr->getValue(3, 4) != 10){
      cout << "FAILURE 19" << endl;
    }
  }catch(...){
    cout << "EXCEPTION 19" << endl;
  }

  try{
    if(segTreePtr->getValue(3, 5) != 9 ){
      cout << "FAILURE 20" << endl;
    }
  }catch(...){
    cout << "EXCEPTION 20" << endl;
  }

  try{
    if(segTreePtr->getValue(3, 6) != 8 ){
      cout << "FAILURE 21" << endl;
    }
  }catch(...){
    cout << "EXCEPTION 21" << endl;
  }

  try{
    if(segTreePtr->getValue(4, 5) != 9 ){
      cout << "FAILURE 23" << endl;
    }
  }catch(...){
    cout << "EXCEPTION 23" << endl;
  }

  try{
    if(segTreePtr->getValue(4, 6) != 8 ){
      cout << "FAILURE 24" << endl;
    }
  }catch(...){
    cout << "EXCEPTION 24" << endl;
  }

  try{
    if(segTreePtr->getValue(5, 6) != 8){
      cout << "FAILURE 26" << endl;
    }
  }catch(...){
    cout << "EXCEPTION 26" << endl;
  }

  segTreePtr->printTree();

  delete segTreePtr;


  return 0;
}

////////////////////////////////////////////////////////////////////////
//END///////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
