#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define N 1000000
// #define thread_num 4
double thread_sums[64] = {0};
int thread_num;
int thread_no=0;//*******

void* pi_sum(void* rank){
	long my_rank = thread_no++;   //**********
	

    double my_sum = 0;
    double factor;
    long i;
    long start = my_rank * (N/thread_num);
    long end = (my_rank+1) * (N/thread_num);

    if(start%2 == 0) factor = 1.0;
    else factor = -1.0;

    for(i=start; i<end; i++){
        my_sum += factor/(2*i+1);
        factor = -factor;
    }
    thread_sums[my_rank] = my_sum;
    // printf("thread: %ld, sum: %.25lf\n" ,my_rank,my_sum);
    return NULL;
}

int main(int argc, char* argv[]){
    long i;
    double total_sum = 0;
    pthread_t* thread_handles;
    thread_num = strtol(argv[1], NULL, 10);
    thread_handles =(pthread_t*) malloc(thread_num*sizeof(pthread_t)); //*************
    clock_t start, end;
    double time;

    start = clock();
    for(i=0; i<thread_num;i++){
        pthread_create(&thread_handles[i], NULL, &pi_sum, NULL);//*************
    }
    for (i=0; i<thread_num; i++){
        pthread_join(thread_handles[i], NULL);
    }
    // free(thread_handles);
    end = clock();
    time = (double)(end-start)/CLOCKS_PER_SEC;
    for(i=0;i<thread_num;i++){
        total_sum += thread_sums[i];
    }
    printf("Pi Value: %.30lf\nThreads: %d\nTime: %lf ", total_sum*4, thread_num, time);

 
 
  return 0;
}