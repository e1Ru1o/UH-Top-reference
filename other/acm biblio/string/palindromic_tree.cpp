/*
	at each step when add a character:
	suf->len is the length of longest suffix palindrome
	suf->suf is the next node with longest suffix palindrome
	
	Tested: SPOJ LPS, APIO14_A
	Complexity: O(n)
*/

template<typename T>
struct palindromic_tree
{
	struct node
	{
		int len;
		map<T, node*> next;
		node *suf;
	};

	vector<T> s;
	vector<node*> nodes;
	node *neg, *zero, *suf;

	node* new_node()
	{
		nodes.push_back(new node());
		return nodes.back();
	}

	palindromic_tree()
	{
		(neg = new_node())->len = -1;
		suf = zero = new_node();
		neg->suf = zero->suf = neg;
	}

	void add(T c)
	{
		int i = s.size();
		s.push_back(c);
		node *p = suf;
		for (; i - 1 - p->len < 0 || s[i - 1 - p->len] != c; p = p->suf);
		if (p->next.count(c))
		{
			suf = p->next[c];
			return;
		}
		suf = new_node();
		suf->len = p->len + 2;
		p->next[c] = suf;
		if (suf->len == 1)
			suf->suf = zero;
		else
		{
			p = p->suf;
			for (; i - 1 - p->len < 0 || 
				s[i - 1 - p->len] != c; p = p->suf);
			suf->suf = p->next[c];
		}
	}

	~palindromic_tree()
	{
		for (auto p : nodes)
			delete p;
	}
};

