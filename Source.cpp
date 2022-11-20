#include <iostream>
#include <string>
#include <memory>

using namespace std;
using val = double;


class Node {
public:
	void add_left(shared_ptr<Node> ptr) {
		left = ptr;
	}
	void add_right(shared_ptr<Node> ptr) {
		right = ptr;
	}
	Node() :left(nullptr), right(nullptr) {};
	Node(shared_ptr<Node> l, shared_ptr<Node> r) : left(l), right(r) {};
	shared_ptr<Node> left, right;
	virtual val evaluate() = 0;
};

class Const : public Node {
public:
	Const() : value(0) {}
	Const(val v) : value(v) {}
	Const(val v, shared_ptr<Node> l, shared_ptr<Node> r) : Node(l, r), value(v) {}
	val value;
	val evaluate() override {
		return value;
	}

};

class Var : public Node {
private:
	val value;
	string name;
public:
	Var(string name) : value(0), name(name) {};
	Var(string name, val value) : value(value), name(name) {};
	Var(string name, val value, shared_ptr<Node> l, shared_ptr<Node> r) : Node(left, right), value(value), name(name) {};
	val evaluate() override {
		return value;
	}
};

class Op : public Node {
public:
	Op(char c) : sign(c) {

	}
	Op(char c, shared_ptr<Node> l, shared_ptr<Node> r) : sign(c), Node(l,r) {

	}
	char sign;
	val evaluate() override {
		if (sign == '+') {
			return left->evaluate() + right->evaluate();
		} else if (sign == '-') {
			return left->evaluate() - right->evaluate();
		}
		else if (sign == '*') {
			return left->evaluate() * right->evaluate();
		}
		else if (sign == '/') {
			if (right->evaluate() == 0) {
				throw runtime_error("division by zero");
			} else return left->evaluate() / right->evaluate();
		}
		else {
			throw runtime_error("bad sign");
		}
	}
};



int main() {
	shared_ptr<Node> current = make_shared<Op>('+');
	current->left = make_shared<Op>('*');
	current->right = make_shared<Op>('-');
	current->left->left = make_shared<Const>(1);
	current->left->right = make_shared<Const>(3);
	current->right->left = make_shared<Const>(5);
	current->right->right = make_shared<Const>(7);
	std::cout <<  current->evaluate() << endl;
	system("pause");
	return 1;
}