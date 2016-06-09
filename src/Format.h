#ifndef _FORMAT_H_
#define _FORMAT_H_
#include <string>
#include <vector>
#include <queue>
#include "Base.h"

using namespace std;

class Format: public Base{
    private:
        vector<Base*> commandLine; //Required vector of base pointers
        queue<string> connectors;
        vector<int> pipes;
        vector<string> cmds;
    public:
        Format(char * in, int type);
        virtual bool execute();
        void format_commands(char * in, queue<string> &connectors, vector<int> &cmdType, vector<string> &cmds);
        bool testCheck(char* in);
        bool formatCheck(char* in);
        int redirectCheck(char* in);
        string formatFinder(char* cutMe, int in);
        void cleanUp(char* cleanMe, int in);
        string grabRed(char* input, int& index);
        string grabPipe(char* in, int &index);
        bool findPipe(char* in);
  
    
};
#endif
