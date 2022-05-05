# simple_shell
  SHell, custom shell version 
  
COMPILATION

#### COMPILATION

- Type "make" in the console

> make

- If the make is not compiled then compile it as follows:

> gcc -Wall -Werror -Wextra -pedantic *.c -o hsh

#### SYNOPSIS

**./hsh**

#### DESCRIPTION

**Simple SHell** is a homebrewed **sh**-compatible command language interpreter that executes commands read from the standard input or from a file. Everytime a command is executed in the interactive method described above it will print the shell prompt again after execution is finished. Its use is very similar to the *sh* command line interpreter with the exceptions listed below.

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

#### AUTHOR

* **Mark Mutuota** [@tenmark86](https://github.com/tenmark86)

