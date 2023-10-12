#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<stdint.h>
using namespace std;

double compute_time(struct timespec start, struct timespec end)
{
double diffSec;
diffSec = (double)(end.tv_sec - start.tv_sec) + ((double)(end.tv_nsec - start.tv_nsec) / (double)1000000000);
return diffSec;
}

void quick_sort(int q[], int l, int r)
{
    if (l >= r) return;

    int i = l - 1, j = r + 1, x = q[l + r >> 1];
    while (i < j)
    {
        do i ++ ; while (q[i] < x);
        do j -- ; while (q[j] > x);
        if (i < j) swap(q[i], q[j]);
    }
    quick_sort(q, l, j), quick_sort(q, j + 1, r);
}

void merge_sort(int q[], int l, int r)
{
    if (l >= r) return;

    int mid = l + r >> 1;
    int tmp[r+1];
    merge_sort(q, l, mid);
    merge_sort(q, mid + 1, r);

    int k = 0, i = l, j = mid + 1;
    while (i <= mid && j <= r)
        if (q[i] <= q[j])tmp[k ++ ] = q[i ++ ];
        else tmp[k ++ ] = q[j ++ ];

    while (i <= mid) tmp[k ++ ] = q[i ++ ];
    while (j <= r) tmp[k ++ ] = q[j ++ ];

    for (i = l, j = 0; i <= r; i ++, j ++ ) q[i] = tmp[j];
}


void bubble_sort(int q[], int l)
{
    for (int i = 0; i < l - 1; i++)
	{
            for (int j = 0; j < l - i - 1; j++)
	        {
                    if (q[j] > q[j + 1]) 
			{
                            int temp = q[j];
                            q[j] = q[j + 1];
                            q[j + 1] = temp;
                        }
                 }
         }
}

void insertion_sort(int q[], int l)
{
	for (int j=1; j<l; j++)
	{
		int temp = q[j];
		int i = j-1;
		while (i>=0 && q[i]>temp)
		{
			q[i+1] = q[i];
			i--;
		}
		q[i+1] = temp;
	}
}

int main(){
double t1,t2,t3,t4;
double s1=0,s2=0,s3=0,s4=0;
for(int ii=0;ii<100;ii++)
{
int i,j;
int b=10000,a=1;
int c[b],d[b],e[b],f[b];
srand((unsigned)time(NULL));
for(i=0;i<b;i++){
    c[i] = (rand() % (b-a+1))+ a;
    d[i] = c[i];
    e[i] = c[i];
    f[i] = c[i];
}
struct timespec start, end;

clock_gettime(CLOCK_MONOTONIC, &start);
quick_sort(c,0,b-1);
clock_gettime(CLOCK_MONOTONIC, &end);
s1+=compute_time(start, end);

clock_gettime(CLOCK_MONOTONIC, &start);
merge_sort(d,0,b-1);
clock_gettime(CLOCK_MONOTONIC, &end);
s2+=compute_time(start, end);

clock_gettime(CLOCK_MONOTONIC, &start);
bubble_sort(e,b);
clock_gettime(CLOCK_MONOTONIC, &end);
s3+=compute_time(start, end);

clock_gettime(CLOCK_MONOTONIC, &start);
insertion_sort(f,b);
clock_gettime(CLOCK_MONOTONIC, &end);
s4+=compute_time(start, end);
}
t1 = s1/100;
t2 = s2/100;
t3 = s3/100;
t4 = s4/100;
printf("快速排序运行时间：");
printf("%.4lf ms \n", t1*1000);
printf("归并排序运行时间：");
printf("%.4lf ms \n", t2*1000);
printf("冒泡排序运行时间："); 
printf("%.4lf ms \n", t3*1000);
printf("插入排序运行时间："); 
printf("%.4lf ms \n", t4*1000);
return 0;
}
