# simple_shell
![Uploading shell.jpeg…]()

SHell, custom shell version 
  
# Requirements

# General
* Allowed editors: ```vi, vim, emacs```
* All your files will be compiled on ```Ubuntu 20.04 LTS``` using ```gcc```, using the options ```-Wall -Werror -Wextra -pedantic -std=gnu89```
* All your files should end with a new line
* A ```README.md``` file, at the root of the folder of the project is mandatory
* Your code should use the ```Betty style```. It will be checked using ```betty-style.pl``` and ```betty-doc.pl```
* Your shell should not have any memory leaks
* No more than 5 functions per file
* All your ```header files``` should be include guarded
* Use system calls only when you need to (why?)
* Write a ```README``` with the description of your project
* You should have an ```AUTHORS file``` at the root of your repository, listing all individuals having contributed content to the repository. Format, see ```Docker```

# More Info

# Output
* Unless specified otherwise, your program must have the exact same output as sh (/bin/sh) as well as the exact same error output.
* The only difference is when you print an error, the name of the program must be equivalent to your argv[0] (See below)

#### COMPILATION

- Type "make" in the console

> make

- If the make is not compiled then compile it as follows:

> gcc -Wall -Werror -Wextra -pedantic *.c -o hsh

#### TESTING
Your shell should work like this in interactive mode:
```$ ./hsh
($) /bin/ls
hsh main.c shell.c
($)
($) exit
$
```
But also in non-interactive mode:
```
$ echo "/bin/ls" | ./hsh
hsh main.c shell.c test_ls_2
$
$ cat test_ls_2
/bin/ls
/bin/ls
$
$ cat test_ls_2 | ./hsh
hsh main.c shell.c test_ls_2
hsh main.c shell.c test_ls_2
$
```
#### SYNOPSIS

**./hsh**

#### DESCRIPTION

**Simple_shell** is a homebrewed **sh**-compatible command language interpreter that executes commands read from the standard input or from a file. Everytime a command is executed in the interactive method described above it will print the shell prompt again after execution is finished. Its use is very similar to the *sh* command line interpreter with the exceptions listed below.

#### OPTIONS

This shell does not take any options as of now. However it does handle the CTRL+D and CTRL+C keyboard signals.

#### ARGUMENTS

This shell does not take arguments but if what is desired is to interpret a command in a non interactive fashion then it must be invoked as descibed in the *Invocation* section.

#### INVOCATION

**Interactive Mode -** To call the shell in its interactive mode it must be called as follows:

> ./hsh

After this invocation the prompt will be printed and the user will be able to enter command line arguments.

**Non-Interactive Mode -** To call the shell in its non-interactive mode you first call the command and then pipe it to the shell as follows:

> [Command] [Command Options] [Arguments] ... | ./hsh

After this invocation the shell will exit and return to the terminal that called it.

#### BUILT-INS

The shell has a few built-in functions. These are: **setenv**, **unsetenv**, **exit, env** and **cd.**

#### BUGS

The shell does not handle the following special characters _", ', `, \, *, #._

#### AUTHORS

* **Mark Mutuota** [@tenmark86](https://github.com/tenmark86)
* **Ken Kamau** [@Ken-Kamau](https://github.com/Ken-Kamau)


