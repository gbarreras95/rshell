#ifndef _COMMAND_H_
#define _COMMAND_H_
#include "Base.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

using namespace std;

class Command : public Base{
    protected:
        char *commands[100];
    public:
        Command(char * cmd, int type); 
     
        
        bool execute();
    
    
};




#endif
