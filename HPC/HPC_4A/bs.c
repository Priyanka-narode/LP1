#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define send_data_tag 2001
#define return_data_tag 2002
#define N 1024

int array2[4096];
int arr[4096];

int cmpfunc(const void* a, const void* b)
{
	return (*(int*)a - *(int*)b);
}
int binarySearch(int arr[], int x , int l, int r) 
{ 
	while(r >= l) 
   	{ 
        	int mid = (l + r)/2; 
        	
        	if(arr[mid] == x)  
            		return mid; 
        	if(arr[mid] < x)
			l = mid+1; 
        	else
			r = mid-1;
   	} 
 	return -1; 
}
int removeDuplicates(int* arr, int n) 
{  
	if (n==0 || n==1) 
        	return n; 
  
    	int temp[n]; 
    	int j = 0; 
    	
    	for(int i=0; i<n-1; i++)
    	{
        	if(arr[i] != arr[i+1]) 
            		temp[j++] = arr[i]; 
        }
        
    	temp[j++] = arr[n-1]; 
    	
    	for(int i=0; i<j; i++) 
        	arr[i] = temp[i]; 
  
    	return j; 
} 
int main(int argc,char** argv)
{
	int ierr, my_id, num_procs, num_elements_to_receive, avg_elements_per_process, start_row, end_row;
	
    	int isFound, key;
    	
    	MPI_Status status;
    	
	double start, finish;

    	ierr = MPI_Init(&argc, &argv); 
	start = MPI_Wtime();

    	ierr = MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
    	ierr = MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    	if(my_id == 0)
    	{
    		printf("Enter the key to be searched: \n");
    		scanf("%d", &key);
    		printf("\n");
    		
		srand(0);

		for(int i=0; i<N; i++)
		{
			arr[i] = rand()%15000;
		}		      		
		
		qsort(arr, N, sizeof(int), cmpfunc);
		
		int new_N = removeDuplicates(arr, N);
		
		printf("Size of Original Array: %d\n", N);
		printf("Size of New Array = %d\n\n", new_N);

    		avg_elements_per_process = new_N / num_procs;
		printf("Average Elements per process = %d\n\n", avg_elements_per_process);
		
        	for(int id=1; id<num_procs; id++)
        	{
            		start_row = (id)*avg_elements_per_process;
            		end_row = start_row+avg_elements_per_process-1;

            		if(end_row>N)
                		end_row = N;
		
            		ierr = MPI_Send(&avg_elements_per_process, 1, MPI_INT, id, send_data_tag, MPI_COMM_WORLD);
            		ierr = MPI_Send(&arr[start_row], avg_elements_per_process, MPI_INT, id, send_data_tag, MPI_COMM_WORLD);
			ierr = MPI_Send(&key, 1, MPI_INT, id, send_data_tag, MPI_COMM_WORLD);
        	}
		
		int index, sol_id;
		
        	index = binarySearch(arr, key, 0, avg_elements_per_process-1);
            		
            	if(index != -1)
            	{
            		isFound = index;
            		sol_id = 0;
            	}
		
        	for(int id=1; id<num_procs; id++)
        	{
            		ierr = MPI_Recv(&index, 1, MPI_INT, MPI_ANY_SOURCE, return_data_tag, MPI_COMM_WORLD, &status);
            		
            		if(index != -1)
            		{
            			isFound = index + (id)*avg_elements_per_process;
            			sol_id = id;
            		}
		}
		
		if(isFound >= 0)
		{ 		      		
            		printf("Element found at index = %d\n", isFound);
            		printf("Found by Processor Number = %d\n\n", sol_id);
            	}
            	else
            		printf("Does NOT Exist!!");
            		
		finish = MPI_Wtime();
		
		printf("\nExecution time = %f seconds\n", (finish-start));
    	}
    	else
    	{
    		ierr = MPI_Recv(&num_elements_to_receive, 1, MPI_INT, 0, send_data_tag, MPI_COMM_WORLD, &status);
        	ierr = MPI_Recv(&array2, num_elements_to_receive, MPI_INT, 0, send_data_tag, MPI_COMM_WORLD, &status);
		ierr = MPI_Recv(&key, 1, MPI_INT, 0, send_data_tag, MPI_COMM_WORLD, &status);

		isFound = binarySearch(array2, key, 0, num_elements_to_receive);

        	ierr = MPI_Send(&isFound, 1, MPI_INT, 0, return_data_tag, MPI_COMM_WORLD);
    	}
 	
    	ierr = MPI_Finalize();
}
