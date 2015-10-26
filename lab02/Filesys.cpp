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
#include "Sdisk.cpp"
#include <vector>
#include <string>
#include <ostringstream>

using namespace std;

void Filesys::Filesys(string disk, int numberofblocks, int bloacksize): Sdisk(disk,numberofblocks,blocksize){
    istring buffer;
    rootsize = getblocksize() / 12;
    fatsize = (getnumberofblocks() * 6.0) / (getblocksize() + 1);
    //If sdisk has root and fat read in to memory.
    if (buffer2[0] != '#') {
    istringstream buffer1, buffer4;
    string buffer2, buffer3;
    getblock(0,buffer2);
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
           getblock(i,s);
           buffer3 += s;
        }
        buffer4.str(buffer3);
        for (int i = 0; i < getnumberofblocks(); i++) {
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
        for (int i = fatsize + 1; i < getnumberofblocks(); i++) {
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
    std::vector<string> blocks1 = block(buffer3, getblocksize());
    std::vector<string> blocks2 = block(buffer4, getblocksize());
    putblock(0,blocks1[0]);
    for (int i = 0; i < blocks2.size(); i++) {
        putblock(i + 1,blocks2[i]);
    }


}

int Filesys::newfile(string file) {
}

int Filesys::rmfile(string file) {

}

int Filesys::getfirstblocknumber(string file) {

}

int Filesys::delblock(string file, int blocknumber) {
    
}

int Filesys::readblock(string file, int blocknumber, string& buffer) {

}

int Filesys::writeblock(string file, int blocknumber, string buffer,) {
    
}

int Filesys::nextblock(string file, int blocknumber) {
    
}
