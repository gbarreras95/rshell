#include <iostream>
#include <string>
#include <unistd.h>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include "Redirect.h"
#include "Command.h"

using namespace std;

Redirect::Redirect(char* ops, int stat){
    //cout << "redirect const" << endl;
    status = stat;// 1 for <, 2 for >, 3 for >>
    string temp = "";
    int i = 0;
    while (ops[i] != '<' && ops[i] != '>')
    {
        temp += ops[i];
        i++;
    }
    arg1 = (char*)temp.c_str();
    i++;i++;
    
    if (this->status == 3)
        i++;
    
    while (ops[i] != '\0')
    {
        filename += ops[i];
        i++;
    }
    // if (stat == 1)
    //     //cout << "< ";
    // else if (stat == 2)
    //     //cout << "> ";
    // else if (stat == 3)
    //     //cout << ">> ";
    //cout << "Filename: |" << filename << "|" << endl;
    
    
}

bool Redirect::execute(){
    int outint, fd;
    outint = dup(1);
    int inint= dup(0);
    ofstream ofile;
    ifstream ifile;
    //streambuf* outbuf = cout.rdbuf();
    //streambuf* inbuf = cin.rdbuf();
    //streambuf* fbuf;
    if (this->status == 2){
        fd = open(filename.c_str(), O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
        dup2(fd, 1);
        close(fd);
        fflush(stdout);
            Base* cmd = new Command(arg1, 3);
            cmd->execute();
            dup2(outint,1);
            close(outint);
        // ofile.open(filename.c_str());
        // cout << filename << '|' << endl;
        // fbuf = ofile.rdbuf();
        // cout.rdbuf(fbuf);
        
    }
    if (this->status == 3){
        fd = open(filename.c_str(), O_RDWR | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
        dup2(fd, 1);
        close(fd);
        fflush(stdout);
            Base* cmd = new Command(arg1, 3);
            cmd->execute();
            dup2(outint,1);
            close(outint);
        // ofile.open(filename.c_str(), ofstream::app);
        // fbuf = ofile.rdbuf();
        // cout.rdbuf(fbuf);
        
    }
    else if (this->status == 1){
        fd = open(filename.c_str(), O_RDWR | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
        dup2(fd, 0);
        close(fd);
        fflush(stdin);
        Base* cmd = new Command(arg1, 3);
        cmd->execute();
        dup2(inint,0);
        close(inint);
    }
    

    // ofile.close();
    // cout.rdbuf(outbuf);
       
    return false;
}