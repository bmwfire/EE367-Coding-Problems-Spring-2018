/* Name: <Brandon Wong>
* Reads in a string of lowercase alphabets, and
* finds the longest substring of a single character.
*/
#include <stdio.h>
#include <stdlib.h>

#define MAXLENGTH 100000

/* 
 * Finds longest substring in 'str' with length 'length'
 *     The substring's starting index is 'first' and
 *     it's last index is 'last'.
 *     It returns the length of the substring.
 */
int strlength(char str[], int length, int *first, int *last);

int main(int argc, char *argv[])
{
if (argc != 2) {
	printf("Usage:  ./a.out  <data file>\n");
	return 0;
}

FILE *fp = fopen(argv[1], "r");
if (fp == NULL) {
	printf("Error in opening file: '%s'\n", argv[1]);
	return 0;
}
int length;
fscanf(fp, " %d ", &length);

if (length >= MAXLENGTH) {
	printf("Data is too large\n");
	return 0;
}

char *str = (char *)malloc(length*sizeof(char));
fgets(str, length+1, fp);

fclose(fp);
int first, last;
int n = strlength(str, length, &first, &last);

printf("String length = %d, first = %d, last = %d\n", n, first, last);

free(str);
}

int strlength(char str[], int length, int *first, int *last)
{
int best_first = 0;  /* Storage for the best string */
int best_last = 0;
int best_length = 1;

int curr_first = 0;  /* Keep track of the current string */
int symbol = str[0];
int symbol2 = str[1]; //Keep track of additional character

for (int i=0; i < length; i++) {
	if ((str[i] != symbol) || (str[i] != symbol2) || (i == length-1)) {
		if (i - curr_first + 1 > best_length) {
			best_first = curr_first;
			best_last = i-1;
			best_length = i - curr_first;
		}
	}
	if ((str[i] != symbol) && (str[i] != symbol2)) {  /* Start of new substring */
		symbol = str[i];
		symbol2 = str[i+1];
		curr_first = i;	
	}
}	

*first = best_first;
*last = best_last;

return best_length;
}


