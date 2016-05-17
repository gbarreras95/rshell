#ifndef _FORMAT_H_
#define _FORMAT_H_
#include <string>
#include <vector>
#include "Base.h"

using namespace std;

class Format: public Base{
    private:
        vector<Base*> commandLine; //Required vector of base pointers
        vector<string> connectors;
        vector<int> connectorPos;
        vector<string> cmds;
    public:
        Format(char * in);
        virtual bool execute();
        void format_commands(char * in, vector<string> &connectors, vector<int> &connectorPos, vector<string> &cmds);
  
    
};
#endif
