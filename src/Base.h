#ifndef _BASE_H_
#define _BASE_H_
using namespace std;

class Base{ //Base class empty constructor, destructor, and virual execute
    protected:
        int status;
    public:
        Base(){};
        ~Base(){};
        virtual bool execute() = 0;
    
    
    
};

#endif
