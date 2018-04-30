/* Name: <Brandon Wong> 
 *
 * Function lcs(char string1[], char string2[]) 
 * displays (on the console) the longest common substring (LCS)
 * of the two strings.
 * (Note that both string1[] and string2[] are 
 * terminated by the null char '\0'.)
 *
 * The current function lcs doesn't work -- it's incomplete.
 * Make it work, by applying top-down approach of dynamic programming
 * with memoization.
 *
 * Your algorithm should run in a reasonable amount of time, 
 * even if the strings have length of 1000.
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
 * lcs(string1, string2)
 * displays the longest common substring of string1 and string2. 
 */
void lcs(char * string1, char * string2);

int main(int argc, char *argv[])
{
if (argc!=3) {
	printf("Usage:  ./a.out <string1> <string2>\n");
	return 0;
}
char * string1 = file_str(argv[1]);
int string1_size = strlen(string1);
if (string1_size > MAXLENGTH) {
	printf("File '%s' is too large (> %d bytes)\n", argv[1], string1_size);
	return 0;
}
char * string2 = file_str(argv[2]);
int string2_size = strlen(string2);
if (string2_size > MAXLENGTH) {
	printf("File '%s' is too large (> %d bytes)\n", argv[2], string2_size);
	return 0;
}

printf("LCS of '%s' in '%s':\n", string1, string2);
lcs(string1,string2);
}

void lcs(char * string1, char * string2)
{
	int string1_size = strlen(string1);
	int string2_size = strlen(string2);
	int length = 0;
	int row, col;

	//Create a table to store lengths of lcs
	int table[string1_size+1][string2_size+1];

	//Traverse and store values
	for(int i = 0; i <= string1_size; i++) {
		for(int j = 0; j <= string2_size; j++) {
			if(i == 0 || j == 0) table[i][j] = 0;
			else if(string1[i-1] == string2[j-1]) {
				table[i][j] = table[i-1][j-1] + 1;
				
				if(length < table[i][j]) {
					length = table[i][j];
					row = i;
					col = j;
				}
			}
			else table[i][j] = 0;
		}
	}

	//Base Check
	if(length == 0) {
		printf("There is no common substring\n");
		return;
	}

	//Allocate space on the heap for LCS
	char * result = (char*)malloc((length+1) * sizeof(char));
	for(int k = 0; table[row][col] != 0; k++) {
		result[k] = string1[row-1];
		row -= 1;
		col -= 1;
	}

	//Print LCS
	for(int p = length; p >= 0; p--)
		printf("%c", result[p]);

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

