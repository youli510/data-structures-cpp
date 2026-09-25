#include <iostream>
#include <vector>
#include <queue>


class graphMatrix {
private:
	std::vector<std::vector<int>> matrix;
	int V;
public:
	graphMatrix(int v) :V(v), matrix(v, std::vector<int>(v, 0)) {}
	void addEdge(int u,int w) {
		matrix[u][w] = 1;
		matrix[w][u] = 1;
	}
	void printMatrix() {
		for (int i = 0; i < V;i++) {
			for (int j: matrix[i]) {
				std::cout << j << " ";
			}
			std::cout << "\n";
		}
	}
	void bfs(int start) {
		std::vector<bool> visit(V,false);
		std::queue<int> q;
		q.push(start);
		visit[start] = true;
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			std::cout << u << " ";
			for (int v = 0;v<V; v++) {
				if (matrix[u][v] == 1 && !visit[v]) {
					q.push(v);
					visit[v] = true;
				}
			}
		}
		std::cout << "\n";
	}
};



int main() {
	graphMatrix g(4);
	g.addEdge(1, 0);
	g.addEdge(2, 0);
	g.addEdge(1, 3);
	g.addEdge(2, 3);
	g.printMatrix();
	g.bfs(0);
	return 0;
}