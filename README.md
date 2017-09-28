Logfind is a small program that works similar to GNU grep. 
Basically, it allows you to input any address in your computer
using the syntax:

"./logfind -a <directory1> <directory2> ..."

and then find any file inside said directory by:

"./logfind -f <filename1> <filename2> ..."

The program will output the directory name, a '->' and the name of 
the file you were looking for.

To create the program just type "make logfind" and it will be ready
to go.
