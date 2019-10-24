#include<stdio.h>
#include<stdlib.h>
__global__ void multiply(int *a,int *b,int *c,int n,int m)
{

int row = blockIdx.y*blockDim.y+threadIdx.y;
int col = blockIdx.x*blockDim.x+threadIdx.x;
int result =0;
if(row<n&&col<m)
{
for(int i =0;i<n;i++)
{
result+=a[row*n+i]*b[i*m+col];
}
c[row*m+col]=result;
}

}
int main()
{

int *a,*b,*c;
int n=3;
int m=3;
int size = n*sizeof(int);
a = (int*)malloc(size*size);
b = (int*)malloc(size*size);
c = (int*)malloc(size*size);

for(int i=0;i<n;i++)
{
for(int j=0;j<n;j++)
{
*(a+i*n+j)=i*n+(j+1);
*(b+i*n+j)=i*n+(j+1);
}
}

printf("\\nThe Matrix a is:\\n");
for(int i=0;i<n;i++)
{
for(int j=0;j<n;j++)
{
printf("%d\t",*(a+i*n+j));
}
printf("\\n");
}

printf("\\nThe Matrix b is:\\n");
for(int i=0;i<n;i++)
{
for(int j=0;j<n;j++)
{
printf("%d\t",*(b+i*n+j));
}


printf("\\n");
}

int *d_a,*d_b,*d_c;
cudaMalloc(&d_a,size*size);

cudaMalloc(&d_b,size*size);

cudaMalloc(&d_c,size*size);
cudaMemcpy(d_a,a,size*size,cudaMemcpyHostToDevice);

cudaMemcpy(d_b,b,size*size,cudaMemcpyHostToDevice);
dim3 dimGrid(1,1);
dim3 dimBlock(16,16);
multiply<<<dimGrid,dimBlock>>>(d_a,d_b,d_c,n,m);

cudaMemcpy(c,d_c,size*size,cudaMemcpyDeviceToHost);

printf("\\nThe Matrix c is:\\n");
for(int i=0;i<n;i++)
{
for(int j=0;j<n;j++)
{
printf("%d\t",*(c+i*n+j));
}


printf("\\n");
}

cudaFree(d_a);

cudaFree(d_b);

cudaFree(d_c);





return 0;

}
