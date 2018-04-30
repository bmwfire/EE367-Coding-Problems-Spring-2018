/* Name:  <Brandon Wong>
 
 * Creates a linked list and then rotates it
 * Usage:  ./a.out N K
 *    where N is the number of nodes in the linked list
 *    and K is the amount to rotate to the right.
 *
 * The initial linked list is
 *
 * head-> 0 -> 1 -> ... -> N-1 -> NULL
 *
 * If we rotate by K=3, the linked list becomes
 *
 * head-> N-3 -> N-2 -> N-1 -> 0 -> 1 ... -> N-4 -> NULL
 *
 * Function 'rotate' does the rotation, but it doesn't work
 * Make changes so that it works. 
 */

#include <stdio.h>
#include <stdlib.h>

struct node {
	int key;
	struct node * next;
};

/* Create a linked list node */
struct node * create_node(int key);

/* Destroy a linked list node */
void destroy_node(struct node * p);

/* Create an initial linked list with 'length' nodes */
struct node * create_list(int length);

/* Destroy linked list */
void destroy_list(struct node* head);

/* Display the linked list */
void display_list(struct node * head);

/* Rotate right by k */
struct node* rotate(struct node* head, int k)
{
	if(k == 0) return head;

	struct node *tail;
	struct node *p;
	int length = 0;
	tail = p = head;

	//Find the tail and count nodes
	while(tail->next != NULL) {
		tail = tail->next;
		length++;
	}

	//Accommodate if k > number of nodes
	k = k % (length+1);
	
	//Create a circular list
	tail->next = head;

	//Find the kth node
	for(int i = 0; i < length-k; i++) 
		p = p->next;

	head = p->next;
	p->next = NULL;
	return head;
}

int main(int argc, char * argv[])
{

if (argc!=3) {
	printf("Usage: ./a.out <length> <shift amount>\n");
	return 0;
}

int length = atoi(argv[1]);
int shift = atoi(argv[2]);
if (shift >= length) {
	printf("Shift amount %d  must be smaller than length %d\n",\
			shift, length);
	return 0;
}

struct node* head = create_list(length);
printf("Initial linked list:\n");
display_list(head);

printf("Rotated linked list:\n");
head = rotate(head, shift);
display_list(head);

destroy_list(head);
return 0;
}

/* Create a linked list node */
struct node * create_node(int key)
{
struct node * p = (struct node *) malloc(sizeof(struct node));
p->key = key;
p->next = NULL;
return p;
}

/* Destroy a linked list node */
void destroy_node(struct node * p)
{
free(p);
}

/* Create an initial linked list with 'length' nodes */
struct node * create_list(int length)
{
srand48(100);

struct node* p = create_node(lrand48()%(10*length));
struct node* head = p;
struct node* tail = p;

for (int i=1; i<length; i++){
	p = create_node(lrand48()%(10*length));
	tail->next = p;
	tail = p;
}
return head;
}

/* Destroy linked list */
void destroy_list(struct node* head)
{
struct node* p = head;;
struct node* prev = p;
while (p!=NULL) {
	p = p->next;
	destroy_node(prev);
	prev = p;
}	
return;
}

/* Display the linked list */
void display_list(struct node * head)
{
printf("List: ");
for (struct node* p=head; p!=NULL; p=p->next) {
	printf("-> %d ", p->key);
}
printf("\n");
}


