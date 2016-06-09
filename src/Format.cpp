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
#include "Redirect.h"

using namespace std;

// streambuf* outbuf;
// ofstream filstr;
// filstr.open(temp);
// outbuf = filstr.rdbuf();
// cout.rdbuf(outbuf);

//split apart commands into workable pieces without connectors
void Format::format_commands(char * in, queue<string> &connectors, vector<int> &pipes, vector<string> &cmds){
    bool paralast = false;
    int open = 0;
    string temp = "";
    int i = 0;
    int numHold = 0;
    int j = 0;
    while (in[j] != '\0'){
        j++;
    }
    
    i = 0;
    while (i < j){
        numHold = 0;
        
        if (in[i] == '>'){
            numHold = i;
            temp = grabRed(in, numHold);
            cmds.push_back(temp); //cout << "pushing back 1" << endl;
            temp.clear();
            //cout << "in if > " << in[numHold] << endl;
            i = numHold;
            i++;
            //cout << "i: " << i << "j: " << j;
            continue;
        }
        
        else if (in[i] == '<'){
            numHold = i;
            temp = grabRed(in, numHold);
            cmds.push_back(temp); //cout << "pushing back 2" << endl;
            temp.clear();
            i = numHold;
            // cout << "i: " << i << endl;
            // cout << "j: " << j << endl;
            i++;
            continue;
        }
        
        // else if (in[i] == '|'){
        //     //temp = grabPipe(in, i);
        //     //cout << "in at i : " << in[i] << endl;
        //     i++;
        //     continue;
        // }
        
        else if (in[i] == '('){
            open++;
        }
        
        else if (in[i] == ')' && open > 0){
            open--;
            temp.clear();
            temp = formatFinder(in, i);
            //cmdType.push_back(1);
            cmds.push_back(temp);// cout << "pushing back 3" << endl;
            //cout << "temp: " << temp << endl;
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
                    //cmdType.push_back(2);
                    cmds.push_back(temp);// cout << "pushing back 4" << endl;
                    //cout << "temp: " << temp << endl;
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
                    //cmdType.push_back(2);
                    cmds.push_back(temp);// cout << "pushing back 5" << endl;
                    //cout << "temp: " << temp << endl;
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
                    //cmdType.push_back(2);
                    cmds.push_back(temp); //cout << "pushing back 6" << endl;
                    //cout << "temp: " << temp << endl;
                    temp.clear();
                }
            }
        }
        
        temp += in[i];
        i++;
        
    }
    
    if (paralast == false && numHold == 0)
        cmds.push_back(temp); //cout << "pushing back 7" << endl;
        //cout << "temp: " << temp << endl;
        //cmdType.push_back(2);
}
//create composite for command objects
Format::Format(char * in, int type){
    status = type;
    vector<int> stringPos;
    //cout << "befoore format commands" << endl;
    format_commands(in, connectors, pipes, cmds);
    //cout << "after format commands" << endl;
    
    for (unsigned int i = 0; i <cmds.size(); ++i){
        
        for(unsigned int j = 0; j < cmds.at(i).size(); j++){
            if (cmds.at(i).at(j) == '\0'){
                cmds.at(i).at(j) = ' ';
            }
        }
    }
    
    // //cout << "num commands: " << cmds.size() << endl;
    // for (unsigned int i = 0; i <cmds.size(); ++i){
    //     cout << '|' << cmds.at(i) << '|' << endl;
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
    
    
    //cout << "creating command line" << endl;
    for (unsigned int i = 0; i < cmds.size(); i++){
        
        //cout << "add new commands to vec of Base*" << endl;
        char* hold = (char*) cmds.at(i).c_str();
        
        while (hold[0] == ' '){
            for (int j = 0; hold[j] != '\0'; j++){
                hold[j] = hold[j+1];
            }
        }
        //cout << "hold: |" << hold << '|' << endl;
        
        if (testCheck(hold)){
            //cout << "make new test" << endl;
            cout << "|" << cmds.at(i) << "|" << endl;
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
        else if (redirectCheck(hold) == 1){
            //cout << "input redirection" << endl;
            commandLine.push_back(new Redirect(hold, 1));
        }
        else if (redirectCheck(hold) == 2){
            //cout << "output redirection overwrite" << endl;
            commandLine.push_back(new Redirect(hold, 2));
        }
        else if (redirectCheck(hold) == 3){
            //cout << "output redirection append" << endl;
            commandLine.push_back(new Redirect(hold, 3));
        }
        else if (findPipe(hold) == true){
            commandLine.push_back(new Command(hold, 7));
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
    
    //cout << "Commandline size: " << commandLine.size() << endl;
    
    for (unsigned int i = 0; i < commandLine.size(); i++){
        if(run == true){
            //cout << "executing command line" << endl;
            //int hold = 0;
            //pid_t temp = fork();
            completed = commandLine.at(i)->execute();
            // if (temp > 0){
            //     wait(&hold);
            // }
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
    //cout << "test check" << endl;
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
    //cout << "format check " << endl;
    return hold;
}

int Format::redirectCheck(char* in){
    //cout << "redirect check" << endl;
    int temp = 0;
    int i = 0;
    while (in[i] != '\0'){
        if (in[i] == '>' && in[i+1] != '>'){
            //cout<<"trunc found"<<endl;
            temp = 2;
            break;
        }
        else if (in[i] == '>' && in[i+1] == '>'){
            //cout<<"append found"<<endl;
            temp = 3;
            break;
        }
        else if (in[i] == '<'){
            temp = 1;
            break;
        }
        i++;
    }
    return temp;
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

string Format::grabRed(char* input, int& index){
    string temp;
    while ((input[index] != '&' || input[index] != '|' ||input[index] != ';') && index > 0){
        index--;
        //cout << "index: " << index << endl;
    }
    
   // cout << "inside while in grabred" << endl;
    temp += input[index];
    while ( input[index+1] != '\0' && input[index+1] != '&' && input[index+1] != '|' && input[index+1] != ';'){
        index++;
        temp += input[index];
    }
    
    return temp;
}

string Format::grabPipe(char* in, int &index){
    index--;index--;
    string temp;
    while (in[index] != ' ')
        index--;

    temp += in[index];
    while (in[index+1] != '&' && (in[index+1] != '|' && in[index+2] != '|') && in[index+1] != ';'){
        index++;
        temp += in[index];
    }
    //cout << "pipe: " << temp << endl;
    
    return temp;
}

bool Format::findPipe(char* in){
    string hold(in);
    for(unsigned i =0; i < hold.size(); i++)
    {
        if(hold.at(i) == '|')
        {
            return true;
        }
    }
    return false;
}