#ifndef FILESYS_H
#define FILESYS_H
class Filesys: public Sdisk
{
public:
    Filesys(string disk, int numberofblocks, int blocksize): Sdisk(disk,numberofblocks,blocksize);
    int fsclose();
    int fssynch();
    int newfile(string file);
    int rmfile(string file);
    int getfirstblocknumber(string file);
    int addblock(string file, int blocknumber);
    int delblock(string file, int blocknumber);
    int readblock(string file, int blocknumber, string& buffer);
    int writeblock(string file, int blocknumber, string buffer);
    int nextblock(string file, int blocknumber);
private:
    int rootsize;
    int fatsize;
    std::vector<string> filename;
    std::vector<int> firstblock;
    std::vector<int> fat
    bool checkblock(string file, int blocknumber);
};
#endif
