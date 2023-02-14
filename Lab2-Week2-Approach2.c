#include <fcntl.h>
#include <getopt.h>
#include <linux/types.h>
#include <sched.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/timerfd.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>

#define MY_PRIORITY (49)  // kernel is priority 50


void print_results();


//Define global variables
char fullString[20][256];

struct Buffers {
    char *sBuffer1;        
    char *sBuffer2;
};

// Timer Functions
// ===============
// Timer related structures and functions:
struct period_info {
    struct timespec next_period;        // sec, nano-sec
    long period_ns;
};



// Thread related Real-time functions
// ========================

static void periodic_task_init(struct period_info *pinfo, long period);
static void increment_period(struct period_info *pinfo);
static void wait_rest_of_period(struct period_info *pinfo);


// Thread-1 to read from "first.txt"

void *getFirstThd(void *ptr){
	//Get string pointer from main

	char *commonBuff;
	commonBuff = (char *)ptr;
        


	// Declare it as a real time task and pass the necessary params to the scheduler 
	struct sched_param param;
    param.sched_priority = MY_PRIORITY;
    if (sched_setscheduler(0, SCHED_FIFO, &param) == -1) {
        printf("Run the program as a sudo user\n");
 	    perror("sched_setscheduler failed, thread 1");
    	exit(20);
    }

        
    //Open File
	
	//Check to make sure file opened correctly
	
        

	// Initialize the periodic Task and read line at a time from "First.txt"
	
	//Loop{
	//Read a line then wait_rest_of_period
	//}
	//Exit pthread
	
}

// Thread-2 to read from "second.txt"
void *getSecThd(void *ptr)
{}

// Thread-3 to copy the results into final buffer.
void *getThirdThd(void *ptr){



}

int main(void) 
{
	//Declare variables	
	pthread_t thrd1, thrd2, thrd3;

        
    char sBuffer1[256];
	char sBuffer2[256];
	struct Buffers myBuffers;
	myBuffers.sBuffer1 = (char *)&sBuffer1;
	myBuffers.sBuffer2 = (char *)&sBuffer2;



	// Create 3 different threads -- First 2 threads will read from two
	// separate files and the 3rd will merge the two sets of information into
	// one.
	// Pass the Scheduler attributes to those threads




	//Join pthreads and check to make sure they joined correctly	
}


// Helper Functions
// ================

// Function to print out results
void print_results(){
	//Print out full string

}





//Write a function to determine the starting time of the thread
//static void increment_period(struct period_info *pinfo){}


// Write a function to the determine the ending time of the thread based on the initialized time
//static void increment_period(struct period_info *pinfo);


// Write a function to sleep for the remaining time of the period after finishing the task





