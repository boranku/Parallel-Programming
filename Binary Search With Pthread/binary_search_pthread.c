#include <stdbool.h>
#include <stdlib.h> 
#include <time.h>
#include <pthread.h>
#include <stdio.h>

#define MAX 2000000

int array[MAX] ;
int thread_num;
int key = 12;
bool found = false;
int part = 0;

void* binary_search(void* arg){

	int thread_id = part++;
	int mid;
	int low = thread_id * (MAX / thread_num);
	int high = (thread_id + 1) * (MAX / thread_num);
	printf("T%d: %d - %d\n",thread_id, low, high);

	while (low < high && !found) {

		mid = (high - low) / 2 + low;

		if (array[mid] == key) {
			found = true;
			break;
		}

		else if (array[mid] > key)
			high = mid - 1;
		else
			low = mid + 1;
	}
}

int compare (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}
int main(int argc, char* argv[]){
	int i, j;
	thread_num = strtol(argv[1], NULL, 10);
 	clock_t t;

	for (i=0;i<MAX;i++){
 		array[i]=rand()%8000;
		}
 	
	qsort(array, MAX, sizeof(int), compare);

	// for(i=0;i<4999;i++){
	// 	for(j=i*400;j<(i+1)*400;j++){
	// 		a[j] = i;
	// 	}
	// }

	pthread_t threads[thread_num];
	t = clock();
	for (int i = 0; i < thread_num; i++) pthread_create(&threads[i], NULL, binary_search, (void*)NULL);
	for (int i = 0; i < thread_num; i++) pthread_join(threads[i], NULL);
	t = clock() - t;
	if (found) printf("%d found.\n",key);
	else printf("%d not found.\n",key);

	double time_taken = ((double)t)/CLOCKS_PER_SEC;
	printf("Time taken: %f seconds \n", time_taken);

	return 0;
}

