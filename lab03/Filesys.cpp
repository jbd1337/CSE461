/****************************************************************** 
* Name: Joshua Dunham
* Course: CSE461
* Date Created: 10-12-2015
* Date Modified: 10-12-2015
* Program:Filesys.cpp
* Lab: 3
* Description: Simple filesystem built on sdisk.
*            
*            
*******************************************************************/

#include "Filesys.h"
#include "Sdisk.h"
#include "Sdisk.cpp"
#include <vector>
#include <string>
#include <ostringstream>

using namespace std;

void Filesys::Filesys(string disk, int numberofblocks, int bloacksize): Sdisk(disk,numberofblocks,blocksize){
    istring buffer;
    rootsize = Sdisk::getblocksize() / 12;
    fatsize = (Sdisk::getnumberofblocks() * 6.0) / (Sdisk::getblocksize() + 1);
    //If sdisk has root and fat read in to memory.
    if (buffer2[0] != '#') {
    istringstream buffer1, buffer4;
    string buffer2, buffer3;
    Sdisk::getblock(0,buffer2);
    buffer1.str(buffer2);
        for (int i = 0; i < rootsize; i++) {
            string s;
            int n;
            buffer1 >> s >> n;
            filename.push_back(s);
            firstbloack.push_back(n);
        }
        for (int i = 1; i <= fatsize; i++) {
           string s;
           Sdisk::getblock(i,s);
           buffer3 += s;
        }
        buffer4.str(buffer3);
        for (int i = 0; i < Sdisk::getnumberofblocks(); i++) {
            int n = 0;
            buffer4 >> n;
            fat.push_back(n)
        }

    }
    //If root and fat do not exist on the disk initialize it.
    else{
        for (int i = 0; i < rootsize; i++) {
           filename.push_back(".....");
           firstblock.push_back(0);
        }
        fat.push_back(fatsize + 1);
        for (int i = 1; i <= fatsize; i++) {
           fat.push_back(1); 
        }
        for (int i = fatsize + 1; i < Sdisk::getnumberofblocks(); i++) {
           fat.push_back(i + 1); 
        }
        fat[fatsize - 1] = 0;
        fssynch();
    }
    vector<string> block(string buffer, int b)
    {
    // blocks the buffer into a list of blocks of size b
        vector<string> blocks;
        int numberofblocks=0;
     
        if (buffer.length() % b == 0){ 
             numberofblocks= buffer.length()/b;
        }
        else { 
            numberofblocks= buffer.length()/b +1;
        }
     
        string tempblock;
        for (int i=0; i<numberofblocks; i++){ 
             tempblock=buffer.substr(b*i,b);
             blocks.push_back(tempblock);
        }
        int lastblock=blocks.size()-1; 
        for (int i=blocks[lastblock].length(); i<b; i++){
             blocks[lastblock]+="#";
        }
        return blocks;
    }
}

bool Filesys::checkblock(string file, int blocknumber) {
    //check if block belongs to the file.
    int fblock = getfirstblock(file);
    //error checking.
    int nblock = fblock;
    if(fblock == block){
        return true;
    }
    while (fat[nblock] != 0 and fat[nblock] != block) {
        nblock = fat[nblock];
    }
    if (fat[nblock] == 0) {
        return false;
    }
    if (fat[nblock] == block) {
        return true;
    }
}
int Filesys::fsclose() {
    
}

int Filesys::fssynch() {
    // synchs fat and root to the disk
    ostringstream buffer1, buffer2;
    for (int i = 0; i < rootsize; i++) {
        buffer1 << filename[i] << " " << firstblock[i] << " ";
    }
    for (int i = 0; i < fat.size; i++) {
        buffer2 << fat[i] << " ";
    }
    string buffer3, buffer4;
    buffer3 = buffer1.str();
    buffer4 = buffer2.str();
    std::vector<string> blocks1 = block(buffer3, Sdisk::getblocksize());
    std::vector<string> blocks2 = block(buffer4, Sdisk::getblocksize());
    Sdisk::putblock(0,blocks1[0]);
    for (int i = 0; i < blocks2.size(); i++) {
        Sdisk::putblock(i + 1,blocks2[i]);
    }


}

int Filesys::newfile(string file) {
    if(file.length() > 5){
        cout << "Filename too long" << endl;
        return 0;
    }
    for (int i = 0; i < filename.size(); i++) {
        if(filename[i] == file){
            return 0;
        }
    }
    for (int i = 0; i < filename.size(); i++) {
        if (filename[i] == ".....") {
            filename[i] = file;
            block[i] = 0;
            fssynch();
            return 1;
        }
    }
    return 0;
}

int Filesys::rmfile(string file) {
    for (int i = 0; i < filename.size(); i++) {
        if(filename[i] == file){
            if (firstblock[i] == 0) {
                filename[i] = ".....";
                return fssynch();
            }
        }
        else{
            cout << "File not empty;
            return 0
        }
    }
}

int Filesys::getfirstblocknumber(string file) {
    if(filename[i] == file) {
        filename[i] = ".....";
        return fssynch();
    }
    return -1;
}

int Filesys::addblock(string file, string block) {
    if(checkblock(file, block){
        Sdisk::getblock(block,buffer);
    }
    int firstb = getfirstblocknumber(file);
    if (firstb == -1) {
        cout << "File does not exist.";
        return 0;
    }    
    int allocate = fat[0];
    if (allocate == 0) {
        cout << "No space on device.";
        return 0;
    }
    fat[0] = fat[allocate];
    fat[allocate] = 0;
    if (firstb == 0) {
        for (int i = 0; i < filename.size(); i++) {
            if (filename[i] == file) {
                firstblock[i] = allocate;
            }
        }
    }
    else{
        int block = firstb;
        while(fat[block] != 0){
            block = fat[block]
        }
        fat[block] = allocate;
    }
    Sdisk::putblock(allocate,buffer);
    fssynch();
}

int Filesys::delblock(string file, int blocknumber) {
  if (checkblock(file,blocknumber)) {
      cout << "File does not exist or block does not belong to file.";
      return 0;
  }  
  if (getfirstblock(file) == blocknumber) {
      for (int i = 0; i < filename.size(); i++) {
          if (filename[i] == file) {
              firstblock[i] == fat[blocknumber];
          }
      }
  }
  else{
    int fblock = getfirstblock(file);
    while (fat[fblock] != block) {
        fblock = fat[fblock];
    }
    fat[fblock] = blocknumber;
  }
  fat[blocknumber]=fat[0]
  fat[0] = blocknumber'
  fssynch();
}

int Filesys::readblock(string file, int blocknumber, string& buffer) {
    int firsb = getfirstblocknumber(file);
    if (firstb == -1) {
        cout << "File does not exist";
        return 0;
    }
    if (firstb == 0) {
        cout << "File is empty";
        return 0;
    }
    int block == firstb;
    while (fat[block] != blocknumber and fat[block] != 0) {
        block = fat[block];    
    }
     if (fat[block]) {
         cout << "Block not found";
         return 0;
     }
     if (fat[block] == blocknumber) {
         Sdisk::getblock(blocknumber, buffer);
         return 1;
     }
}

int Filesys::writeblock(string file, int blocknumber, string buffer,) {
    
}

int Filesys::nextblock(string file, int blocknumber) {
    
}
