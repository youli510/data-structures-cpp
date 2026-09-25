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
	void insert(int pos, char ch) {
		text.insert(pos, 1, ch);
		undoStack.push(action{action::DELETE, pos, ch});
		while (!redoStack.empty()) {
			redoStack.pop();
		}
	}
	void remove(int pos) {
		char ch = text[pos];
		text.erase(pos,1);
		undoStack.push(action{action::INSERT,pos,ch});
		while (!redoStack.empty()) {
			redoStack.pop();
		}
	}
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
