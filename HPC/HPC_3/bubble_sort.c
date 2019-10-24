#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	srand(0);
	
        int N;
        
        printf("Enter the number of elements to be sorted: ");
        scanf("%d", &N);
        
        int *x;
        x = (int*)malloc(N*sizeof(int));
        
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
        	
	int flag = 1;
	int nr = 0;
	int temp;
	while(flag)
	{
		#pragma omp parallel private(temp)
		{
			nr++;
            		flag = 0;
            		#pragma omp for reduction(+:flag)
            		for(int i = 0; i < N-1; i = i + 2)
            		{
                    		if(x[i] > x[i+1] )
                    		{
                            		temp = x[i];
                            		x[i] = x[i+1];
                            		x[i+1] = temp;
                            		++flag;
                    		}
            		}
            		#pragma omp for reduction(+:flag)
            		for(int i = 1; i < N-1; i = i + 2)
            		{
                    		if( x[i] > x[i+1] )
                    		{
                            		temp = x[i];
                            		x[i] = x[i+1];
                            		x[i+1] = temp;
                            		++flag;
                    		}
            		}
    		}
    	}
    	
    	printf("Sorted Array is: \n");
        for(int i = 0; i < N; i++)
        	printf("%d ", x[i]);
       	
       	printf("\n");

    	return 0;
}
