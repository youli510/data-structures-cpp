#include <iostream>
#include <queue>
#include <cmath>

struct Node {
	int r, c;
	int g;
	int f;
	bool  operator>  (const Node& o)        const                { return f > o.f; }
//  返回值  重载   另一个Node(不可修改)    该函数不可修改自己       比较f
};
int heuristic(int r,int c,int gr,int gc) {
	return abs(r - gr) + abs(c - gc);
}			//曼哈顿距离(离终点的权重)
int aStar(const std::vector<std::vector<int>>& grid,
		int sr, int sc,		//起点
		int gr, int gc)		//终点
{
	int rows = grid.size(), cols = grid[0].size();
	const int INF = 1e9;
	// gScore 数组：记录到每一格的最短实际步数
	std::vector<std::vector<int>> gScore(rows,std::vector<int>(cols,INF));
	//优先队列（f小的先出）
	std::priority_queue<  Node,      std::vector<Node>,  std::greater<Node>> pq;
	//				    元素类型        底层容器          比较器
	gScore[sr][sc] = 0;
	pq.push({sr,sc,0,heuristic(sr,sc,gr,gc)});
	int dr[4] = {-1,1,0,0};
	int dc[4] = {0,0,-1,1};
	while (!pq.empty()) {
		Node cur = pq.top();
		pq.pop();
		if (cur.g > gScore[cur.r][cur.c]) continue;
		if (cur.r == gr && cur.c == gc)return cur.g;
		for (int k = 0; k < 4; k++) {
			int nr = cur.r + dr[k];
			int nc = cur.c + dc[k];
			if (nr < 0 || nr >= rows || nc < 0 || nc >= cols|| grid[nr][nc] == 1) continue;
			int newG = cur.g + 1;
			if (newG<gScore[nr][nc]) {
				gScore[nr][nc]=newG;
				int nf = newG + heuristic(nr,nc,gr,gc);
				pq.push({nr,nc,newG,nf});
			}
		}
	}
	return -1;
}

int main() {
	std::vector<std::vector<int>> g1 = {
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0}
	};
	std::cout << aStar(g1, 0, 0, 2, 2) << "\n";    // 期望 4
	std::vector<std::vector<int>> g2 = {
	{0, 1, 0, 0},
	{0, 1, 0, 0},
	{0, 1, 1, 0},
	{0, 0, 0, 0}
	};
	std::cout << aStar(g2, 0, 0, 0, 3) << "\n";    // 期望 9
	std::vector<std::vector<int>> g3 = {
	{0, 1, 0},
	{0, 1, 0},
	{0, 1, 0}
	};
	std::cout << aStar(g3, 0, 0, 0, 2) << "\n";    // 期望 -1
	return 0;
}