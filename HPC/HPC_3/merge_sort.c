#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void merge(int *x, int N, int * tmp) 
{
	int i = 0;
	int j = N/2;
	int t = 0;

   	while(i<N/2 && j<N) 
   	{
      		if(x[i] < x[j]) 
      		{
         		tmp[t] = x[i];
         		t++;
         		i++;
      		}
      		else 
      		{
         		tmp[t] = x[j];
         		t++;
         		j++;
      		}
   	}
   	while (i<N/2) 
   	{
      		tmp[t] = x[i];
      		t++;
      		i++;
   	}
      	while(j<N) 
      	{
        	tmp[t] = x[j];
        	t++;
        	j++;
   	}
   	memcpy(x, tmp, N*sizeof(int));
}
void mergesort(int *x, int N, int *tmp)
{
	if(N < 2) 
   		return;

   	#pragma omp task firstprivate (x, N, tmp)
   		mergesort(x, N/2, tmp);

   	#pragma omp task firstprivate (x, N, tmp)
   		mergesort(x+(N/2), N-(N/2), tmp);
 
   	#pragma omp taskwait

   	merge(x, N, tmp);
}
int main()
{	
	time_t t;
	srand((unsigned) time(&t));	
	
	int N;
	
	printf("Enter the number of elements to be sorted: ");
	scanf("%d", &N);

	int *x;
        x = (int*)malloc(N*sizeof(int));
        
        int *tmp;
        tmp = (int*)malloc(N*sizeof(int));
        
        for(int i = 0; i < N; i++)
        {
        	x[i] = rand()%N;
        }
            
        printf("Initial array is: \n");
        for(int i = 0; i < N; i++)
       	{
        	printf("%d ", x[i]);
        }
        printf("\n");
        
   	#pragma omp parallel
   	{
      		#pragma omp single
      			mergesort(x, N, tmp);
   	}
   	
   	printf("Sorted Array is: \n");
        for(int i = 0; i < N; i++)
        	printf("%d ", x[i]);
       	
       	printf("\n");

    	return 0;
}	
