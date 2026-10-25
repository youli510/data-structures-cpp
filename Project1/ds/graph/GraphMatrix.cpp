#include <iostream>
#include <vector>
#include <queue>


class graphMatrix {
private:
	std::vector<std::vector<int>> matrix;
	int V;
public:
	graphMatrix(int v) :V(v), matrix(v, std::vector<int>(v, 0)) {}
	// 加无向边：matrix[u][w] 与 matrix[w][u] 同时置 1（矩阵对称）
	void addEdge(int u,int w) {
		matrix[u][w] = 1;
		matrix[w][u] = 1;
	}
	// 打印 n×n 邻接矩阵（1 表示有边，0 表示无边）
	void printMatrix() {
		for (int i = 0; i < V;i++) {
			for (int j: matrix[i]) {
				std::cout << j << " ";
			}
			std::cout << "\n";
		}
	}
	// 矩阵版 BFS：扫描 u 的整行，用 matrix[u][v]==1 判断是否有边
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