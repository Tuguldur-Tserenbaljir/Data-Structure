#include <algorithm> 
#include<iostream>
#include<string>
using namespace std; 
int main() 
{ 
    string s;
    getline(cin, s);
    reverse(s.begin(), s.end()); 
	cout<<""<<s; 
    return 0;
}