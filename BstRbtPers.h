#pragma once

using namespace std;

namespace BST
{
template < class T >
class RBT
{
private:
	enum Color { red, black };
	struct Node
	{
		T v;
		Color c;
		Node *l = nullptr, *r = nullptr;
		Node(T v, Color c) : v(v), c(c) {}
		Node(Node *n) : v(n->v), c(n->c), l(n->l), r(n->r) {}
	};
	vector < Node * > roots = {nullptr}; // and my home was never on the ground
	void lr(Node *&n) // left rotation
	{
		Node *t = n;
		n = n->r;
		t->r = n->l;
		n->l = t;
	}
	void rr(Node *&n) // right rotation
	{
		Node *t = n;
		n = n->l;
		t->l = n->r;
		n->r = t;
	}
	Color c(Node *&n)
	{
		return n ? n->c : black;
	}
	void insert(Node *&n, Node *p, Node *b, T v)
	{

		if (!n)
			n = new Node(v, red);
		else
		{
			if (n->l)
				n->l = new Node(n->l);
			if (n->r)
				n->r = new Node(n->r);
			if (v < n->v)
			{
				insert(n->l, n, n->r, v);
				if (n->c == red && n->l->c == red)
				{
					if (c(b) == red)
					{
						n->c = black;
						b->c = black;
						p->c = red;
					}
					else
					{
						if (p && p->r == n)
							rr(n);
					}
				}
				if (c(n->l) == red && c(n->l->l) == red)
				{
					rr(n);
					n->c = black;
					n->r->c = red;
				}
			}
			else if (v > n->v)
			{
				insert(n->r, n, n->l, v);
				if (n->c == red && n->r->c == red)
				{
					if (c(b) == red)
					{
						n->c = black;
						b->c = black;
						p->c = red;
					}
					else
					{
						if (p && p->l == n)
							lr(n);
					}
				}
				if (c(n->r) == red && c(n->r->r) == red)
				{
					lr(n);
					n->c = black;
					n->l->c = red;
				}
			}
		}
	}
	void clear(Node *n)
	{
		if (n)
		{
			clear(n->l);
			clear(n->r);
			delete n;
		}
	}
	int size(Node *n)
	{
		if (n)
			return size(n->l) + size(n->r) + 1;
		else
			return 0;
	}
	void print(Node *n, int h)
	{
		cout << n->v.name << ' ';
		if(n->c == black)
			cout << "B\n";
		if (n->c == red)
			cout << "R\n";
		if(n->l)
		{
			for (int i = 0; i < h; ++i)
				cout << '\t';
			cout << n->v.name << " L ";
			print(n->l, h+1);
		}
		if (n->r)
		{
			for (int i = 0; i < h; ++i)
				cout << '\t';
			cout << n->v.name << " R ";
			print(n->r, h+1);
		}
	}
public:
	RBT() {}
	~RBT()
	{
		clear();
	}
	void insert(T &value)
	{
		Node *new_root = nullptr;
		if (roots.size() > 1)
			new_root = new Node(roots[roots.size() - 1]);
		roots.push_back(new_root);
		insert(roots[roots.size() - 1], nullptr, nullptr, value);
		roots[roots.size() - 1]->c = black;
	}
	void clear()
	{
		for (Node *root: roots)
			clear(root);
	}
	int size(int version)
	{
		return size(roots[version]);
	}
	void print(int version)
	{
		print(roots[version], 0);
	}
};
}