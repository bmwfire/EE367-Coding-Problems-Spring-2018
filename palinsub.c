/* Name: <Brandon Wong>
 *
 * Function palinsub(char string[]) 
 * displays (on the console) the longest palindrome substring 
 * of string[].
 * (string1[] is terminated by the null char '\0'.)
 *
 * The current function lcs doesn't work -- it's incomplete.
 * Make it work, by applying either top-down (with memoization) or
 * bottom-up dynamic programming. 
 *
 * Your algorithm should run in a reasonable amount of time, 
 * even if the strings have length of 1000.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
 * palinsub(string)
 * displays the longest palindrome subsequence. 
 */
void palinsub(char * string);

int main(int argc, char *argv[])
{
if (argc!=2) {
	printf("Usage:  ./a.out <string>\n");
	return 0;
}
char * string = file_str(argv[1]);
int string_size = strlen(string);
if (string_size > MAXLENGTH) {
	printf("File '%s' is too large (> %d bytes)\n", argv[1], string_size);
	return 0;
}

printf("Longest palindrome subsequence of '%s'':\n", string);
palinsub(string);
}

void palinsub(char * string)
{
	int string_size = strlen(string);
	bool table[string_size][string_size];
	memset(table, 0, sizeof(table));

	//Case 1: All substrings of length 1 are palindromes
	int max_length = 1;
	for(int i = 0; i < string_size; i++)
		table[i][i] = true;

	//Case 2: Substring of length 2
	int start = 0;
	for(int i = 0; i < string_size-1; i++) {
		if(string[i] == string[i+1]) {
			table[i][i+1] = true;
			start = i;
			max_length = 2;
		}
	}

	//Case 3: Substring of lengths greater than 2
	for(int k = 3; k <= string_size; k++) {
		for(int i = 0; i < string_size-k+1; i++) {
			int j = i + k - 1;

			if(table[i+1][j-1] && string[i] == string[j]) {
				table[i][j] = true;

				if(k > max_length) {
					start = i;
					max_length = k;
				}
			}
		}
	}

	//Print result
	for(int i = start; i <= start + max_length-1; i++)
		printf("%c", string[i]);

	printf("\n");
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

