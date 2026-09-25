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
	void insert(bit32 val) {
		root = insert(root, val);
	}
	enum TraversalType { PRE, IN, POST };
	enum Mode { RECURSIVE, ITERATIVE };
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
	void preorder(Treenode*node)const {
		if (node == nullptr) return;
		std::cout << node->data << " ";
		preorder(node->lchild);
		preorder(node->rchild);
	}				//前序遍历(递归)
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
	void inorder(Treenode* node)const {
		if (node == nullptr) return;
		inorder(node->lchild);
		std::cout << node->data << " ";
		inorder(node->rchild);
	}				//中序遍历(递归)
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
	void postorder(Treenode* node)const {
		if (node == nullptr) return;
		postorder(node->lchild);
		postorder(node->rchild);
		std::cout << node->data << " ";
	}				//后序遍历(递归)
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
	void destroyTree(Treenode*node) {
		if (node == nullptr)return;
		destroyTree(node->lchild);
		destroyTree(node->rchild);
		delete node;
	}
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