#include <unistd.h>  // Needed for fork()
#include <limits.h>  // Needed for HOST_NAME_MAX
#include <stdio.h>   // Needed for printf()
#include <errno.h>   // Needed for EXIT_FAILURE and EXIT_SUCCESS
#include <stdlib.h>  // Needed for atoi()
#include <time.h>    // Needed for time and ctime
/*
 * These are the number of papers, tobacco and matches that we start with
 * A better way would be to pass them in via the Command Line Arguments
 */
#define PAPER_NUMBER "3"
#define TOBACCO_NUMBER "3"
#define MATCHES_NUMBER "3"
// The number of smoker threads that we are creating
#define NUMBER_OF_SMOKERS 3
// Didn't you know that False is 1 and True is 0?
#define TRUE 1
#define FALSE 0
// Function declearations
void child(int my_smoker_number, int number_of_smokers);
/**
 * Look ma! A main function!
 * This prints out all of our system information and then forks itself a bunch of times
 */
int main(int argc, char *argv[]) {
	// Let's get all of our information before we display it
	// Get the hostname
	char hostname[HOST_NAME_MAX];
	// Sometimes gethostname will fail, and then give us -1
	if(gethostname(hostname, sizeof hostname) == -1) {
		perror("gethostname() failed");
		exit(EXIT_FAILURE);
	}

	// We need a place to store our time
	time_t epoch_time;
	// Get the epoch
	epoch_time = time(&epoch_time);
	// Sometimes time() fails...
	if (epoch_time == -1) {
		perror("time() failed");
		exit(EXIT_FAILURE);
	}
	// Convert our time into a string
	// Because not everyone can read number seconds since January 1970...
	char * string_time = ctime(&epoch_time);
	// But sometimes even that fails...
	if (string_time == NULL) {
		perror("ctime() failed");
		exit(EXIT_FAILURE);
	}

	// Print out our information
	printf("AGENT INFO:\n");
	printf("\tHOSTNAME: %s\n", hostname);
	printf("\tPID: %d\n", getpid());
	printf("\tUID: %d\n", getuid());
	printf("\tTIME: %s\n", string_time);

	// Create the three environment variables
	// But even these fail sometimes.
	if (putenv("PAPER="PAPER_NUMBER) != 0) {
		perror("putenv() @ PAPER failed");
		exit(EXIT_FAILURE);
	}
	if (putenv("TOBACCO="TOBACCO_NUMBER) != 0) {
		perror("putenv() @ TOBACCO failed");
		exit(EXIT_FAILURE);
	}
	if (putenv("MATCHES="MATCHES_NUMBER) != 0) {
		perror("putenv() @ MATCHES failed");
		exit(EXIT_FAILURE);
	}

	// Print out the values we just stored
	char * paper   = getenv("PAPER");
	char * tobacco = getenv("TOBACCO");
	char * matches = getenv("MATCHES");
	// However, sometimes this fails (notice a pattern?)
	if (paper == NULL) {
		perror("getenv() @ PAPER failed");
		exit(EXIT_FAILURE);
	}
	if (tobacco == NULL) {
		perror("getenv() @ TOBACCO failed");
		exit(EXIT_FAILURE);
	}
	if (matches == NULL) {
		perror("getenv() @ MATCHES failed");
		exit(EXIT_FAILURE);
	}
	// We finally get to print them out!
	printf("PAPER: %s\n", paper);
	printf("TOBACCO: %s\n", tobacco);
	printf("MATCHES: %s\n", matches);

	// Let's start forking some children! (that's what she said...)
	printf("\nFORKING THREE SMOKERS!\n");
	// Make our children
	pid_t child1;
	pid_t child2;
	pid_t child3;
	// Fork the first child
	child1 = fork();
	// We need to see if we're in the parent or the child
	// But first, fork might have failed!
	if (child1 == -1) {
		perror("fork() @ Child #1 failed");
		exit(EXIT_FAILURE);
	} else if (child1 == 0) {
		// Child thread
		// Let's give some second-hand smoke to our young, impressionable children!
		child(1, NUMBER_OF_SMOKERS);
	} else {
		// Parent thread
		// Giving birth to children is tiring, so let's sleep
		//sleep(1);
		// But first we need to flush our buffers
		fflush(NULL);
		// Let's make another child!
		child2 = fork();
		// But it might not be successful
		if (child2 == -1) {
			perror("fork() @ Child #2 failed");
			exit(EXIT_FAILURE);
		} else if (child2 == 0) {
			// CPS needs to take me away...
			child(2, NUMBER_OF_SMOKERS);
		} else {
			// ...before I make more children!
			//sleep(1);
			// But not before I cleanse my system!
			fflush(NULL);
			// But mommy, I wanted triplets!
			child3 = fork();
			if (child3 == -1) {
				perror("fork() @ Child #3 failed");
				exit(EXIT_FAILURE);
			} else if (child3 == 0) {
				// Third-handed smoke is the best!
				child(3, NUMBER_OF_SMOKERS);
			} else {
				// Wait for the children to get lung cancer
				wait(NULL);
				wait(NULL);
				wait(NULL);
				// And then die
				printf("\nAGENT IS DONE!\n");
				exit(EXIT_SUCCESS);
			}
		}
	}
	// We should never get to this point...
	exit(EXIT_FAILURE);
}
/*
 * Hey! Listen!
 * It's a child -process-, not a child -thread-
 */
void child(int my_smoker_number, int number_of_smokers) {
	// Grab our environmental variables from the nether
	char * paper_string   = getenv("PAPER");
	char * tobacco_string = getenv("TOBACCO");
	char * matches_string = getenv("MATCHES");
	// And make a place to store our new ones
	char paper_new_string[8];
	char tobacco_new_string[8];
	char matches_new_string[8];
	// And the number of roll-your-own-cigarettes we can make
	int paper;
	int tobacco;
	int matches;

	// But first, BILLY MAYS HERE WITH SOME ERROR CHECKING!
	if (paper_string == NULL) {
		perror("getenv() @ PAPER failed");
		exit(EXIT_FAILURE);
	}
	if (tobacco_string == NULL) {
		perror("getenv() @ TOBACCO failed");
		exit(EXIT_FAILURE);
	}
	if (matches_string == NULL) {
		perror("getenv() @ MATCHES failed");
		exit(EXIT_FAILURE);
	}

	// Converting a string to a number is a painful process
	// But luckily we have this function whose name I can't pronounce to do it.
	paper   = atoi(paper_string);
	tobacco = atoi(tobacco_string);
	matches = atoi(matches_string);

	// In order to "fake" inner-process communication, we need to subtract
	// from current values our smoker number.
	paper = paper - (my_smoker_number - 1);
	tobacco = tobacco - (my_smoker_number - 1);
	matches = matches - (my_smoker_number - 1);
	// If we get negative numbers, round them to zero
	if (paper < 0) {
		paper = 0;
	}
	if (tobacco < 0) {
		tobacco = 0;
	}
	if (matches < 0) {
		matches = 0;
	}

	// Store those new values in our "environmental variables"
	// Is there a syscall on *NIX that won't fail?
	if (sprintf(paper_new_string, "PAPER=%d", paper) <= 0) {
		perror("sprintf @ New Paper failed");
		exit(EXIT_FAILURE);
	}
	if (sprintf(tobacco_new_string, "TOBACCO=%d", tobacco) <= 0) {
		perror("sprintf @ New Tobacco failed");
		exit(EXIT_FAILURE);
	}
	if (sprintf(matches_new_string, "MATCHES=%d", matches) <= 0) {
		perror("sprintf @ New Matches failed");
		exit(EXIT_FAILURE);
	}

	// I lied. Before, we only made the string.
	// Now we actually store it.
	if (putenv(paper_new_string) != 0) {
		perror("putenv() @ PAPER failed");
		exit(EXIT_FAILURE);
	}
	if (putenv(tobacco_new_string) != 0) {
		perror("putenv() @ TOBACCO failed");
		exit(EXIT_FAILURE);
	}
	if (putenv(matches_new_string) != 0) {
		perror("putenv() @ MATCHES failed");
		exit(EXIT_FAILURE);
	}

	// Print out our birth certificate
	printf("SMOKER S%d: %d\n", my_smoker_number, getpid());

	// And loop through until we get lung cancer.
	while(1) {
		// As before, get the variables from space
		paper_string   = getenv("PAPER");
		tobacco_string = getenv("TOBACCO");
		matches_string = getenv("MATCHES");

		// And make sure that nothing is broken
		if (paper_string == NULL) {
			perror("getenv() @ PAPER failed");
			exit(EXIT_FAILURE);
		}
		if (tobacco_string == NULL) {
			perror("getenv() @ TOBACCO failed");
			exit(EXIT_FAILURE);
		}
		if (matches_string == NULL) {
			perror("getenv() @ MATCHES failed");
			exit(EXIT_FAILURE);
		}

		// Strings can't be integers
		paper   = atoi(paper_string);
		tobacco = atoi(tobacco_string);
		matches = atoi(matches_string);

		// If we have negative resources, we can't smoke.
		// Hint: We should use this methodology for debts...
		if (paper <= 0) {
			printf("S%d: NO PAPER!\n", my_smoker_number);
			exit(EXIT_SUCCESS);
		}
		paper = paper - (number_of_smokers);

		if (tobacco <= 0) {
			printf("S%d: NO TOBACCO!\n", my_smoker_number);
			exit(EXIT_SUCCESS);
		}
		tobacco = tobacco - (number_of_smokers);

		if (matches <= 0) {
			printf("S%d: NO MATCHES!\n", my_smoker_number);
			exit(EXIT_SUCCESS);
		}
		matches = matches - (number_of_smokers);

		// Once again, round negative numbers to zero
		// It makes for a prettier display
		if (paper < 0) {
			paper = 0;
		}
		if (tobacco < 0) {
			tobacco = 0;
		}
		if (matches < 0) {
			matches = 0;
		}

		// Print out our resources for the *NEXT* round. (I don't know why we do this, but it's in the homework)
		printf("\nS%d Resources:\n", my_smoker_number);
		printf("\tS%d: PAPER IS AVAILABLE! P:%d\n", my_smoker_number, paper);
		printf("\tS%d: TOBACCO IS AVAILABLE! T:%d\n", my_smoker_number, tobacco);
		printf("\tS%d: MATCHES ARE AVAILABLE! M:%d\n", my_smoker_number, matches);

		// Now we store them in the nether
		if (sprintf(paper_new_string, "PAPER=%d", paper) <= 0) {
			perror("sprintf @ New Paper failed");
			exit(EXIT_FAILURE);
		}
		if (sprintf(tobacco_new_string, "TOBACCO=%d", tobacco) <= 0) {
			perror("sprintf @ New Tobacco failed");
			exit(EXIT_FAILURE);
		}
		if (sprintf(matches_new_string, "MATCHES=%d", matches) <= 0) {
			perror("sprintf @ New Matches failed");
			exit(EXIT_FAILURE);
		}

		// But as before, we're not actually storing them in lines 310-320, we're making the variable to make the variable
		if (putenv(paper_new_string) != 0) {
			perror("putenv() @ PAPER failed");
			exit(EXIT_FAILURE);
		}
		if (putenv(tobacco_new_string) != 0) {
			perror("putenv() @ TOBACCO failed");
			exit(EXIT_FAILURE);
		}
		if (putenv(matches_new_string) != 0) {
			perror("putenv() @ MATCHES failed");
			exit(EXIT_FAILURE);
		}

		// Our doctor gave us a grim prognosis
		printf("S%d IS SMOKING!\n\n", my_smoker_number);
		// Cleansing your system after smoking is an oxymoron.
		fflush(NULL);
		// Wait for our friends and family to get lung cancer from second-hand smoke.
		sleep(NUMBER_OF_SMOKERS);
	}
}
