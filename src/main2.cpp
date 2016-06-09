#include <iostream>
#include <string>

using namespace std;

int main(){
    char * hold = (char*)"Convert this to a string\0";
    string temp = hold;
    
    cout << temp << '|' << endl;
    
    return 0;
}