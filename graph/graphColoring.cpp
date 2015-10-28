/* Given an undirected graph and a number m, determine if the graph can be colored with at most m colors such that no two 
adjacent vertices of the graph are colored with same color. Here coloring of a graph means assignment of colors to all vertices.

Input:
1) A 2D array graph[V][V] where V is the number of vertices in graph and graph[V][V] is adjacency matrix representation 
of the graph. A value graph[i][j] is 1 if there is a direct edge from i to j, otherwise graph[i][j] is 0.
2) An integer m which is maximum number of colors that can be used.

Output:
An array color[V] that should have numbers from 1 to m. color[i] should represent the color assigned to the ith vertex. 
The code should also return false if the graph cannot be colored with m colors.

For reference on the definition of the graph m-coloring problem, see https://en.wikipedia.org/wiki/Graph_coloring.
For references on algorithms for solving this problem, see http://www.geeksforgeeks.org/backttracking-set-5-m-coloring-problem/.
*/


#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define V 4 // number of vertices in the graph: 0,...,V-1

void printColoring(vector<int> &coloring) {
    for (int i = 0; i < coloring.size(); i++) {
        cout << coloring[i] << "  ";
    }
    cout << endl;
}

bool validColoring(int G[][V], vector<int> &coloring, int u, int color) {
    for (int v = 0; v < V; v++) {
        if (G[u][v] && coloring[v] == color) {
            return false;
        }
    }
    return true;
}

bool graphColoringDFS(int G[][V], int m, vector<int> &coloring, int u) {
    // terminate condition
    if (u == V) { // alll nodes are colorerd
        return true;
    }
    // recurse on the next node of s
    for (int c = 1; c <= m; c++) {
        if (validColoring(G, coloring, u, c)) {
            coloring[u] = c;
            if (graphColoringDFS(G, m, coloring, u+1)) {
                return true;
            }
            coloring[u] = 0; // reset u's color back to the unset state: not necessary in this case
        }
    }
    return false;
}

bool graphColoring(int G[][V], int m) {
    // corner cases
    if (m < 1)  return false;
    if (m >= V)  return true;
    vector<int> coloring(V, 0); // 0 = not yet colored
    if (graphColoringDFS(G, m, coloring, 0)) {
        cout << "coloring exists: ";
        printColoring(coloring);
        return true;
    } else {
        return false;
    }
}

int main() {
	int graph[V][V] = {{0, 1, 1, 1},
        {1, 0, 1, 0},
        {1, 1, 0, 1},
        {1, 0, 1, 0},
    };
    int m = 2; // number of colors
    cout << graphColoring (graph, m) << endl;
	return 0;
}
