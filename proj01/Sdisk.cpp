/****************************************************************** 
* Name: Joshua Dunham
* Course: CSE461
* Date Created: 10/05/2015
* Date Modified: 10/12/2015
* Program: Sdisk.cpp
* Description: Program to emulate disk for writing file system for.
*
*******************************************************************/

#include "Sdisk.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

Sdisk::Sdisk(string diskname, int numberofblocks, int blocksize) {
   fstream sdiskfile;
   sdiskfile.open(diskname.c_str(), ios::in);
   if (sdiskfile.good()) {
       sdiskfile.close();
       sdiskfile.open(diskname.c_str(), ios::in | ios::out);
       this->numberofblocks = numberofblocks;
       this->blocksize = blocksize;
       this->diskname = diskname;
       sdiskfile.close();
       
   }
   else{
       sdiskfile.close();
       sdiskfile.open(diskname.c_str(),ios::out);
       for (int i = 0; i < (numberofblocks * blocksize); i++) {
           sdiskfile << "#";
       }
       this->numberofblocks = numberofblocks;
       this->blocksize = blocksize;
       this->diskname = diskname;
       sdiskfile.close();
   } 
}
int Sdisk::getblock(int blocknumber, string& buffer) {
    if(buffer.size() > blocksize){
        cout << "Error" << endl;
        return 1;
    }
    int position = 0;
    char c;
    position =  (blocknumber * blocksize);
    fstream sdisk;
    sdisk.open(diskname.c_str(), ios::in | ios::out);
    if (sdisk.good()) {
        sdisk.seekg(position);
        buffer.clear();
        for (int i = (blocksize); i > 0; i--) {
            sdisk.get(c);
            buffer.push_back(c);
        }
        return 0;
        }
    else{
        return 1;
    }
}
int Sdisk::putblock(int blocknumber, string buffer) {
    if(buffer.size() > blocksize){
        cout << "Error" << endl;
        return 1;
    }
    int position = 0;
    position =  (blocknumber * blocksize);
    fstream sdisk;
    sdisk.open(diskname.c_str(), ios::in | ios::out);
    if (sdisk.good()) {
        sdisk.seekp(position);
        sdisk << buffer; 
        return 0;
        }
    else{
        return 1;
    }
}

int Sdisk::getnumberofblocks() {
    return numberofblocks;
}

int Sdisk::getblocksize() {
    return blocksize;
}
