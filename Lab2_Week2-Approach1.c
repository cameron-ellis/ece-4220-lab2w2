#include <limits.h>
#include <sys/mman.h>
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


//Define global variables
struct period_info {
    struct timespec next_period;        // sec, nano-sec
    long period_ns;
};

struct Buffers {
    char *sBuffer1;        
    char *sBuffer2;
};


char fullString[20][256];


// Thread related Real-time functions
// ========================

static void periodic_task_init(struct period_info *pinfo, long period);
static void increment_period(struct period_info *pinfo);
static void wait_rest_of_period(struct period_info *pinfo);

// Thread-1 to read from "first.txt"
void *getFirstThd(void *ptr)
{
        
        
    char *commonBuff;
	commonBuff = (char *)ptr;
        
        
    //Open File
	
	//Check to make sure file opened correctly
	
        

	// Initialize the periodic Task and read line at a time from "First.txt"
	
	//Loop{
	//Read a line then wait_rest_of_period
	//}

	


	//Exit pthread
	pthread_exit(0);

}
 

//Do the same for thread Two
// Thread-2 to read from "second.txt"



// Thrid to synchronize the two threads
void *getThirdThd(void *ptr){
	//Variables
	int numOfStrings = 18, i = 0;
	
	struct Buffers *commonBuff;
	commonBuff = (struct Buffers *)ptr;
	char *sBuffer1 = commonBuff->sBuffer1;
	char *sBuffer2 = commonBuff->sBuffer2;
	
	
	// Initialize the periodic Task
	//Loop{ Copy the strings
		// From thread1 and 2 periodically using wait_rest_of_period
	//}

	//Exit pthread
	pthread_exit(0);
}
 
 
 void print_results(){

}
 
int main(int argc, char* argv[])
{
    struct sched_param param;
    pthread_attr_t attr;
    pthread_t thread1, thread2, thread3;
    int ret;
        
        
        
    char sBuffer1[256];
	char sBuffer2[256];
	struct Buffers myBuffers;
	myBuffers.sBuffer1 = (char *)&sBuffer1;
	myBuffers.sBuffer2 = (char *)&sBuffer2;
 

 
 
    /* Initialize pthread attributes (default values) */


        


	// Create 3 different threads -- First 2 threads will read from two
	// separate files and the 3rd will merge the two sets of information into
	// one.
	// Pass the Scheduler attributes to those threads



        
        
        
 
    /* Join the threads, which will make the process wait till the threads are done*/

       

 
 
        print_results();
        
out:
        return ret;
}



//   Write a function to determine the starting time of the thread
//static void increment_period(struct period_info *pinfo){}


// Write a function to the determine the ending time of the thread based on the initialized time
//static void increment_period(struct period_info *pinfo);


// Write a function to sleep for the remaining time of the period after finishing the task


