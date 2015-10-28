Given a connected graph, detetermine if it is a bipartite graph. 

For the definition of a bipartite graph, see https://en.wikipedia.org/wiki/Bipartite_graph
For more reference on the general m-coloring problem, see http://www.geeksforgeeks.org/backttracking-set-5-m-coloring-problem/
For additional problems related to bipartite graph, see e.g. http://www.geeksforgeeks.org/maximum-bipartite-matching/

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <climits>
#include <queue>
#include <unordered_map>

using namespace std;

// check if a connected undirected graph is bipartite or not

struct GraphNode {
    int label;
    vector<GraphNode *> neighbors;
    GraphNode(int x) : label(x) {};
};

bool isBipartite(GraphNode *s) {
    // corner case
    unordered_map<GraphNode *, int> coloring;
    coloring[s] = 0; // assign a starting color for node
    queue<GraphNode *> q;
    q.push(s);
    // assign 2 colors to graph nodes via BFS
    while (!q.empty()) {
        GraphNode *c = q.front();
        q.pop();
        int curColor = coloring[c];
        vector<GraphNode *> nNodes = c->neighbors;
        for (int i = 0; i < nNodes.size(); i++) {
            GraphNode *nc = nNodes[i];
            if (coloring.find(nc) == coloring.end()) { // not yet assigned a color
                coloring[nc] = (curColor + 1) % 2;
                // push nc into q
                q.push(nc);
            } else if (coloring[nc] == coloring[c]) {
                return false;
            }
        }
    }
    return true;
}


// adjacency matrix representation of graph

#define V 4 // V = number of vertices

bool isBipartite2(int G[][V], int s) {
    vector<int> coloring(V, -1); // -1 = not yet colored
    coloring[s] = 1;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int c = q.front();
        q.pop();
        int curColor = coloring[c];
        for (int nc = 0; nc < V; nc++) {
            if (G[c][nc] && coloring[nc] == -1) {
                coloring[nc] = (curColor + 1) % 2;
                q.push(nc);
            } else if (G[c][nc] && coloring[nc] == curColor) {
                return false;
            }
        }
    }
    return true;
}

int main() {
	 int G[][V] = {{0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0}
    };
 
    isBipartite2(G, 0) ? cout << "Yes" : cout << "No";
	return 0;
}
