/*Name:  <Brandon Wong> 

 * Mergesort is implemented in function 'mergesort', which is
 * implemented using recursion. 
 * Change mergesort so that it is implemented iteratively and
 * still has O(n log n) time complexity.
 */

#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h>

#define MAXLENGTH 1000 

/* Initializes array a[] wih random values */
void init(int a[], int length); 

/* Displays array a[] */
void display(int a[], int length); 

/* 
 * Merges sorted subarrays 
 *    (a[last], a[last+1],..., a[midpt-1))
 *    (a[midpt], a[midpt+1], ..., a[last-1])
 * into a sorted array.
 */
void merge(int a[], int first, int midpt, int last);

/*
 * Change the following recursive implementation of mergesort 
 * into an iterative implementation.
 */
void mergesorted(int a[], int first, int last);        /* Merge sort */
//Note that Xcode's standard library has mergesort.
//There were conflicting syntax hence the name change of function mergesort to mergesorted.

void mergesort_iter(int a[], int n); //Iterative Implementation of Merge Sort

int min(int x, int y); //Utility function used in mergesort_iter

int main(int argc, char* argv[]) 
{
if (argc != 2){
	printf("Usage:  ./a.out <length of array>\n");
	return 0;
}
int length = atoi(argv[1]);
if (length >= MAXLENGTH) {
	printf("Length %d must be less than %d\n",length,MAXLENGTH);
	return 0;
}

//printf("length of array = %d\n", length);

/* Initialize and display the array */
int a[MAXLENGTH];       /* Array of data */
init(a, length);    
printf("\nInitial array:\n");
display(a, length);    

/* Sort and display the array */
//mergesorted(a, 0, length);
mergesort_iter(a, length);
printf("\nSorted array:\n");
display(a, length);    
}

/* 
 * Mergesort:  Sorts the values in a[first], a[first+1],..., a[last-1] 
 * This is a recursive implementation.
 *
 * Change this into an iterative implementation  
 * that has O(n log n) time complexity.
 */

int min(int x, int y) //needed to build a min function for mergesort_iter 
{
	if(x < y) return x;
	else return y;
}

void mergesort_iter(int a[], int n) 
{
	for(int size = 1; size < n; size = 2*size) 
	{
		for(int left = 0; left < n; left += 2*size) 
		{	
			int middle = left + size; //set a middle index
			int right = min(left + 2*size, n);
			merge(a, left, middle, right);
		}
	}
}

void mergesorted(int a[], int first, int last)
{
int midpt;

midpt = (first+last)/2;

if (first < midpt-1) mergesorted(a, first, midpt);
if (midpt < last-1) mergesorted(a, midpt, last);
merge(a, first, midpt, last);
}


/*
 * Merges two sorted subarrays (sorted in increasing order)  
 *    (a[first], ..., a[midpt-1]) and
 *    (a[midpt],..., a[last-1]) 
 *    into
 *    subarray temp[first],..., temp[last-1] in increasing order.
 *    
 *    Then it copies temp[first],..., temp[last-1] back into
 *    a[first],..., a[last-1].
 */
void merge(int a[], int first, int midpt, int last)
{
static int temp[MAXLENGTH];

int leftptr;   /* Pointers used in array a[ ] */
int rightptr;
int k;         /* pointer used in array temp[ ] */
int delay;

leftptr = first;
rightptr = midpt; 

/* Merge values in the two arrays of a[] into temp[] */
for(k=first; k<last; k++) {
   if (leftptr >= midpt) temp[k] = a[rightptr++];
   else if (rightptr >= last) temp[k] = a[leftptr++];
   else if (a[leftptr] < a[rightptr]) temp[k] = a[leftptr++];
   else if (a[leftptr] >= a[rightptr]) temp[k] = a[rightptr++];
   else printf("There's a bug \n"); /* We shouldn't get here */
}

/* Copy temp[] back to a[] */
for(k=first; k<last; k++) a[k] = temp[k];
}


/* Initializes array a[] with random values. */
void init(int a[], int length)
{
int temp; 
int k;

for (int i=0; i<length; i++) a[i] = i; /* Initialize with distinct values */

/* Randomly shuffle the values */
srand48(1);     /*  Seed the pseudorandom number generator */
for (int i=0; i<length; i++) {
   k = lrand48()%(length-i);
   temp = a[k];
   a[k] = a[length-i-1];
   a[length-i-1] = temp; 
}
}

/* Displays the values in the array a[] */
void display(int a[], int length)
{
for (int i=0; i<length; i++) {
   printf(" %d ", a[i]);
   if ((i+1)%10 == 0) printf("\n");
}
printf("\n");
}


