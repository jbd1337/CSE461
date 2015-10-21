#include "Sdisk.h"
#include <string>
#include <iostream>

using namespace std;

int main()
{
   Sdisk cooldisk("cooldisk.txt",2,5);
   string info;
   info = "1111";
   string test;
   cooldisk.putblock(0,info);
   cooldisk.getblock(0,test);
    return 0;
}
