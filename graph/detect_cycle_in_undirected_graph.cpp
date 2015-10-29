/* Given an undirected graph, check if there is a cycle in the graph. 

We do a DFS traversal of the given graph. For every visited vertex ‘v’, if there is an adjacent ‘u’ such that u is already 
visited and u is not parent of v, then there is a cycle in graph. If we don’t find such an adjacent for any vertex, we say that 
there is no cycle. 

The assumption of this approach is that there are no parallel edges between any two vertices.
*/

#include <iostream>
#include <vector>
#include <list>

using namespace std;

class UndirectedGraph {
public:
    UndirectedGraph(int numEdge) {
        V = numEdge;
        adj = new list<int>[V]; // array of V lists
    }
    
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    bool isCyclic();
    
private:
    int V; // number of vertices
    // list supports constant time insertion and deletion anywhere within the sequence
    // can iterate in both directions
    // reference: http://www.cplusplus.com/reference/list/list/
    list<int> *adj; 
    bool isCyclicDFS(int u, vector<bool> &visited, int parent);
};

bool UndirectedGraph::isCyclic() {
    vector<bool> visited(V, false);
    for (int u = 0; u < V; u++) {
        if (!visited[u]) {
            if (isCyclicDFS(u, visited, -1))
                return true;
        }
    }
    return false;
}

bool UndirectedGraph::isCyclicDFS(int u, vector<bool> &visited, int parent) {
    cout << "curNode = " << u << endl;
    // mark current node as visited
    visited[u] = true;
    list<int>::iterator it;
    // recurse on the neighboring nodes of u
    for (it = adj[u].begin(); it != adj[u].end(); it++) {
        int nu = *it;
        if (!visited[nu]) {
            cout << nu << " is not visited yet" << endl;
            if (isCyclicDFS(nu, visited, u))
                return true;
        } else if (nu != parent) { // nu is visited but not parent
            return true;
        }
    }
    return false;
}

int main() {
	UndirectedGraph g1(5);
    g1.addEdge(1, 0);
    g1.addEdge(0, 2);
    g1.addEdge(2, 0);
    g1.addEdge(0, 3);
    g1.addEdge(3, 4);
    g1.isCyclic()? cout << "Graph contains cycle\n":
                   cout << "Graph doesn't contain cycle\n";
	return 0;
}
