//括号匹配
#include <stack>
#include <string>
#include <iostream>

bool parenmatch(const std::string&s) {
	std::stack<char> st;
	for (char c : s) {
		if (c == '(' || c == '{' || c == '[')
			st.push(c);
		else if (c == ')' || c == '}' || c == ']'){
			if (st.empty()) return false;
			char n = st.top();
			st.pop();
			if (c==')' && n != '(') return false;
			if (c == '}' && n != '{') return false;
			if (c == ']' && n != '[') return false;
		}
	}
	return st.empty();
}

int main() {
	using namespace std;
	cout << parenmatch("()")<<"\n";
	cout<<parenmatch("({[]})")<<"\n";
	cout<<parenmatch("({[})")<<"\n";
	cout<<parenmatch("(")<<"\n";
	cout<<parenmatch(")")<<"\n";
	cout<<parenmatch("abc")<<"\n";
	return 0;
}