#include <iostream>
#include <string>
#include <unistd.h>
#include <cstring>
#include <cstdlib>
#include <iterator>
#include <queue>
#include "Format.h"
#include "Command.h"
#include "Test.h"

using namespace std;

//split apart commands into workable pieces without connectors
void Format::format_commands(char * in, queue<string> &connectors, vector<int> &cmdType, vector<string> &cmds){
    bool paralast = false;
    int open = 0;
    string temp = "";
    int i = 0;
    while (in[i] != '\0'){
        
        if (in[i] == '('){
            open++;
        }
        
        else if (in[i] == ')' && open > 0){
            open--;
            temp.clear();
            temp = formatFinder(in, i);
            cmdType.push_back(1);
            cmds.push_back(temp);
            temp.clear();
            cleanUp(in, i);
            if (in[i+1] == '\0')
                paralast = true;
        }
        
        else if ((in[i] == '&' && in[i+1] == '&') && open == 0){
            in[i] = '\0';
            in[i+1] = '\0';
            connectors.push("&&");
            if(temp.empty() == false){
                bool allspace = true;
                for (unsigned int i = 0; i < temp.size(); i++)
                    if (temp[i] != ' ')
                        allspace = false;
                if (allspace == false){
                    cmdType.push_back(2);
                    cmds.push_back(temp);
                    temp.clear();
                }
            }
            
            i++;
			if(in[i] == '#')
				in[i] = '\0';
				
        }
        
        else if ((in[i] == '|' && in[i+1] == '|') && open == 0){
            in[i] = '\0';
            in[i+1] = '\0';
            connectors.push("||");
            if(temp.empty() == false){
               bool allspace = true;
                for (unsigned int i = 0; i < temp.size(); i++)                    
                    if (temp[i] != ' ')
                        allspace = false;
                if (allspace == false){
                    cmdType.push_back(2);
                    cmds.push_back(temp);
                    temp.clear();
                }
            }
            i++;
        }
        
        else if ((in[i] == ';') && open == 0){
            in[i] = '\0';
            connectors.push(";");
            if(temp.empty() == false){
               bool allspace = true;
                for (unsigned int i = 0; i < temp.size(); i++)
                    if (temp[i] != ' ')
                        allspace = false;
                if (allspace == false){
                    cmdType.push_back(2);
                    cmds.push_back(temp);
                    temp.clear();
                }
            }
        }
        
        temp += in[i];
        i++;
    }
    
    if (paralast == false)
        cmds.push_back(temp);
        cmdType.push_back(2);
}
//create composite for command objects
Format::Format(char * in, int type){
    status = type;
    vector<int> stringPos;
    
    format_commands(in, connectors, cmdType, cmds);
    
    for (unsigned int i = 0; i <cmds.size(); ++i){
        
        for(unsigned int j = 0; j < cmds.at(i).size(); j++){
            if (cmds.at(i).at(j) == '\0'){
                cmds.at(i).at(j) = ' ';
            }
        }
    }
    
    // cout << "num commands: " << cmds.size() << endl;
    // for (unsigned int i = 0; i <cmds.size(); ++i){
    //     cout << cmds.at(i) << endl;
    // }
    // cout << endl;
    // cout << "num commands status: " << cmdType.size() << endl;
    //  for (unsigned int i = 0; i <cmdType.size(); ++i){
    //     cout << cmdType.at(i) << endl;
    // }
    // cout << endl;
    
    
    // cout << "output queue" << endl;
    // while ( !connectors.empty() ){
    //     cout << connectors.front() << endl;
    //     connectors.pop();
    // }
    // cout << endl;
    
    
    
    for (unsigned int i = 0; i < cmds.size(); i++){
        
        //add new commands to vec of Base*
        char* hold = (char*) cmds.at(i).c_str();
        if (testCheck(hold)){
            //cout << "make new test" << endl;
            //cout << "|" << cmds.at(i) << "|" << endl;
            while (cmds.at(i).at(cmds.at(i).size()-1) == ' '){
                cmds.at(i).erase(cmds.at(i).size()-1, cmds.at(i).size()-1);
            }
            while (cmds.at(i).at(0) == ' '){
                cmds.at(i).erase(0 , 1);
            }
            
            
            //cout << "format: " << "|" << hold << "|" << endl;
            commandLine.push_back(new Test(hold, 3));
        }
        else if (formatCheck(hold)){
            //cout << "make new format" << endl;
            commandLine.push_back(new Format(hold, 1));
        }
        else{
            //cout << "make new command" << endl;
            commandLine.push_back(new Command(hold, 2));
        }
    
    }
}

bool Format::execute(){
    bool run = true;
    bool completed = true;
    
    
    for (unsigned int i = 0; i < commandLine.size(); i++){
        if(run == true){
            completed = commandLine.at(i)->execute();
        }
        
        if(i != commandLine.size() - 1)
        {
            if(connectors.front() == "&&")
            {
                if(completed == true)
                {
                    run = true;
                }
                else
                {
                    run = false;
                }
                connectors.pop();
            }
            else if(connectors.front() == "||")
            {
                if(completed == true)
                {
                    run = false;
                }
                else
                {
                    run = true;
                }
                connectors.pop();
            }
            else if(connectors.front() == ";")
            {
                run = true;
                connectors.pop();
            }
        }
    }
    
    return completed;
}

bool Format::testCheck(char* input){
    string firstChar;
    string lastChar;
    
    char temp[1000];
    strcpy(temp, input);
    char* hold = strtok(temp, " ");
    firstChar = hold;
    if (firstChar == "test")
        return true;
    while (hold != '\0'){
        lastChar = hold;
        hold = strtok(NULL, " ");
    }
    if (firstChar == "[" && lastChar == "]")
        return true;
    
    return false;
}

bool Format::formatCheck(char* input){
    bool hold = false;
    int i = 0;
    while (input[i] != '\0'){
        if (input[i] == '&' && input[i+1] == '&')
            hold = true;
        else if (input[i] == '|' && input[i+1] == '|')
            hold = true;
        else if (input[i] == ';')
            hold = true;
        i++;
    }
    return hold;
}

string Format::formatFinder(char* cutMe, int in){
    string hold = "";
    while (cutMe[in] != '('){
        in--;   
    }
    in++;
    while (cutMe[in] != ')'){
        hold += cutMe[in];
        in++;
    }
    
    return hold;
}

void Format::cleanUp(char* cleanMe, int in){
    while (cleanMe[in] != '('){
        cleanMe[in] = ' ';
        in--;
    }
    cleanMe[in-1] = ' ';
}