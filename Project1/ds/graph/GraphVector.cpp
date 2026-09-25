#include <iostream>
#include <vector>
#include <queue>
#include <stack>


class graph {
private:
	std::vector<std::vector<int>> adj;
	int V;
public:
	graph(int v) :V(v), adj(v) {}
	void addEdge(int u,int w) {
		adj[u].push_back(w);
		adj[w].push_back(u);
	}
	void printgraph() {
		for (int i = 0; i < V;i++) {
			std::cout<<i<<":";
			for (int v:adj[i]) {
				std::cout << v << " ";	// v 依次 = adj[i][0], adj[i][1], adj[i][2], ...

			}
			std::cout << "\n";
		}
	}
	void bfs(int start) {
		std::vector<bool> visit(V, false);
		std::queue<int> q;
		q.push(start);
		visit[start] = true;
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			std::cout << u << " ";
			for (int v:adj[u]) {
				if (!visit[v]) {
					visit[v] = true;
					q.push(v);
				}
			}
		}
		std::cout << "\n";
	}				//bfs(队列)
	void dfs(int u,std::vector<bool>& visit) {
		visit[u] = true;
		std::cout << u << " ";
		for (int v : adj[u]) {
			if (!visit[v]) {
				dfs(v, visit);
			}
		}
	}
	void dfsALL(int start) {
		std::vector<bool> visit(V,false);
		dfs(start,visit);
		std::cout << "\n";
	}				//递归dfs
	void dfsIteratuve(int start) {
		std::vector<bool> visit(V, false);
		std::stack<int> st;
		st.push(start);
		visit[start] = true;
		while (!st.empty()) {
			int u = st.top();
			st.pop();
			std::cout << u << " ";
			for (int v : adj[u]) {
				if (!visit[v]) {
					visit[v] = true;
					st.push(v);
				}
			}
		}
		std::cout << "\n";
	}
};					//迭代dfs(用栈)


int main() {
	graph g(4);
	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(3, 1);
	g.addEdge(2, 3);
	g.printgraph();
	g.bfs(0);
	g.dfsALL(0);
	g.dfsIteratuve(0);
	return 0;
}