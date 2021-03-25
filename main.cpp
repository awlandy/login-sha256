#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <openssl/sha.h>

using namespace std;

bool isUser = false;

string sha256(const string str)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(hash, &sha256);
    stringstream ss;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return ss.str();
}

bool fileExsists(const char *fileName){
	ifstream infile(fileName);
	return infile.good();
}

int main(){
	char filename[] = "key.txt";
	string key_name, key_pw;
	string storedName = "Andy";
	string storedPW   = "1228";

	if(fileExsists(filename)){
		ifstream key(filename);
		if(key.is_open()){
			getline(key, key_name);
			getline(key, key_name);
			key.close();
		}
	}else{
		ofstream key(filename);
		key << sha256(storedName) << '\n';
		key << sha256(storedPW) << '\n';
		key.close();
	}
	cout << "***login***";
	cout << "username: ";
	string name{};
	cin >> name;

	cout << "password: ";
	string pw{};
	cin >> pw;
		
	if (name == storedName && pw == storedPW){
		isUser = true;
		cout << "Welcome " << storedName << '\n';
	}
	else
		cout << "Login failed.\n";

	return 0;
}
