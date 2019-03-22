## RUNNING

- run "make"

- execute by using "./BansalJi"

- type "quit" or "exit" to exit the shell

## FEATURES

#### ls command
###### Usage:
- ls takes arguments as flags (in the form -(flagname)).
- It lists the files of all the current directory mentioned, in the form of option selected by the flags.

* "ls" - lists in alphabetical order
* "ls -a" - display hidden files
* "ls -l" - long list
* "ls -al"/"ls -la" - long list including hidden files

- Similarities to real command: "ls -a" displays files sorted in alphabetical order (NOT CONSIDERING THE PREPENDED '.')  

#### cd command
* "cd (absolute path)" - goes to absolute path
* "cd" - goes to ~/
* "cd .." - goes to previous directory
* "cd ." - goes to same directory

#### echo command
* "echo" - prints empty line
* "echo text" - prints "text"

#### pwd command
* "pwd" - prints absolute path of present working directory

#### pinfo command
* "pinfo" : prints the process related info of the shell program 
* "pinfo <pid>" : prints the process info about given pid
- pid -- 
- Process status -- {R/S/S+/Z}
- Virtual Memory
- Executable path -- (Absolute path - includes ~/ if executable is present inside the shell directory)