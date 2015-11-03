// You can use this to test your Filesys class 
#include "Filesys.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;
int main()
{
	Sdisk disk1("disk1",256,128);
	Filesys fsys("disk1",256,128);
	fsys.newfile("file1");
	fsys.newfile("file2");

	string bfile1;
	string bfile2;

	for (int i=1; i<=1024; i++)
	 {
		 bfile1+="1";
	 }

	vector<string> blocks=fsys.block(bfile1,128); 

	int blocknumber=0;

	for (int i=0; i < blocks.size(); i++)
	 {
		fsys.addblock("file1",blocks[i]);

	 }
	fsys.delblock("file1",fsys.getfirstblocknumber("file1"));

	for (int i=1; i<=2048; i++)
	 {
		 bfile2+="2";
	 }

	blocks=fsys.block(bfile2,128); 

	for (int i=0; i< blocks.size(); i++)
	 {
		 fsys.addblock("file2",blocks[i]);
	 }
	cout << fsys.getfirstblocknumber("file2") << endl;
	fsys.delblock("file2",fsys.getfirstblocknumber("file2"));
	fsys.printRoot();
	fsys.newline();
	fsys.printFat();
}

