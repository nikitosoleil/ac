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
		int sz = 1;
		Node(T v, Color c) : v(v), c(c) {}
		void update()
		{
			sz = 1 + (l ? l->sz : 0) + (r ? r->sz : 0);
		}
	} *root = nullptr;
	void lr(Node *&n) // left rotation
	{
		Node *t = n;
		n = n->r;
		t->r = n->l;
		n->l = t;
		n->l->update();
	}
	void rr(Node *&n) // right rotation
	{
		Node *t = n;
		n = n->l;
		t->l = n->r;
		n->r = t;
		n->r->update();
	}
	Color c(Node *&n)
	{
		return n ? n->c : black;
	}
	void insert(Node *&n, Node *p, Node *b, T v)
	{
		if (!n)
			n = new Node(v, red);
		else if (v < n->v)
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
		n->update();
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
public:
	RBT() {}
	~RBT()
	{
		clear();
	}
	void insert(T &value)
	{
		insert(root, nullptr, nullptr, value);
	}
	void clear()
	{
		clear(root);
	}
	bool order(int num, T &result)
	{
		Node *n = root;
		while (true)
		{
			if (!n)
				return false;
			else
			{
				int l_sz = (n->l ? n->l->sz : 0);
				if (num == l_sz + 1)
				{
					result = n->v;
					return true;
				}
				else if (num <= l_sz)
					n = n->l;
				else
				{
					num -= l_sz + 1;
					n = n->r;
				}
			}
		}
	}
};
}