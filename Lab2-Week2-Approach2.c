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

static void periodic_task_init(struct period_info *pinfo);
static void inc_period(struct period_info *pinfo);
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
	FILE* f;
	f = fopen("first.txt","r");
	//Check to make sure file opened correctly
	if (f == NULL)
	{
		printf("first.txt failed to open!\n");
		exit(1);
	}
	
	// Initialize the periodic Task and read line at a time from "First.txt"
	struct period_info pinfo;
	periodic_task_init(&pinfo);
	//Loop{
	//Read a line then wait_rest_of_period
	//}
	int i = 0;
	while(i < 10) {
		fgets(commonBuff,256,f);
		i++;
		wait_rest_of_period(&pinfo);
	}
	fclose(f);
	//Exit pthread
	pthread_exit(0);
}

// Thread-2 to read from "second.txt"
void *getSecThd(void *ptr)
{
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
	FILE* f;
	f = fopen("second.txt","r");
	//Check to make sure file opened correctly
	if (f == NULL)
	{
		printf("second.txt failed to open!\n");
		exit(1);
	}
	
	// Initialize the periodic Task and read line at a time from "Second.txt"
	struct period_info pinfo;
	periodic_task_init(&pinfo);
	//Loop{
	//Read a line then wait_rest_of_period
	//}
	int i = 0;
	while(i < 10) {
		fgets(commonBuff,256,f);
		i++;
		wait_rest_of_period(&pinfo);
	}
	fclose(f);
	//Exit pthread
	pthread_exit(0);
}

// Thread-3 to copy the results into final buffer.
void *getThirdThd(void *ptr){
	//Get buffer pointer from main

	struct Buffers* myBuffers;
	myBuffers = (struct Buffers *)ptr;
    
	// Declare it as a real time task and pass the necessary params to the scheduler 
	struct sched_param param;
    param.sched_priority = MY_PRIORITY;
    if (sched_setscheduler(0, SCHED_FIFO, &param) == -1) {
        printf("Run the program as a sudo user\n");
 	    perror("sched_setscheduler failed, thread 1");
    	exit(20);
    }
	
	// Initialize the periodic Task and combine the strings from the buffer
	struct period_info pinfo;
	periodic_task_init(&pinfo);
	//Loop{
	//Read a line then wait_rest_of_period
	//}
	int i = 0;
	while (i < 19)
	{
		strcpy(fullString[i], myBuffers->sBuffer1);
		strcpy(fullString[i+1], myBuffers->sBuffer2);
		wait_rest_of_period(&pinfo);
		i += 2;
	}
	// Exit thread
	pthread_exit(0);
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
	pthread_create(&thrd1, NULL, &getFirstThd, myBuffers.sBuffer1);
	pthread_create(&thrd2, NULL, &getSecThd, myBuffers.sBuffer2);
	pthread_create(&thrd3, NULL, &getThirdThd, &(myBuffers));


	//Join pthreads and check to make sure they joined correctly
	pthread_join(thrd1, NULL);
	pthread_join(thrd2, NULL);
	pthread_join(thrd3, NULL);

	// PRINT
	print_results();	
}


// Helper Functions
// ================

// Function to print out results
void print_results(){
	//Print out full string
	for (int i = 0; i < 20; i++)
	{
		printf("%s", fullString[i]);
	}
}

//Write a function to determine the starting time of the thread
static void periodic_task_init(struct period_info *pinfo)
{
        /* for simplicity, hardcoding a 1ms period */
        pinfo->period_ns = 1000000;
 
        clock_gettime(CLOCK_MONOTONIC, &(pinfo->next_period));
}

// Write a function to the determine the ending time of the thread based on the initialized time
//static void increment_period(struct period_info *pinfo);
static void inc_period(struct period_info *pinfo) 
{
        pinfo->next_period.tv_nsec += pinfo->period_ns;
 
        while (pinfo->next_period.tv_nsec >= 1000000000) {
                /* timespec nsec overflow */
                pinfo->next_period.tv_sec++;
                pinfo->next_period.tv_nsec -= 1000000000;
        }
}

// Write a function to sleep for the remaining time of the period after finishing the task
static void wait_rest_of_period(struct period_info *pinfo)
{
        inc_period(pinfo);
 
        /* for simplicity, ignoring possibilities of signal wakes */
        clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &pinfo->next_period, NULL);
}