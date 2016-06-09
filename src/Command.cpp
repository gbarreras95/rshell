
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
                    //cout << " doesntworks" << endl;
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
                if(this->status == 7){
                        
                        int mypipefd[2];
                        //cout << "hello" << endl;
    
                        //    string hello;
                            
                            
                        //    char* cmd
                            
                        //     char* hold = strtok(cmd, "|");
                        //     //char* commands[2];            
                        //     char* cmd1;
                        //     char* cmd2;
                        //     cmd1 = hold;   
                            
                        //     while(hold != NULL)
                        //     {
                        //         cmd2 = hold;
                        //         hold = strtok(NULL, " "); 
                                
                        //     }
                                    
                            
                            
                        //      cout << cmd1 << "!" << endl;
                            
                        //      cout << cmd2 << "!" <<  endl;
                            
                        //     string hold1(cmd1);
                        //     if(hold1.at(hold1.size() - 1) == ' ')
                        //     {
                        //         hold1.at(hold1.size() - 1) = '\0';
                                
                        //     }
                            
                        //     string hold2(cmd2);
                        //     if(hold2.at(hold2.size() - 1) == ' ')
                        //     {
                        //         hold2.at(hold2.size() - 1) = '\0';
                                
                        //     }
                            
                        //     cmd1 = (char*) hold1.c_str();
                        //     cmd2 = (char*) hold2.c_str();
                            
                        
                            
                            int ret;
                            ret = pipe(mypipefd);
                            if(ret == -1)
                            {
                                perror("pipe");
                                return false;
                            }
                            
                            pid_t pid=fork();
                        
                            
                        
                            if(pid==0){
                        
                                close(mypipefd[0]);  //close the read/write
                                dup2(mypipefd[1], 1); 
                                execlp( commands[0], commands[0], NULL);
                            }
                        
                            else{
                        
                                close(mypipefd[1]);         // close the read/write
                                dup2(mypipefd[0], 0);
                                execlp(commands[2], commands[2] , NULL);           
                            }
                            return true;
                        
                }
                
                
                
                
                else{
                        int hold;
                
                        if(strcmp(*commands, "exit") == 0) // quits when type exit
                        {
                        exit(0);
                        }
                
                        pid_t pid = fork();
                
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
}
    
    






