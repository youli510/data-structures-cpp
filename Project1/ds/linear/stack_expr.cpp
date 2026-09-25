//栈表达式求值
#include <iostream>
#include <string>
#define MAXSIZE 100
using bit32 = int;
template <typename T>

class stack {
private:
	T* data;
	int top;
	int capacity;

public:
	stack(int cap = 100) :capacity(cap), top(-1) {
		data = new T[capacity];
	}
	~stack() {
		delete[]data;
	}
	stack(const stack&) = delete;
	stack& operator=(const stack&) = delete;

	bool empty() const {
		return top == -1;
	}

	bool full() const {
		return top >= capacity - 1;
	}

	bool push(const T &n) {
		if (full()) {
			std::cerr << "满了";
			return false;
		}
		data[++top] = n;
		return true;
	}

	bool pop(T &n){
		if (empty()) {
			std::cerr << "空的";
			return false;
		}
		n = data[top--];
		return true;
	}

	bool getTop(T &n) const{
		if (empty()) {
			std::cerr << "空的";
			return false;
		}
		n = data[top];
		return true;
	}

};
enum class Token {
	left_paren,right_paren,
	add,sub,mul,div,mod,
	eos,num
};
Token getToken(const std::string& expr, char& symbol, int& index) {
	using enum Token;
	if (index >= static_cast<int>(expr.size())) {
		symbol = '\0';
		return eos;
	}  
	//static_cast<int>(expr.size()) 把无符号的长度值显式转换为 int，
	//让比较发生在两个相同的有符号类型之间，避免编译器产生“有符号/无符号比较”的警告


	symbol = expr[index++];
	switch (symbol) {
		case '(': return left_paren;
		case')':return right_paren;
		case'+':return add;
		case'-':return sub;
		case'*':return mul;
		case'/':return div;
		case '%':return mod;
		default:return num;
	}
}
bit32 evaluatepostfix(const std::string &expr) {
	using enum Token;
	stack<int> st;
	char symbol;
	int index = 0;
	bit32 op1, op2, result;
	Token token = getToken(expr, symbol, index);
	while (token != eos) {
		if (token == num) {
			st.push(symbol - '0');
		}
		else {
			st.pop(op2);
			st.pop(op1);
			switch (token) {
				case add:st.push(op1 + op2); break;
				case sub:st.push(op1 - op2); break;
				case mul:st.push(op1 * op2); break;
				case div:st.push(op1 / op2); break;
				case mod:st.push(op1 % op2); break;
				default:
					std::cerr << "unknown";
					return 0;
			}
		}
		token = getToken(expr,symbol,index);
	}
	st.pop(result);
	return result;
}
void append(std::string &fix,Token op) {
	using enum Token;
	switch (op) {
	case add:fix += '+'; break;
	case sub:fix += '-'; break;
	case mul:fix += '*'; break;
	case div:fix += '/'; break;
	case mod:fix += '%'; break;
	default: break;
	}
}
std::string posfix(const std::string &infix) {
	using enum Token;
	std::string posfix;
	int in_stack[] = {0,19,12,12,13,13,13,0};
	int out_stack[] = {20,19,12,12,13,13,13,0};
	stack<Token> st;
	st.push(eos);
	char symbol;
	int index = 0;
	Token token = getToken(infix, symbol, index);
	while (token != eos) {
		if (token == num) { 
			posfix += symbol; 
		}
		else if (token == right_paren) {
			Token toptoken;
			st.pop(toptoken);
			while (toptoken != left_paren) {
				//st.pop(toptoken);
				append(posfix,toptoken);
				st.pop(toptoken);
			}
			//st.pop(toptoken);
		}
		else {
			Token toptoken;
			st.getTop(toptoken);
			while (in_stack[static_cast<int>(toptoken)]>=out_stack[static_cast<int>(token)]) {
				st.pop(toptoken);
				append(posfix,toptoken);
				st.getTop(toptoken);
			}
			st.push(token);
		}
		token = getToken(infix,symbol,index);
	}
	Token toptoken;
	st.pop(toptoken);
	while (toptoken!=eos) {
		append(posfix,toptoken);
		st.pop(toptoken);
	}
	return posfix;
}


int main() {
	std::string expr = "7/(9-2)*2";			//"82/2+56*-";
	bit32 result = evaluatepostfix(posfix(expr));
	std::cout << result;
	return 0;
}