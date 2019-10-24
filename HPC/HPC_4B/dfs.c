#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 4096

void printInorder(int* arr, int start, int end)
{
	if(start > end) 
    		return; 
    		 
  	printInorder(arr, start*2 + 1, end); 
  
  	printf("%d\t", arr[start]); 
  
  	printInorder(arr, start*2 + 2, end); 
}
void buildTree(int* arr, int start, int end, int* tree, int k, int offset)
{
	if(start<=end && k<=N-1)
	{
		int mid = (end+start+1)/2;
	
		tree[k] = mid+offset;
	
		buildTree(arr, start, mid-1, tree, k*2+1, offset);
		buildTree(arr, mid+1, end, tree, k*2+2, offset);
	}
}
int main(int argc, char const *argv[])
{
	int arr[N];
	int tree[N];
	int children = 4;
	int store[children][N];
	
	clock_t cpu_start = clock();
	
	for(int turns=1; turns<=children; turns++)
	{
		int offset = (turns-1)*N;
	
		buildTree(arr, 0, N, tree, 0, offset);
	
		printInorder(tree, 0, N-1);
	}
	
	clock_t cpu_finish = clock();
	
	printf("\nTime elapsed in traversing is = %lf milliseconds\n", (cpu_finish - cpu_start));

	return 0;
}
