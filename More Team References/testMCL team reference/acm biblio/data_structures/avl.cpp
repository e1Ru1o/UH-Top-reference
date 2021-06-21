template<typename T>
struct avl
{
	struct node
	{
		T key;
		int h, sz;
		node* ch[2];

		int bf(){ return ch[1]->h - ch[0]->h; };

		void update()
		{
			h = 1 + max(ch[0]->h, ch[1]->h);
			sz = 1 + ch[0]->sz + ch[1]->sz;
		}

	}*root, *null;

	node* new_node(const T &key)
	{
		node* u = new node();
		u->key = key;
		u->h = u->sz = 1;
		u->ch[0] = u->ch[1] = null;
		return u;
	}

	node* rotate(node* u, bool d)
	{
		if (u == null || u->ch[!d] == null)
			return u;

		node* t = u->ch[!d];
		u->ch[!d] = t->ch[d];
		t->ch[d] = u;

		u->update();
		t->update();

		return t;
	}

	node* balance(node* u)
	{
		u->update();

		if (u->bf() > 1)
		{
			if (u->ch[1]->bf() <= 0) // Right on left child
				u->ch[1] = rotate(u->ch[1], 1);
			u = rotate(u, 0); // Left
		}
		else if (u->bf() < -1)
		{
			if (u->ch[0]->bf() >= 0) // Left on right child
				u->ch[0] = rotate(u->ch[0], 0);
			u = rotate(u, 1); // Right
		}

		u->update();
		return u;
	}

	node* insert(node* u, const T &key)
	{
		if (u == null)
			return u = new_node(key);

		if (u->key == key)
			return u;

		bool d = (key < u->key);
		u->ch[!d] = insert(u->ch[!d], key);

		return u = balance(u);
	}

	node* erase(node* u, T key)
	{
		if (u == null)
			return u;

		int tmp = u->key;
		if (u->key == key)
		{
			if (u->ch[0] == null || u->ch[1] == null)
				return u->ch[u->ch[0] == null];
			else
			{
				node* t = u->ch[0];
				while (t->ch[1] != null)
					t = t->ch[1];
				key = u->key = t->key;
			}
		}

		bool d = (key < tmp);
		u->ch[!d] = erase(u->ch[!d], key);

		return u = balance(u);
	}

	void insert(T key)
	{
		root = insert(root, key);
	}

	void erase(T key)
	{
		root = erase(root, key);
	}

	bool find(const T &key)
	{
		node* u = root;
		while (true)
		{
			if (u == null)
				return false;
			if (u->key == key)
				return true;
			u = u->ch[!(key < u->key)];
		}
	}

	int order_of_key(const T &key)
	{
		int r = 0;
		node* u = root;
		while (true)
		{
			if (u == null)
				return r;
			if (key <= u->key)
				u = u->ch[0];
			else
				r += u->sz - u->ch[1]->sz, u = u->ch[1];
		}
	}

	T kth(int k)
	{
		assert(k <= root->sz);
		node* u = root;
		while (true)
		{
			if (u->sz - u->ch[1]->sz == k)
				return u->key;
			if (k <= u->ch[0]->sz)
				u = u->ch[0];
			else
				k -= u->sz - u->ch[1]->sz, u = u->ch[1];
		}
	}

	void in_order(node* u)
	{
		if (u == null)
			return;

		in_order(u->ch[0]);
		cout << u->key.first << "\n";
		in_order(u->ch[1]);
	}

	avl()
	{
		null = new node();
		null->h = null->sz = 0;
		null->ch[0] = null->ch[1] = 0;
		root = null;
	}
};