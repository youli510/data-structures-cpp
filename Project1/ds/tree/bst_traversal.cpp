//二叉树遍历
#include <iostream>
#include <string>
#include <stack>

using bit32=char;
class tunk {
private:
	struct Treenode {
		bit32 data;
		Treenode* lchild;
		Treenode* rchild;
		Treenode(bit32 val = 0) : data(val), lchild(nullptr), rchild(nullptr) {}
	};
	Treenode* root;
public:
	tunk(std::string&seq) :root(nullptr) {
		int index = 0;
		root = creatTree(seq,index);
	}
	tunk() :root(nullptr) {}
	~tunk() {
		destroyTree(root);
	}
	// 插入一个值（保持二叉搜索树性质）
	void insert(bit32 val) {
		root = insert(root, val);
	}
	enum TraversalType { PRE, IN, POST };
	enum Mode { RECURSIVE, ITERATIVE };
	// 统一入口：按「遍历方式 × 递归/迭代」两种维度分发
	void traverse(TraversalType type,Mode mode) {
		if (mode==ITERATIVE) {
			switch (type) {
			case PRE:  preorderIterative();  break;
			case IN:   inorderIterative();   break;
			case POST: postorderIterative(); break;
			}
		}
		else {
			switch (type) {
			case PRE:  preorder(root);  break;
			case IN:   inorder(root);   break;
			case POST: postorder(root); break;
			}
		}
	}
	

private:
	// 递归插入并返回该子树的根
	Treenode* insert(Treenode* node,bit32 val) {
		if (node==nullptr) {
			return new Treenode(val);
		}
		if (val < node->data) {
			node->lchild = insert(node->lchild,val);
		}
		else  {
			node->rchild = insert(node->rchild,val);
		}
		return node;
	}
	// 递归前序：根 → 左 → 右
	void preorder(Treenode*node)const {
		if (node == nullptr) return;
		std::cout << node->data << " ";
		preorder(node->lchild);
		preorder(node->rchild);
	}				//前序遍历(递归)
	// 迭代前序：用栈，先 push 右再 push 左（保证左孩子先出栈）
	void preorderIterative()const {
		if (!root) return;
		std::stack<Treenode*> st;
		st.push(root);
		while (!st.empty()) {
			Treenode* node = st.top();
			st.pop();
			std::cout << node->data << " ";
			if (node->rchild) st.push(node->rchild);
			if (node->lchild) st.push(node->lchild);
		}
		std::cout << std::endl;
	}				//前序遍历(迭代)
	// 递归中序：左 → 根 → 右（BST 上是升序）
	void inorder(Treenode* node)const {
		if (node == nullptr) return;
		inorder(node->lchild);
		std::cout << node->data << " ";
		inorder(node->rchild);
	}				//中序遍历(递归)
	// 迭代中序：一路向左压栈，弹出访问后再转向右子树
	void inorderIterative() {
		if (!root) return;
		std::stack<Treenode*> st;
		Treenode* cur = root;
		while (cur || !st.empty()) {
			while (cur) {
				st.push(cur);
				cur = cur ->lchild;
			}
			cur = st.top();
			st.pop();
			std::cout << cur->data << " ";
			cur = cur->rchild;
		}
	}			//中序遍历(迭代)
	// 递归后序：左 → 右 → 根
	void postorder(Treenode* node)const {
		if (node == nullptr) return;
		postorder(node->lchild);
		postorder(node->rchild);
		std::cout << node->data << " ";
	}				//后序遍历(递归)
	// 迭代后序：双栈法（stack1 生成「根右左」，stack2 反序弹出即后序）
	void postorderIterative() {
		if (!root) return;
		std::stack<Treenode*> A;
		std::stack<Treenode*> B;
		A.push(root);
		Treenode* node;
		while (!A.empty()) {
			node = A.top();
			A.pop();
			B.push(node);
			if (node->lchild) A.push(node->lchild);
			if (node->rchild)A.push(node->rchild);
		}
		while (!B.empty()) {
			node = B.top();
			B.pop();
			std::cout << node->data << " ";
		}
		std::cout << std::endl;
	}			//后序遍历(迭代)
	// 递归释放整棵树的所有节点
	void destroyTree(Treenode*node) {
		if (node == nullptr)return;
		destroyTree(node->lchild);
		destroyTree(node->rchild);
		delete node;
	}
	// 按「根-右-左」顺序的前序串建树（字符 # 表示空节点）
	Treenode* creatTree(std::string& pre, int& index) {
		if (index >= pre.length())return nullptr;
		char ch = pre[index++];
		if (ch == '#')return nullptr;
		Treenode* node = new Treenode(ch);
		node->rchild = creatTree(pre,index);
		node->lchild = creatTree(pre,index);
		return node;
	}
};
int main() {
	std::string seq = "ABD##E##C##";
	tunk tk(seq);
	std::cout << "递归前序: "; tk.traverse(tunk::PRE, tunk::RECURSIVE);
	std::cout << "迭代前序: "; tk.traverse(tunk::PRE, tunk::ITERATIVE);
	std::cout << "递归中序："; tk.traverse(tunk::IN, tunk::RECURSIVE);
	std::cout << "迭代中序: "; tk.traverse(tunk::IN, tunk::ITERATIVE);
	std::cout << "递归后序："; tk.traverse(tunk::POST, tunk::RECURSIVE);
	std::cout << "迭代后序："; tk.traverse(tunk::POST, tunk::ITERATIVE);
	return 0;
}