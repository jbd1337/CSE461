/****************************************************************** 
* Name: Joshua Dunham
* Course: CSE461
* Date: 10/05/2015
* Program: progmaintest.cpp
* Description: Program from Dr. Murpy to test sdisk
*              modified by me to show the size is correct
* 
*******************************************************************/

#include <iostream>
#include <string>
#include "Sdisk.h"


int main()
{
  Sdisk disk1("test1",16,32);
  string block1, block2, block3, block4;
  for (int i=1; i<=32; i++) block1=block1+"1";
  for (int i=1; i<=32; i++) block2=block2+"2";
  disk1.putblock(4,block1);
  disk1.getblock(4,block3);
  cout << "Should be 32 1s : ";
  cout << block3 << endl;
  cout << block3.size() << endl;
  disk1.putblock(8,block2);
  disk1.getblock(8,block4);
  cout << "Should be 32 2s : ";
  cout << block4 << endl;;
  cout << block4.size() << endl;;
}

