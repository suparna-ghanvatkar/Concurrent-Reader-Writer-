#include<stdio.h>
#include <time.h>
#include <unistd.h>
#include <omp.h>

int main()
{
	int i=0,NumberofReaderThread=4,NumberofWriterThread=5;
	omp_lock_t writelock;
	int global_var=0;
	omp_init_lock(&writelock);
	printf("\nEnter number of Readers thread(MAX 10)");
 	scanf("%d",&NumberofReaderThread); 
 	printf("\nEnter number of Writers thread(MAX 10)");
 	scanf("%d",&NumberofWriterThread);
 	int tid=0;
 	int val;
	#pragma omp parallel
	#pragma omp for

 	for(i=0;i<NumberofReaderThread+NumberofWriterThread;i++)
 	{
 		int tid=omp_get_thread_num();
 		val=rand()%20;
 		if(i<NumberofReaderThread)
 			sleep(val);
 		if(i<NumberofReaderThread)
 		{
 			printf("Reader thread\n");
 			while(1)
 			{
				if(omp_test_lock(&writelock)) {
					omp_unset_lock(&writelock);
					printf("Value read is:%d\n",global_var);
					break;
				} 			
 			}
 		}
 		else {
 			printf("Writer thread\n");
 			while(1)
 			{
 				printf("%d writer trying for lock",i-NumberofReaderThread);
				if(omp_test_lock(&writelock)) {
					global_var++;
					printf("Value incremented, lock held by writer %d\n",i-NumberofReaderThread);
					sleep(0.1);
					omp_unset_lock(&writelock);
					break;
				} 			
 			}
 		}
 	}
 	omp_destroy_lock(&writelock);
 	return 0;
 }
