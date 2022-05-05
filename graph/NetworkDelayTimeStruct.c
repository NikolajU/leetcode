#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printTable(int** matrix, int len1, int len2){
    for (int i = 0; i < len1; i++)  {
        for( int y = 0; y < len2; y++) {
            printf("%d ", matrix[i][y]);
        }
        printf("\n");
    }
}

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)b - *(int*)a );
}

struct Node {
    unsigned char to;
    int cost;
};

void traverseX(struct Node** matrix, int* costsArray, int n, int y, unsigned char* connections) {
    for (int x=0; x < connections[y]; x++) {
        int costToNode = matrix[y][x].cost;
        unsigned char to = matrix[y][x].to;
        if (costToNode > -1) {
            int newCost = costsArray[y] + costToNode;
            int oldCost = costsArray[to];

            if (newCost < oldCost || oldCost == -1) {
                costsArray[to] = newCost;
                traverseX(matrix, costsArray, n, to, connections);
            }
        }
    }
}

int networkDelayTime(int** times, int timesSize, int* timesColSize, int n, int k){
    struct Node **matrix2;
    matrix2 = malloc(n * sizeof(*matrix2));
    int i;

    // loop through times and count how many connections each node has.
    unsigned char *connections = calloc(n, sizeof(unsigned char));
    for(i = 0; i < timesSize; i++) {
        connections[times[i][0]-1] += (unsigned char) 1;
    }

    // create an array for every node, that has the following properties:
    // matrix = [ [{ unsigned char to: 3, int cost: 43 }] ]
    for(i=0; i < n; i++) {
        matrix2[i] = malloc(connections[i] * sizeof(struct Node) ); // allocating space for Node structures.
    }

    connections = calloc(n, sizeof(unsigned char));
    for(i = 0; i < timesSize; i++) {
        struct Node node1;
        int from = times[i][0] -1;
        node1.to = times[i][1] -1;
        node1.cost = times[i][2];

        matrix2[from][connections[from]] = node1;
        connections[from] += (unsigned char) 1;
    }

    // initialize array with cost to go to node.
    int *costsArray = malloc(n * sizeof(int));
    memset(costsArray, -1, n * sizeof(int));
    costsArray[k-1] = 0;

    // start traversing the graph from node k-1 (k-1 because array starts counting from 0).
    traverseX(matrix2, costsArray, n, k-1, connections);

    qsort(costsArray, n, sizeof(int), cmpfunc);

    if (costsArray[n-1] == -1) return -1;
    return costsArray[0];
}

int main(){
    int arr1[3][3] = {{2,1,1}, {2,3,1}, {3,4,1}};

    int **times = malloc(3 * sizeof(*times));
    for (int i = 0; i < 3; i++) {
        times[i] = &arr1[i][0];
    }

    int timesColSize = 3;
    int* timesColSizeP = &timesColSize;

    int result1 = networkDelayTime(times, 3, timesColSizeP, 4, 2);
    printf("result1: %d %d\n\n", result1 == 2, result1);


    int arr4[] = {1,2,1};
    int **times2 = malloc(1 * sizeof(*times2));
    times2[0] = &arr4[0];

    int timesColSize2 = 3;
    int* timesColSizeP2 = &timesColSize2;

    int result2 = networkDelayTime(times2, 1, timesColSizeP2, 2, 2);
    printf("result2: %d %d\n", result2 == -1, result2);


    int timesColSize3 = 3;
    int* timesColSizeP3 = &timesColSize3;

    int arr5[20][3] = {{3,5,78},{2,1,1},{1,3,0},{4,3,59},{5,3,85},{5,2,22},{2,4,23},{1,4,43},{4,5,75},{5,1,15},{1,5,91},{4,1,16},{3,2,98},{3,4,22},{5,4,31},{1,2,0},{2,5,4},{4,2,51},{3,1,36},{2,3,59}};
    int **times3 = malloc(20 * sizeof(*times));
    for (int i = 0; i < 20; i++) {
        times3[i] = &arr5[i][0];
    }

    int result3 = networkDelayTime(times3, 20, timesColSizeP3, 5, 5);
    printf("result3: %d %d\n", result3 == 31, result3);

}