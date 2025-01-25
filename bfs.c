#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_node 100
#define max_node_len 10

int findNodeIndex();
int selectStartIndex();
void bfs();

typedef struct {
    char name[max_node_len];
} Node;

typedef struct{
    char bfsList[max_node];
    int front;
    int next;
} bfsQueue;

int edges=0;

int main() {
    char count[4], type[11];
    int num, weight;

    FILE *fptr = fopen("graph.txt", "r");

    if (!fptr) {
        perror("FAILED");
        return EXIT_FAILURE;
    }

    fgets(count, sizeof(count), fptr);
    num = atoi(count); 

    int adjMatrix[max_node][max_node] = {0};
    Node nodes[max_node];

    for (int i = 0; i < num; i++) {
        fscanf(fptr, "%s", nodes[i].name); 
    }

    fscanf(fptr, "%s", type);
    int isDirected = (strcmp(type, "directed") == 0);

    char node1[max_node_len], node2[max_node_len];
    while (fscanf(fptr, "%s %s %d", node1, node2, &weight) == 3) {
        int index1 = findNodeIndex(nodes, num, node1);
        int index2 = findNodeIndex(nodes, num, node2);
	    edges++;
        adjMatrix[index1][index2] = weight;
        if (!isDirected) {
            adjMatrix[index2][index1] = weight; 
        }
    }

    fclose(fptr);

    int startIndex = selectStartIndex(adjMatrix, num);

    bfs(adjMatrix, nodes, num, startIndex, isDirected);

    return 0;
}

int findNodeIndex(Node nodes[], int numNodes, char* nodeName) {
    for (int i = 0; i < numNodes; i++) {
        if (strcmp(nodes[i].name, nodeName) == 0) {
            return i;
        }
    }
    return -1;
}

int selectStartIndex(int adjMatrix[max_node][max_node], int numNodes) {
    int maxConnections = -1;
    int startIndex = -1;

    for (int i = 0; i < numNodes; i++) {
        int connections = 0;
        for (int j = 0; j < numNodes; j++) {
            if (adjMatrix[i][j] != 0) {
                connections++;
            }
        }

        if (connections > maxConnections) {
            maxConnections = connections;
            startIndex = i;
        }
    }

    return startIndex;
}

void bfs(int adjMatrix[max_node][max_node], Node nodes[], int num, int startIndex, int isDirected) {
    
    int isVisited[max_node] = {0}; 
    bfsQueue queue = {{0}, 0, 0}; 
    int totalWeight = 0;

    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num; j++) {
            if (adjMatrix[i][j] != 0) {
                totalWeight += adjMatrix[i][j];
            }
        }
    }
    if (!isDirected) {
        totalWeight /= 2;
    }

    queue.bfsList[queue.next++] = startIndex;
    isVisited[startIndex] = 1;

    printf("BFS Traversal Path: ");
    while (queue.front < queue.next) {
        int current = queue.bfsList[queue.front++]; 
        printf("%s", nodes[current].name);

        
        if (queue.front <= edges) {
            printf(" -> ");
        }

        for (int i = 0; i < num; i++) {
            if (adjMatrix[current][i] != 0 && !isVisited[i]) {
                queue.bfsList[queue.next++] = i;
                isVisited[i] = 1;
            }
        }
    }

    printf("\nTotal Weight: %d\n", totalWeight);

    
    printf("Unreachable Nodes: ");
    int unreachable = 0;
    for (int i = 0; i < num; i++) {
        if (!isVisited[i]) {
            printf("%s ", nodes[i].name);
            unreachable = 1;
        }
    }
    if (!unreachable) {
        printf("None");
    }
    printf("\n");
}
