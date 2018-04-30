/* Name: <Brandon Wong>
 *
 * Bellman Ford algorithm
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX_ARRAY_SIZE 100
#define INFINITY 100000

struct adjlist_node {
	int node;
	int weight;
	struct adjlist_node * next;
};

void bf(struct adjlist_node ** adjlist, int num_nodes);

int main(int argc, char * argv[])
{
if (argc != 2) {
	printf("Usage:  ./a.out <file name>\n");
	return 0;
}

FILE * fp = fopen(argv[1],"r");
if (fp == NULL) {
	printf("File '%s' didn't open\n", argv[1]);
	return 0;
}
int num_nodes;
fscanf(fp, "%d", &num_nodes);

/* Create adjacency list */
struct adjlist_node ** adjlist = (struct adjlist_node **) 
	malloc(sizeof(struct adjlist_node *)*num_nodes);
for (int i=0; i<num_nodes; i++) {
	adjlist[i] = NULL;
}	

int num_links;
fscanf(fp, "%d", &num_links);
int end_node0, end_node1, weight;
struct adjlist_node * newnode;
for (int i=0; i<num_links; i++) {
	fscanf(fp, "%d %d %d", &end_node0, &end_node1, &weight);

	newnode = (struct adjlist_node *) malloc(sizeof(struct adjlist_node *));
	newnode->weight = weight;
	newnode->node = end_node1;
	newnode->next = adjlist[end_node0];
	adjlist[end_node0] = newnode;

	newnode = (struct adjlist_node *) malloc(sizeof(struct adjlist_node *));
	newnode->weight = weight;
	newnode->node = end_node0;
	newnode->next = adjlist[end_node1];	
	adjlist[end_node1] = newnode;
}

/* Display the adjacency list */
printf("Adjacency list:\n");
for (int i=0; i<num_nodes; i++) {
	printf("Node %d:", i);
	for (struct adjlist_node * current = adjlist[i]; current != NULL;
			current = current->next) {
		printf("-> [node=%d wt=%d]", current->node, current->weight);
	}
	printf("\n");
}

bf(adjlist, num_nodes);

fclose(fp);
return 0;
}

/*
 * The following function 'bf' doesn't work.  It should compute
 * shortest paths from node 0 to all other nodes, and dispslay
 * the paths.
 * The input adjlist is the adjacency list, and num_nodes is the
 * number of nodes.
 */
void bf(struct adjlist_node ** adjlist, int num_nodes)
{
	printf("Shortest paths:\n");
	
	int dist[MAX_ARRAY_SIZE];
	int parent[MAX_ARRAY_SIZE];
	int result[num_nodes][num_nodes];

	//Initialize all distances to infinity
	for (int i = 0; i < num_nodes; i++) {
		dist[i] = INFINITY;
		parent[i] = -1;
	} 

	//Initialize all values to a number
	dist[0] = parent[0] = 0;

	//Update dist table for shortest path
	for (int i = 1; i < num_nodes; i++) {
		for (struct adjlist_node * curr = adjlist[i]; curr != NULL; curr = curr->next) {
			
			//If the distance is infinity
			if(dist[i] == INFINITY) {
				dist[i] = curr->weight + dist[curr->node];
				parent[i] = curr->node;
			}
		
			//If the distance is large but not infinity
			else if(dist[i] > curr->weight + dist[curr->node]) {
				parent[i] = curr->node;
				dist[i] = curr->weight + dist[curr->node];
			}
		}
	}

	//Set the source node of graph
	for (int i = 0; i < num_nodes; i++) {
		for (int j = 0; j < num_nodes; j++) {
			if(j == 0) 
				result[i][j] = 0;
			else
				result[i][j] = -1;
		}
	}

	//Traverse adjacency list for shortest path
	for (int i = 1; i < num_nodes; i++) {
		int check = 1;
		int conductor = parent[i];

		//Traverse back to the source node
		while (conductor != 0) {
			result[i][check] = conductor;
			conductor = parent[conductor];
			check++;
		}
		result[i][check] = i;
	}

	//Print results
	for (int i = 1; i < num_nodes; i++) {
		printf("0 ");
		for (int j = 1; j < num_nodes; j++) {
			if(result[i][j] != -1)
				printf("-> %d ", result[i][j]);
		}
		printf("\n");
	}
}

