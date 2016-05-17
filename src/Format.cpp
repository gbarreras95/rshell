#include <iostream>
#include <string>
#include <unistd.h>
#include <cstring>
#include <cstdlib>
#include <iterator>
#include "Format.h"
#include "Command.h"

using namespace std;

//split apart commands into workable pieces without connectors
void Format::format_commands(char * in, vector<string> &connectors, vector<int> &connectorPos, vector<string> &cmds){
    string temp = "";
    int i = 0;
    while (in[i] != '\0'){
        if (in[i] == '&' && in[i+1] == '&'){
            in[i] = '\0';
            in[i+1] = '\0';
            connectors.push_back("&&");
            connectorPos.push_back(i);
            if(temp.empty() == false){
                
                cmds.push_back(temp);
                temp.clear();
            }
            i++;
			if(in[i] == '#')
				in[i] = '\0';
        }
        else if (in[i] == '|' && in[i+1] == '|'){
            in[i] = '\0';
            in[i+1] = '\0';
            connectors.push_back("||");
            connectorPos.push_back(i);
            if(temp.empty() == false){
                
                cmds.push_back(temp);
                temp.clear();
            }
            i++;
        }
        else if (in[i] == ';'){
            in[i] = '\0';
            connectors.push_back(";");
            connectorPos.push_back(i);
            if(temp.empty() == false){
                
                cmds.push_back(temp);
                temp.clear();
            }
        }
        
        temp += in[i];
        i++;
        
    }
    
    
    cmds.push_back(temp);
}
//create composite for command objects
Format::Format(char * in){
    
    vector<int> stringPos;
    
    format_commands(in, connectors, connectorPos, cmds);
    
    for (unsigned int i = 0; i <cmds.size(); ++i){
        
        for(unsigned int j = 0; j < cmds.at(i).size(); j++){
            if (cmds.at(i).at(j) == '\0'){
                cmds.at(i).at(j) = ' ';
            }
        }
    }
    
    
    
    
    
    
    
    for (unsigned int i = 0; i < cmds.size(); i++){
        
        //add new commands to vec of Base*
        char* hold = (char*) cmds.at(i).c_str();
        
        commandLine.push_back(new Command(hold));

    }
}

bool Format::execute(){
    bool run = true;
    bool completed = true;
    
    
    
    
   //uses two bools to decide if first called failed or not 
    for (unsigned int i = 0; i < commandLine.size(); i++){
        if(run == true){
            completed = commandLine.at(i)->execute();
        }
        
        if(i != commandLine.size() - 1)
        {
            if(connectors.at(i) == "&&")
            {
                if(completed == true)
                {
                    run = true;
                }
                else
                {
                    run = false;
                }
            }
            if(connectors.at(i) == "||")
            {
                if(completed == true)
                {
                    run = false;
                }
                else
                {
                    run = true;
                }
            }
            if(connectors.at(i) == ";")
            {
                run = true;
            }
        }
    }
    
    return true;
}
