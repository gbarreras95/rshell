#ifndef _TEST_H_
#define _TEST_H_

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

class Test: public Base{
    protected:
        char* filePath;
        char* flag;
    public:
        Test( char* line, int type );  
        bool execute();
};
#endif