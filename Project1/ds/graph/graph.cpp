#include <iostream>
#include <queue>
#include <stack>

struct Edge {
	int dest;
	Edge* next;
};

class graph {
private:
	int V;
	Edge** heads;
public:
	graph(int v):V(v) {
		heads = new Edge * [v];
		for (int i = 0; i <v; i++) {
			heads[i] = nullptr;
		}
	}
	//~graph();
	void addEdge(int u, int w) {
		Edge* node1 = new Edge(w,heads[u]);
		Edge* node2 = new Edge(u,heads[w]);
		heads[u] = node1;
		heads[w] = node2;
	};
	void printgraph() {
		for (int i = 0; i <= V - 1;i++) {
			Edge* p = heads[i];
			std::cout << i << ":";
			while (p) {
				std::cout << p->dest << " ";
				p = p->next;
			}
			std::cout << "\n";
		}
	}
	void bfs(int star) {
		bool* visit = new bool[V];
		for (int i = 0; i < V; i++) visit[i] = false;
		std::queue<int> q;
		q.push(star);
		visit[star] = true;
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			std::cout << u << " ";
			Edge* p = heads[u];
			while (p) {
				int v = p->dest;
				if (!visit[v]) {
					visit[v] = true;
					q.push(v);
				}
				p = p->next;
			}
		}
		std::cout << "\n";
		delete[] visit;
	}
	void dfs(int u,bool* visit) {
		visit[u] = true;
		std::cout << u << " ";
		Edge* p = heads[u];
		while (p) {
			int v = p->dest;
			if (!visit[v]) {
				dfs(v, visit);
			}
			p = p->next;
		}
	}
	void dfsALL(int start) {
		bool* visit = new bool[V];
		for (int i = 0; i < V; i++) visit[i] = false;
		dfs(start, visit);
		std::cout << "\n";
		delete[] visit;
	}
	void dfsIterative(int start) {
		bool* visit = new bool[V];
		for (int i = 0; i < V; i++) visit[i] = false;
		std::stack<int> st;
		st.push(start);
		visit[start] = true;
		while (!st.empty()) {
			int u = st.top();
			st.pop();
			std::cout << u << " ";
			Edge* p = heads[u];
			while (p) {
				int v = p->dest;
				if (!visit[v]) {
					visit[v] = true;
					st.push(v);
				}
				p = p->next;
			}
		}
		std::cout << "\n";
		delete[] visit;
	}
};




int main() {
	graph g(4);
	g.addEdge(0,1);
	g.addEdge(0,2);
	g.addEdge(3,1);
	g.addEdge(2,3);
	g.printgraph();
	g.bfs(0);
	g.dfsALL(0);
	g.dfsIterative(0);
	return 0;
}