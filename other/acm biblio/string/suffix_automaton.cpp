/*
	Tested: SPOJ LCS
	COmplexity: O(n)
*/

template<typename T>
struct suffix_automata
{
	struct state
	{
		int len;
		state *link;
		map<T, state*> next;
	};

	vector<state*> states;
	state *last;

	suffix_automata()
	{
		states.push_back(new state{ 0, nullptr });
		last = states.front();
	}

	void extend(T c)
	{
		state *nlast = new state{ last->len + 1 }, *p;
		states.push_back(nlast);

		for (p = last; p != nullptr && !p->next.count(c); p = p->link)
			p->next[c] = nlast;

		if (p == nullptr)
			nlast->link = states.front();
		else
		{
			state *q = p->next[c];
			if (p->len + 1 == q->len)
				nlast->link = q;
			else
			{
				state *clone = new state{ p->len + 1, 
					q->link, q->next };
				states.push_back(clone);
				for (; p != nullptr && p->next[c] == q; p = p->link)
					p->next[c] = clone;
				q->link = nlast->link = clone;
			}
		}

		last = nlast;
	}

	~suffix_automata()
	{
		for (state *e : states)
			delete e;
	}
};
