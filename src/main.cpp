#include <iostream>
#include <string>
#include <unistd.h>
#include <fstream>
#include <cstring>
#include <iterator>
#include "Format.h"
#include "Command.h"

using namespace std;

void delete_comments(char* fixMe){
	for (int i = 0; fixMe[i] != '0'; i++){
		if (fixMe[i] == '#')
			fixMe[i] = '\0';
	}
}

int main(){
    streambuf* backup;
    backup = cout.rdbuf();
    
    char *name = getlogin();   //The extra credit login info
    char server[256];
    gethostname(server, 250);
    string prompt = "$ ";

    if (name != NULL && server != NULL){
 	   string userName = name;
 	   string serverName = server;
 	   prompt = userName + "@" + serverName + "$ ";
    }
   
   while (true){ //this is the rshell        
       cout << prompt;
       char userCommand[10000]; 
       cin.getline (userCommand, 100000, '\n'); //takes in the new line
       
       if (userCommand[0] == '\0'){ 
            continue;
       }
    	delete_comments(userCommand);
		 
       Format newLine(userCommand, 1);  //Taking in the commands
       newLine.execute();  // Executing the commands
       cout.rdbuf(backup);
   }
 
 
    return 0;  
}
