/*
 * Name: <Brandon Wong>
 *
 * Function subseq(char target[], char key[]) returns
 * the number of occurrences that the string 'key' is a 
 * substring of 'target'. 
 * (Note that both strings are terminated by the null char '\0'.)
 * Note that substrings are distinct if they have distinct locations.
 *
 * As an example, suppose target = 'rabbbit' and key = 'rabbit'.
 * Then subseq will return 3.
 *
 * The current function subseq doesn't work -- it's incomplete.
 * Make it work.  This may require adding new functions.
 * Use the top-down approach where you implement a recursive
 * algorithm with memoization.  Your algorithm should run in
 * a reasonable amount of time, even if the strings have
 * length of 1000.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLENGTH 1000

/*
 * Open a file 'str_file'.  Then read it and put it in a 
 * dynamically allocated buffer.  Return the pointer to the
 * buffer.
 */
char * file_str(char * str_file);

/* 
 * Create and destroy an row x ccl int array
 *    Note that after: int ** a = create_array(r, c)
 *    then you can access the array using a[i][j] 
 */
int ** create_array(int row, int col);
void destroy_array(int ** arr, int row);

/* 
 * subseq(target, key) returns the number of times string 'key' is
 * a substring of string 'target'.  The substring does not have to
 * be contiguous.  Also substrings at different locations are considered
 * distinct.
 */
int subseq(char * target, char * key);

int main(int argc, char *argv[])
{
if (argc!=3) {
	printf("Usage:  ./a.out <target string> <key string>\n");
	return 0;
}
char * target = file_str(argv[1]);
int target_size = strlen(target);
if (target_size > MAXLENGTH) {
	printf("File '%s' is too large (> %d bytes)\n", argv[1], target_size);
	return 0;
}
char * key = file_str(argv[2]);
int key_size = strlen(key);
if (key_size > MAXLENGTH) {
	printf("File '%s' is too large (> %d bytes)\n", argv[2], key_size);
	return 0;
}

printf("Number of occurences of '%s' in '%s': %d\n",key, target,
		subseq(target,key));

}

int subseq(char * target, char * key)
{
	int t_size = strlen(target);
	int k_size = strlen(key);
	int array[k_size + 1][t_size + 1];

	//Size of target must be larger than size of key
	if(k_size > t_size) return 0;

	//Initialize 2D array to hold values
	for(int i = 1; i <= k_size; i++) 
		array[i][0] = 0;

	for(int j = 0; j <= t_size; j++)
		array[0][j] = 1;

	//Reuse calculate values in 2D array
	for(int i = 1; i <= k_size; i++)
		for(int j = 1; j <= t_size; j++)
		{
			//If the value in the key is not equal to the value in the target
			if(key[i - 1] != target[j - 1])
				
				//Then store the same key value and the previous target value in the array
				array[i][j] = array[i][j - 1];
			else
				//Store current and previous key value in the array
				array[i][j] = array[i][j - 1] + array[i - 1][j - 1];
		}

	return array[k_size][t_size];
}

int ** create_array(int row, int col)
{
int ** arr = (int **) malloc(row*sizeof(int *));
for (int i=0; i<row; i++) {
	arr[i] = (int *) malloc(col*sizeof(int));
}
return arr;
}

void destroy_array(int ** arr, int row)
{
for (int i=0; i<row; i++) {
	free(arr[i]);
}
free(arr);
}

char * file_str(char * str_file) 
{
FILE * fp = fopen(str_file, "r");
if (fp == NULL) {
	printf("File '%s' didn't open\n", str_file);
	return 0;
}
fseek(fp, 0, SEEK_END);
long size = ftell(fp);
rewind(fp);
char *buf = (char *) malloc(sizeof(char)*(size+1));
if (buf==NULL) {
	printf("Couldn't allocate memory for file '%s'\n", str_file);
	return 0;
}
int result = fread(buf,1,size,fp);
if (result!=size) {
	printf("Didn't read the entire file '%s'\n", str_file);
	return 0;
}
size--;
buf[size] = '\0';
printf(">>>String in file '%s':\n",str_file);
printf("'%s'\n", buf);
printf("Length = %ld\n",size);
fclose(fp);
return buf;
}

