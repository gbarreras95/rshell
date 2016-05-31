#include "Base.h"
#include "Test.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <vector>
#include <string>

using namespace std;

Test::Test(char * line, int type){ //Constructor splits up command into char* array
                			// for the execvp
                			
              //cout << line << endl;
              
              
              status = type;
              string str(line);
              //cout << "test constrictor string: |" << str << cout << "|" << endl;
              if(str.at(0) == '[')
              {
                  str.erase(str.size() - 1, str.size() - 1);
                  
              }
              //cout << "test constrictor string: |" << str << cout << "|" << endl;
              int i =0;
              for(i = 0; str.at(i)!= ' '; i++)
              {}
              
              
              str.erase(0, i + 1);
              
            
              
              char *testLine = (char*) str.c_str();
              //cout << "line 42 test line: " << testLine << endl;
              if(*testLine == '-')
              {
                      char* hold = strtok(testLine, " ");
                        //cout << "line 48 hold : " << hold << endl;
                
                      flag = hold;
                        
                      filePath = strtok(NULL, " ");
                      
                      //cout << filePath << endl;
                    //   hold = strtok(fileHold, "/");
                    //   //cout << "/" << endl;
                    //   int i = 0;
                    //   while(hold != NULL)
                    //   {
                    //           filePath[i] = hold;
                              
                    //           i++;
                    //           hold = strtok(NULL, "/");
                    //   }
                       
                    //   filePath[i] = '\0';
                       
                    //   for(int j = 0; j < i; j++)
                    //   {
                    //           cout << filePath[j] << endl;
                    //   }
              }
              
              
              else{
                      string e = "-e";
                      flag = (char*) e.c_str();
                      
                      filePath = testLine;
                      
                      //cout << filePath << endl;
                    //   char* hold = strtok(testLine, "/");
                    //   int i = 0;
                    //   while(hold != NULL)
                    //   {
                    //           filePath[i] = hold;
                              
                    //           i++;
                    //           hold = strtok(NULL, "/");
                    //   }
                       
                    //   filePath[i] = '\0';
                    //   for(int j = 0; j < i; j++)
                    //   {
                    //           cout << filePath[j] << endl;
                    //   }
                      
              }
                
        }
        
        
bool Test::execute()
{
        // cout << "test execute" << endl;
        // cout << flag << endl;
        // cout << filePath << endl;
        // cout << "end";
        struct stat fileStat;
        
        stat(filePath, &fileStat);
        
        // cout << "test execute" << endl;
        // cout << flag << endl;
        // cout << filePath << endl;
        // cout << "end";
        
        if(strcmp(flag, "-e") == 0)
        {
            if(S_ISREG(fileStat.st_mode))
            {
                cout << "(True)" << endl;
                return true;
            }
            else if(S_ISDIR(fileStat.st_mode))
            {
                cout << "(True)" << endl;
                return true;
            }
            else
            {
                cout << "(False)" << endl;
                return false;
            }
            
        }
        
        
        else if(strcmp(flag, "-d") == 0)
        {
            if(S_ISDIR(fileStat.st_mode))
            {
                cout << "(True)" << endl;
                return true;
            }
            else
            {
                cout << "(False)" << endl;
                return false;
            }
        }
        else if(strcmp(flag, "-f") == 0)
        {
            if(S_ISREG(fileStat.st_mode))
            {
                cout << "(True)" << endl;
                return true;
            }
            else
            {
                cout << "(False)" << endl;
                return false;
            }
        }
        else
        {
            cout << "(False)" << endl;
            return false;
        }
        
}