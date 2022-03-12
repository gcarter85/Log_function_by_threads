#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>

/*
Name: Carter Gamary
Course: CSCI 4500 - 820
Date: 2022/02/28
Assignment: Program #1
*/

// Global Variables
int ops;
int numThread;
int flow = 1;
double inVal;
double result = 0.0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *threadMath(void *arg);

// Thread Data Struct
typedef struct _thread_data_t {
    int tID;
    double eq;
} thread_data_t;

// Completes the calculations for the threads
void *threadMath(void *arg) {
    thread_data_t *thr = (thread_data_t *)arg;
    int thread = thr->tID;
    ++thread;

    // Iterate through as many times as inputted originally
    for (int i = 0; i <= ops; i++) {
        flow = i * numThread;
        flow += thread;

        // Check wether even or odd for whether it is added or subtracted
        if (thread % 2 == 0) {
            thr->eq = -pow((inVal - 1), flow) / flow;
        } else {
            thr->eq = pow((inVal - 1), flow) / flow;
        }

        // Lock thread, add to result, and unlock thread
        pthread_mutex_lock(&lock);
        result += thr->eq;
        pthread_mutex_unlock(&lock);
    }

    pthread_exit(NULL);
}

// Main creates the threads, and joins them.
int main(int argc, char *argv[]) {
    char *err;
    // Grab the three values from the arguments & create needed vars.
    inVal = strtod(argv[1], &err);
    numThread = atoi(argv[2]);
    ops = atoi(argv[3]);
    thread_data_t threadD[numThread];
    pthread_t threadID[numThread];
    int i;
    
    // Check if Value is between 0 and 2, exit if not
    if (!(inVal < 2 && inVal > 0))
    {
        printf("Value must be between 0 and 2.\n");
        return EXIT_FAILURE;
    }

    // If no threads or no iterations exit
    if (numThread <= 0 || ops <= 0) {
        printf("Thread count and number of iterations must be at least 1.\n");
        return EXIT_FAILURE;
    }

    // Create Threads
    for (i = 0; i < numThread; i++) {
        int thread_create = 0;
        threadD[i].tID = i;

        thread_create = pthread_create(&threadID[i], NULL, threadMath, &threadD[i]);

        // If thread not created exit
        if (thread_create != 0) {
            printf("pthread_create error\n");
            return EXIT_FAILURE;
        }
    }

    // Join Threads
    for(i = 0; i < numThread; i++) {
        int *thread_retval;
        int join_retval;

        join_retval = pthread_join(threadID[i], (void**) (&thread_retval));

        // Check if not joined correctly
        if (join_retval != 0) {
            printf("Join error: %d.\n", join_retval);
            pthread_exit(NULL);
        }
    }

    pthread_mutex_destroy(&lock);

    // Print the result and the Math funtion
    printf("%.14f \n", result);
    printf("%.14f \n", log(inVal));
    pthread_exit(NULL);
    return 1;
}