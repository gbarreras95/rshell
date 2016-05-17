rShell
------
Intro
------
Able to run commands such as ls, rm and other basic commands. It uses functions
such as execvp(), wait(), and fork(). 
Functions
---------
-Able to execute linux commands that are built into bash
-Able to execute multiple commands with connectors ||, ; and && in between
-When exit is entered the shell is terminated.
-able to run commands that include flags such as ls -l, or ls -a

Restrictions
------------
-Unable to run cd to change directory
-A size limit for the command
-exit command needs needs to be run twice sometimes
-Does not account for parenthesis and brackets

