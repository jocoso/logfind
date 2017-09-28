Logfind is a small program that works similar to GNU grep. 
Basically, it allows you to input any directory address 
in your computer by using the syntax:

"./logfind -a <directory1> <directory2> ..."

and then find any file inside said directory by:

"./logfind -f <filename1> <filename2> ..."

If successful, the program will output the directory name, a '->' and the name of 
the file you were looking for. Otherwise, it won't output anything.

To create logfind just type "make logfind" and it will be ready
to go.
