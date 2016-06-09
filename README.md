rShell
------
Intro
------
Able to run commands such as ls, rm and other basic commands. It uses functions
such as execvp(), wait(), and fork(). It prints out one's username along with a
command promt $. It then takes in commands and runs them. If the command 
attempted to be run is not valid an error will occur and it will print out a 
message. It will continue to run untile exit is entered. 
Functions
---------
-Able to execute linux commands that are built into bash

-Able to execute multiple commands with connectors ||, ; and && in between

```sh
$ ls -l || vim && false ; cal
```

-When exit is entered the shell is terminated.

-able to run commands that include flags such as ls -l, or ls -a

Restrictions
------------
-CANNOT handle multiple pipe operations chained together

-Unable to run cd to change directory

-test command does not work after connectors

-A size limit for the command

-exit command needs to be run twice sometimes

-Parenthesis cannot be used inside of eachother ex: "((echo A && echo B) || echo c) && echo d is NOT allowed.

Development
------------
-We used
```c++
    strtok(char *, connector)
```

to parse the function.

-We used

```c++
if(execvp(commands[0], commands) == -1)
{
	perror("execvp");
}
```
to not only execute also determine if the command is valid
