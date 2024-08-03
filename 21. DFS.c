#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define the structure for a graph node
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// Define the structure for a graph
typedef struct Graph {
    int numVertices;
    Node** adjLists;
    bool* visited;
} Graph;

// Function to create a new adjacency list node
Node* createNode(int vertex) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with a given number of vertices
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;

    graph->adjLists = (Node**)malloc(vertices * sizeof(Node*));
    graph->visited = (bool*)malloc(vertices * sizeof(bool));

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = false;
    }

    return graph;
}

// Function to add an edge to the graph
void addEdge(Graph* graph, int src, int dest) {
    // Add edge from src to dest
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // Add edge from dest to src (for undirected graph)
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// Function to perform DFS traversal from a given vertex
void dfs(Graph* graph, int vertex) {
    Node* adjList = graph->adjLists[vertex];
    Node* temp = adjList;

    // Mark the current node as visited and print it
    graph->visited[vertex] = true;
    printf("Visited %d\n", vertex);

    // Recur for all the vertices adjacent to this vertex
    while (temp != NULL) {
        int connectedVertex = temp->vertex;

        if (!graph->visited[connectedVertex]) {
            dfs(graph, connectedVertex);
        }
        temp = temp->next;
    }
}

// Function to free the memory allocated for the graph
void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        Node* temp;
        while (graph->adjLists[i] != NULL) {
            temp = graph->adjLists[i];
            graph->adjLists[i] = graph->adjLists[i]->next;
            free(temp);
        }
    }
    free(graph->adjLists);
    free(graph->visited);
    free(graph);
}

// Main function to test the DFS implementation
int main() {
    // Create a graph
    int vertices = 6;
    Graph* graph = createGraph(vertices);

    // Add edges to the graph
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 5);
    addEdge(graph, 4, 5);

    // Perform DFS traversal
    printf("Depth-First Search (starting from vertex 0):\n");
    dfs(graph, 0);

    // Free the allocated memory
    freeGraph(graph);

    return 0;
}
