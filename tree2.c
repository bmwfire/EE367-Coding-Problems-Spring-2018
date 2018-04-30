/*
 * EE 367 Machine Problem
 *
 * Author:  Galen Sasaki
 * Completor:  Brandon Wong
 * Date:  Feb 5, 2018
 *
 * This program maintains a binary search tree that
 * can be manually changed by the user.  Here are
 * the commands:  
 *   - (q) Quit
 *   - (e) Insert an alphabet
 *   - (d) Delete an alphabet
 *   - (t) List the nodes in the tree and their children
 *   - (i) List the nodes in in-order
 *   - (p) List the nodes in post-order
 *
 * The commands 'd' and 'p' do not work.
 * Your task is to make them work by implementing two functions:
 *   - deleteNode();
 *   - listPostOrder();
 *  
 *  You can compile by "gcc tree.c"
 */

#include <stdio.h>
#include <stdlib.h>

struct node {
  char key;
  struct node *left, *right; 
};

/* Creates and destroys nodes and trees */
struct node * createNode(char key);  
void destroyNode(struct node * node);
void destroyTree(struct node * root);

/* insertNode and deleteNode will insert and delete nodes.  */
struct node * insertNode(struct node *node, char key);
struct node * deleteNode(struct node *node, char key);

//Helper function for deleteNode
struct node * minValue(struct node *node);

/* List the nodes in in-order and post-order */
void listInOrder(struct node * node);
void listPostOrder(struct node * node);

/* Displays a tree. */
void displayTree(struct node * root);

int main()
{

struct node * root = NULL;  /* Initialilze tree to empty */

printf("Welcome to the binary search tree!\n\n");

char key;
char cmd;
while(1) {
   printf("Commands \n");
   printf("     (q) Quit\n");
   printf("     (i) Insert a lower-case alphabet \n");
   printf("     (x) Delete a lower-case alphabet \n");
   printf("     (d) Display tree \n");
   printf("     (n) List nodes in-order\n");
   printf("     (p) List nodes post-order\n");

   printf("Enter command: ");
   cmd = getchar();
   while (getchar()!='\n');

   switch(cmd) {
	case 'q': /* Quit */
		destroyTree(root);
		return 0;
	case 'i': /* Insert key */ 
		printf("Enter char to insert ('a' - 'z'): ");
		key = getchar();
   		while (getchar()!='\n');
		root = insertNode(root, key);
		break;
	case 'x': /* Delete key */
		printf("Enter char to delete ('a' - 'z'): ");
		key = getchar();
   		while (getchar()!='\n');
		root = deleteNode(root, key);
		break;
	case 'd': /* Display tree */
		displayTree(root);
		break;
	case 'n': /* Display nodes in-order */
		printf("In-order list:");
		listInOrder(root);
		printf("\n");
		break;
	case 'p': /* Display nodes post-order */
		printf("Post-order list:");
		listPostOrder(root);
		printf("\n");
		break;
	default:
		printf("Invalid command, try again\n");
   }
}
}

struct node * createNode(char key)
{
struct node *p = (struct node *) malloc(sizeof(struct node));
p->left = NULL;
p->right = NULL;
p->key = key;
return p;
}

void destroyNode(struct node * node)
{
free(node);
}

void destroyTree(struct node * root)
{
if (root != NULL) {
	destroyTree(root->left);
	destroyTree(root->right);
	destroyNode(root);
}
}

/* 
 * Fix this  
 */
struct node * deleteNode(struct node * node, char key) 
{
	//Base Case
	if(node == NULL) return node;

	//Left subtree traversal
	if(key < node->key) 
		node->left = deleteNode(node->left, key);
	
	//Right subtree traversal
	else if(key > node->key)
		node->right = deleteNode(node->right, key);
	
	//Found node to delete
	else {
		//Case 1a: node has one child on right
		if(node->left == NULL) {
			struct node *temp = node->right;
			free(node);
			return temp;
		}
		
		//Case 1b: node has one child on left
		else if(node->right == NULL) {
			struct node *temp = node->left;
			free(node);
			return temp;
		}
		
		//Case 2: node has two children so use right child as replacement
		struct node *temp = minValue(node->right);
		node->key = temp->key;
		node->right = deleteNode(node->right, temp->key);
	}
	return node;
}

//Helper function for deleteNode
struct node * minValue(struct node *node) 
{
	struct node *current = node;
	
	while(current->left != NULL)
		current = current->left;

	return current;
}

void listInOrder(struct node * node)
{
if (node != NULL) {
	listInOrder(node->left);
	printf(" %c ",node->key);
	listInOrder(node->right);
}
}

/*
 * Fix tnis 
 */
void listPostOrder(struct node * node)
{
	if(node != NULL) {
		listPostOrder(node->left);
		listPostOrder(node->right);
		printf(" %c ", node->key);
	}
}

struct node * insertNode(struct node * node, char key)
{
if (node == NULL) {
	return createNode(key);
}
if (node->key == key) {  /* Do nothing since key is already there */
	return node;
}
else if (key < node->key) {
	node->left = insertNode(node->left, key);
	return node;
}
else {
	node->right = insertNode(node->right, key);
	return node;
}
}

void displayTree(struct node * node)
{
if (node == NULL) {
	return;
}
printf("Node %c: ", node->key);
printf("Children[ ");
if (node->left == NULL) {
	printf("/");
}
else {
	printf("%c", node->left->key);
}
printf(", ");
if (node->right == NULL) {
	printf("/");
}
else {
	printf("%c", node->right->key);
}
printf(" ]\n");
displayTree(node->left);
displayTree(node->right);
}

