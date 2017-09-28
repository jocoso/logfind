#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include "dbg.h"

#define MAX_SIZE 100

//A tool called logfind that let user thorough log files for text
//The idea is that i can type 

/*logfind <name>*/

//And it will search all the common places that log files are stored, 
//And print out every file that has the word "<name>" in it
//This tool take any sequence of words and assumes i mean AND

/*logfind <name0> <name1> <name2>*/

//Will be equal to ...

/*logfind <name0> && logfind <name1> && logfind <name2>*/


//PROTOTYPES
int findir(int argc, char* argv[], char data[][MAX_SIZE], size_t size);
int addir(int argc, char* argv[], char data[][MAX_SIZE], size_t size);
//----------

//MAIN FUNCTION
int main(int argc, char *argv[]){
	//VARIABLES
	FILE *file;
	int rc;
	size_t size = 0;
	char list[MAX_SIZE][MAX_SIZE];
	//---------
	
	//Opening directory...
	//TODO: Check how the program works when the directory is removed.
	if(access("directories.txt", F_OK) == 0){  //Does the directory exists?
		file = fopen("directories.txt", "r");
		check_debug(file != NULL, "File couldn't be opened");
		
		//Extracting the information from the text file and placing it into an array
		//Getting size of directory.
		while(fgets(list[size], sizeof list[size], file) != NULL){
			//Null operator is placed at the end, so strcmp works without problems
			list[size][strcspn(list[size], "\r\n")] = '\0';	
			size++;
		}
	} 
	
	//Check if the user input was correct. In case there are too few arguments specify proper syntax.
	check_debug(argc - 2 != 0, "./logfind <flag> <filename> ...\n");
	//Flags are supposed to start with a '-'
	check_debug(argv[1][0] == '-', "Not a valid input flag");
	
	
	//MAIN SWITCH
	switch(argv[1][1]){
		case 'a':	//flag 'a': is for adding directories in the search
			rc = addir(argc, argv, list, size);
			check_debug(rc == 0, "\n");
			break;
			
		case 'f':	//flag 'f': is for finding files in directories
			rc = findir(argc-2, argv, list, size);
			check_debug(rc == 0, "\n");
			break;

		default:
			printf("Not a valid input flag\n");
	}
	
	
	return 0;
error:
	return -1;
}



//findir function finds files in directories.
int findir(int argc, char* argv[], char data[][MAX_SIZE], size_t size){
	//VARIABLES
 	DIR *dir;
 	FILE *file;
 	struct dirent *ent;
 	unsigned short int was_found = 0;
 	//---------
 	
 	check_debug(size > 0, "You haven't add a directory yet. Type './logfind -a <directory name>' to add directories")
 	
 	file = fopen("directories.txt", "r");//Opening the file...
 	//Usual checking that the file was opened correctly
 	check_debug(file != NULL, "Directory couldn't be opened\n");
 	
 	//MAIN LOOP
	for(int i = 0; i < size; i++){
		//Assigning current directory 
 		dir = opendir(data[i]);
 		//Check if the directory assignment was successful
 		check_debug(dir != NULL, "Unable to open directory.");
 		
 		//Check if the given file name is in directory.
 		//If the assertion is true, it prints the directory 
 		//where it was found -> the name of the file
 		while((ent = readdir(dir)) != NULL){
 			for(int j = 0; j < argc; j++){
 				if((strcmp(argv[j+2], ent->d_name)) == 0){
 					printf("%s->%s\n", data[i], ent->d_name);
 					was_found = 1;
 				}
 		//Don't loop throught entire directory if it already found what it was looking for.
 				if(was_found){
 					was_found = 0;
 					break;
 				}			
 			}
 		
 		}
	}
	
	//Closing...
	closedir(dir);
	fclose(file);
 	return 0;
 error:
 	//To avoid problems when compiling,
 	//check if the filename is open before trying to close it.
 	if(file) fclose(file);
 	if(dir) closedir(dir);
 	return -1;
}

//The addir function add directory names inside directories.txt
//TODO: Change directory.txt to binary file
int addir(int argc, char* argv[], char data[][MAX_SIZE], size_t size){
	//VARIABLES
	DIR *dir;
	FILE *file;
	char new_data[size][MAX_SIZE];
	//---------
	
	
	//Avoid truncating a file by checking if there is any data in directories.txt
	if(size){
		file = fopen("directories.txt", "a");
	}else{
		file = fopen("directories.txt", "w");
	}
	
	//TODO: Check if this is really necessary 
	for(int i = 0; i < size; i++){
		strncpy(new_data[i], data[i], sizeof data[i]);
	}
	
	
	//MAIN LOOP
	for(int i = 2; i < argc; i++){
		//Try to open the given address
		dir = opendir((argv[i]));
		//Complains if it couldn't open it. Meaning the directory is not valid.
		check_debug(dir != NULL, "This is not a valid directory address.\n");
		//Otherwise place the directory string inside directories.txt
		for(int data_loop = 0; data_loop < size; data_loop++){
			if(strcmp(new_data[data_loop], argv[i]) == 0){
				return 0; //Never continue if the given data is identical to existing data.
			}
		}
		//Printing in file...
		fprintf(file, "%s\n", argv[i]);
	}
	
	
	//Closing Files
	fclose(file);
	return 0;
error:
	if(file) fclose(file);
	printf("Unable to add directory.\n");
	return -1;
}
