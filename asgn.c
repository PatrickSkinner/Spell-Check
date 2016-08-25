/**
 * asgn.c
 * @author Patrick Skinner, Cassidy Mowat, Luke Biggs
 *
 * The entry point for our 2015 COSC242 assignment.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <time.h>
#include "container.h"
#include "mylib.h"
#include "flexarray.h"
#include "rbt.h"
#include "htable.h"

/* Variable declarations */
FILE *fp;
container_t type;
int tableSize;
htable h;
int printFlag;
int timeFlag;
clock_t start, end;

/* A method used to print the help method of our program,
   detailing what the various user inputs do. */
static void help_message() {
    fprintf(stderr, "\n\n%s%s",
        "Stores words read from a specified file on the command line.\n"
        "Words are stored in a hash table using two forms of container.\n"
        "Words are then read in from stdin.\n"
        "Words read from stdin not in the hash table are printed to stdout.\n"
        "Once finished reading in words from stdin, the program finishes.\n\n"
        " -r        Tells the program to use an RBT as its container type.\n"
        " -s size   Uses 'size' to denote the size of the hash table.\n",
        " -p        Prints the hash table to stdout one line per container.\n"
        " -i        Prints information to stderr relating to time taken to\n"
        "           fill the hash table, search the hash table and how\n"
        "           many unknown words were found.\n"
        " -h        Prints this help message to stderr.\n\n\n");
}


/**
 * This method is used to handle the options given on the command line,
 * printing out the help message by default
 *
 * @param argc the number of command line arguments.
 * @param argv array of strings containing the command line arguments.
 */
static void options(int argc,char **argv){
    const char *optstring = "rs:pih";
    char option;

    while ((option = getopt(argc, argv, optstring)) != EOF) {
        switch (option) {
			case 'r':
				type = RED_BLACK_TREE;
				break;
			case 's':
				tableSize = atoi(optarg);
				break;
			case 'p':
				printFlag = 1;
				break;
			case 'i':
				timeFlag = 1;
				break;
			case 'h':
				help_message();
				exit(EXIT_SUCCESS);
				break;
			default:
				help_message();
				exit(EXIT_SUCCESS);
        }
    }
}

/**
 * The entry point of the program (main method).
 *
 * @param argc the number of command line arguments.
 * @param argv array of strings containing the command line arguments.
 *
 * @return EXIT_SUCCESS if program is execution is successful.
 */
int main(int argc, char **argv){
	char word[256];
	double fillTime;
	double searchTime;
	int unknownWords = 0;

	tableSize = 3877;
	options(argc, argv);
	h = htable_new(tableSize, type);
	fp = fopen(argv[optind], "r");

	start = clock();
	while (getword(word, sizeof word, fp) != EOF){
		htable_insert(h, word);
	}
	end = clock();
	fillTime = (end - start) / (double)CLOCKS_PER_SEC;

	start = clock();
	while (getword(word, sizeof word, stdin) != EOF){
		if(htable_search(h, word) == 0){
			printf("%s\n", word);
			unknownWords++;
		}
	}
	end = clock();
	searchTime = (end - start) / (double)CLOCKS_PER_SEC;

	if(printFlag != 0){
		printf("\n\n");
		htable_print(h);
	}

	if(timeFlag != 0){
		printf("\n\n%s%f\n", "Fill Time: ", fillTime);
		printf("%s%f\n", "Search Time: ", searchTime);
		printf("%s%d\n", "Unknown Words: ", unknownWords);
	}

	fclose(fp);
	htable_free(h);

	return EXIT_SUCCESS;
}
