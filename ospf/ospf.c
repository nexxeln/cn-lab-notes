#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_ROUTERS 20
#define INF INT_MAX

// Function to find the vertex with minimum distance
int minDistance(int dist[], int visited[], int V)
{
    int min = INF, min_index = -1;

    for (int v = 0; v < V; v++)
    {
        if (!visited[v] && dist[v] <= min)
        {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// Function to print the path from source to j
void printPath(int parent[], int j)
{
    if (parent[j] == -1)
        return;

    printPath(parent, parent[j]);
    printf(" -> %d", j);
}

// Function to implement Dijkstra's algorithm
void dijkstra(int graph[MAX_ROUTERS][MAX_ROUTERS], int src, int V)
{
    int dist[MAX_ROUTERS];    // Distance array
    int visited[MAX_ROUTERS]; // Visited array
    int parent[MAX_ROUTERS];  // Parent array to store shortest path tree

    // Initialize arrays
    for (int i = 0; i < V; i++)
    {
        dist[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++)
    {
        int u = minDistance(dist, visited, V);
        visited[u] = 1;

        for (int v = 0; v < V; v++)
        {
            if (!visited[v] && graph[u][v] &&
                dist[u] != INF &&
                dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    // Print paths and costs for each destination
    printf("\nShortest paths from router %d:\n", src);
    printf("--------------------------------\n");
    for (int i = 0; i < V; i++)
    {
        printf("Destination %d:\n", i);
        if (i == src)
        {
            printf("  Path: %d\n", src);
            printf("  Cost: 0\n");
        }
        else
        {
            if (dist[i] != INF)
            {
                printf("  Path: %d", src);
                printPath(parent, i);
                printf("\n  Cost: %d\n", dist[i]);
            }
            else
            {
                printf("  No path available\n");
                printf("  Cost: INFINITY\n");
            }
        }
        printf("\n");
    }
}

int main()
{
    int V;                                     // Number of routers
    int graph[MAX_ROUTERS][MAX_ROUTERS] = {0}; // Adjacency matrix
    int source;

    printf("Enter the no of routers : ");
    scanf("%d", &V);

    printf("Enter the cost matrix values :\n");

    // Input the cost matrix in the specified order
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            printf("%d->%d:", i, j);
            scanf("%d", &graph[i][j]);
        }
    }

    printf("Enter the source router:");
    scanf("%d", &source);

    // Calculate and print shortest paths
    dijkstra(graph, source, V);
    printf("\n");

    return 0;
}
