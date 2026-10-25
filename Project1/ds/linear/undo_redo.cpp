//撤回恢复
#include <iostream>
#include <stack>


class editor {
private:
	struct action {
		enum Type { INSERT, DELETE } type;
		int position;
		char value;
	};
	std::stack<action> undoStack;
	std::stack<action> redoStack;
	std::string text;
public:
	std::string gettext() {
		return text;
	}
	// 插入字符；把对应的「撤销动作 = 删除」压入 undo，并清空 redo
	void insert(int pos, char ch) {
        text.insert(pos, 1, ch);
		undoStack.push(action{action::DELETE, pos, ch});
		while (!redoStack.empty()) {
			redoStack.pop();
		}
	}
	// 删除字符；把对应的「撤销动作 = 插入」压入 undo，并清空 redo
	void remove(int pos) {
		char ch = text[pos];
		text.erase(pos,1);
		undoStack.push(action{action::INSERT,pos,ch});
		while (!redoStack.empty()) {
			redoStack.pop();
		}
	}
	// 撤销：从 undo 弹一个动作执行，并把正向动作压入 redo
	void undo() {
		if (undoStack.empty()) return;
		action act = undoStack.top();
		undoStack.pop();
		if (act.type==action::DELETE) {
			text.erase(act.position,1);
			redoStack.push(action{ action::INSERT,act.position,act.value });
		}
		else {
			text.insert(act.position,1,act.value);
			redoStack.push(action{ action::DELETE,act.position,act.value });
		}
	}
	// 重做：从 redo 弹一个动作执行，并把反向动作压回 undo
	void redo() {
		if (redoStack.empty()) return;
		action act = redoStack.top();
		redoStack.pop();
		if (act.type == action::DELETE) {
			text.erase(act.position, 1);
			undoStack.push(action{ action::INSERT,act.position,act.value });
		}
		else {
			text.insert(act.position, 1, act.value);
			undoStack.push(action{ action::DELETE,act.position,act.value });
		}
	}
	// 公共逻辑：从 from 栈取动作执行，再把反向动作压入 to 栈
	void moveaction(std::stack<action>&from,std::stack<action>&to) {
		if (from.empty()) return;
		action act = from.top();
		from.pop();
		if (act.type==action::DELETE) {
			text.erase(act.position, 1);
			to.push(action{ action::INSERT,act.position,act.value });
		}
		else {
			text.insert(act.position, 1, act.value);
			to.push(action{ action::DELETE,act.position,act.value });
		}
	}
};

int main() {
	editor st;
	st.insert(0,'a');
	st.insert(1, 'b');
	st.insert(2, 'c');
	std::cout << st.gettext() << "\n";
	st.remove(1);
	std::cout << st.gettext()<<"\n";
	st.undo();
	std::cout << st.gettext() << "\n";
	st.undo();
	std::cout << st.gettext() << "\n";
	st.redo();
	std::cout << st.gettext() << "\n";
	st.redo();
	std::cout << st.gettext() << "\n";
	return 0;
}
