/****************************************************************** 
* Name: Joshua Dunham
* Course: CSE461
* Date Created: 10/05/2015
* Date Modified: 10/12/2015
* Program: Sdisk.cpp
* Description: Program to emulate disk for writing file system for.
*
*******************************************************************/

#ifndef SDISK_H
#define SDISK_H

#include <fstream>
#include <string>
using namespace std;
class Sdisk
{
public:
    Sdisk(string diskname, int numberofblocks, int blocksize);
    int getblock(int blocknumber, string& buffer);
    int putblock(int blocknumber, string buffer);
    int getnumberofblocks();
    int getblocksize();

private:
    string diskname;
    int numberofblocks;
    int blocksize;
};
#endif
