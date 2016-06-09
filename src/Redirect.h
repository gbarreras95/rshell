#ifndef _REDIRECT_H_
#define _REDIRECT_H_
#include <string>
#include "Base.h"
using namespace std;

class Redirect: public Base{
    protected:
        char* arg1;
        string filename;
    
    public:
        Redirect(char* ops, int stat);
        virtual bool execute();
};

#endif