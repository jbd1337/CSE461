/****************************************************************** 
* Name: Joshua Dunham
* Course: CSE461
* Date: 10/05/2015
* Program: lab1.cpp
*
*
*
*******************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class PasswordFile
{
 public:
 PasswordFile(string filename);// opens the file and reads the names/passwords in the vectors user and password.
 void addpw(string newuser, string newpassword); //this adds a new user/password to the vectors and writes the vectors to the file filename
 bool checkpw(string usr, string passwd); // returns true if user exists and password matches
 static void newsalt(int ns);
 private:
 static int salt;
 string filename; // the file that contains password information
 vector<string> user; // the list of usernames
 vector<string> password; // the list of passwords
 void synch(); //writes the user/password vectors to the password file
 string encrypt(string s);
 string decrypt(string s);
};

int PasswordFile::salt=1;

 void PasswordFile::newsalt(int ns)
 { salt=ns;
 }
  
string PasswordFile::encrypt(string s)
{ for (int i=0; i<s.size(); i++)
      { s[i]+=salt;
      }
 return s;
}

PasswordFile::PasswordFile(string filename){
	string usr,pass;
	ifstream infile;
	infile.open(filename.c_str());
	infile >> usr >> pass;
	while(infile.good()){
		user.push_back(usr);
		password.push_back(pass);
		infile >> usr >> pass;
	}
	user.push_back(usr);
	password.push_back(pass);
	infile.close();
}
//string PasswordFile::decrypt(string s)
// NOT NEEDED - 
//{ for (int i=0; i<s.size(); i++)
//      { s[i]-=salt;
//     }
// return s;
void PasswordFile::synch(){
	ofstream outfile;
	outfile.open("password.txt");
	for(int i = 0; i < password.size(); i++){
		outfile << user[i]  << " " << password[i] << endl;
	}
	outfile.close();
        return;
}
void PasswordFile::addpw(string newuser, string newpassword){
    for (int i = 0; i < user.size(); i++) {
        if(user[i] == newuser){
            cout << "User Exists" << endl;
            return;
        }
    }
        cout << 1 << endl;
	user.push_back(newuser);
	password.push_back(encrypt(newpassword));
	synch();	
        return;
}
bool PasswordFile::checkpw(string usr, string passwd){
	for(int i = 0; i < user.size(); i++){
		if(user[i] == usr){
			if(password[i] == encrypt(passwd)){
				return true;
			}else{ return false; }
		}
	} 
}
  
int main()
{
 PasswordFile passfile("password.txt");
 passfile.addpw("dbotting","123qwe");
 passfile.addpw("egomez","qwerty");
 passfile.addpw("tongyu","liberty");
 passfile.addpw("dbotting","DOH!");
 if (passfile.checkpw("dbotting","123qwe") && passfile.checkpw("egomez","qwerty")&& passfile.checkpw("tongyu","liberty")&& !passfile.checkpw("dbotting","DOH!")){
     cout << "works" << endl;
    }
}

