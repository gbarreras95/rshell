
#include "Base.h"
#include "Command.h"
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

Command::Command(char * cmd, int type){ //Constructor splits up command into char* array
                status = type;		// for the execvp
                
                
                char * chold = new char[' '];
                if(strcmp(cmd, chold) == 0){
                    cout << " doesntworks" << endl;
                }
                char* hold = strtok(cmd, " ");
                
                
                int i = 0;
                while(hold != NULL)
                {
                        commands[i] = hold;
                        hold = strtok(NULL, " "); 
                        i++;
                }
                
                commands[i] = '\0';
                
                
                
        } 
     
        
 bool Command::execute() // execute
        {
            
                pid_t pid = fork();
                int hold;
                
                if(strcmp(*commands, "exit") == 0) // quits when type exit
                {
                    exit(0);
                }
                
                
                
                if(pid == -1)  //if forking error
                {
                        perror("fork()");
                        return false;
                }
                
                if(pid == 0)  //if in child process execute
                {
                        
                        if(execvp(commands[0], commands) == -1)
                        {
                                perror("execvp"); //prints out error message
                                return false;
                                
                        }
                        
                }
                else if(pid > 0) //if in parent process 
                {
                        wait(&hold);
                }
                if(hold != 0)
                {
                        return false;
                }
                return true;
}
    
    






