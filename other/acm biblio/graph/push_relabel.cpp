template<typename T>
struct push_relabel
{
	struct edge { int v, next; T w, f; };

	int n;
	queue<int> q;
	vector<bool> m;
	vector<T> e;
	vector<int> h, p, c;
	vector<edge> G;

	push_relabel(int n) :
			n(n), p(n, -1) {}

	void add_edge(int u, int v, T w)
	{
		G.push_back({ v, p[u], w, 0 });
		p[u] = G.size() - 1;
		G.push_back({ u, p[v], 0, 0 });
		p[v] = G.size() - 1;
	}

	inline void enqueue(int u)
	{
		if (!m[u] && e[u])
		{
			m[u] = true;
			q.push(u);
		}
	}

	void push(int u, int i)
	{
		T mf = min(e[u], G[i].w - G[i].f);
		if (mf && h[u] > h[G[i].v])
		{
			G[i].f += mf;
			e[G[i].v] += mf;
			G[i ^ 1].f -= mf;
			e[u] -= mf;
			enqueue(G[i].v);
		}
	}

	void relabel(int u)
	{
		--c[h[u]];
		h[u] = 2 * n;
		for (int i = p[u]; i != -1; i = G[i].next)
			if (G[i].w - G[i].f && h[G[i].v] < h[u])
				h[u] = h[G[i].v];
		++c[++h[u]];
		enqueue(u);
	}

	T max_flow(int s, int t)
	{
		e.assign(n, 0);
		h.assign(n, 0);
		c.assign(2 * n, 0);
		m.assign(n, false);
		for (auto &e : G)
			e.f = 0;

		c[0] = n - 1;
		c[n] = 1;
		h[s] = n;
		m[s] = m[t] = true;
		for (int i = p[s]; i != -1; i = G[i].next)
		{
			e[s] += G[i].w;
			push(s, i);
		}

		for (int u; !q.empty(); q.pop())
		{
			u = q.front();
			m[u] = false;

			for (int i = p[u]; e[u] && i != -1; i = G[i].next)
				push(u, i);

			if (e[u])
			{
				if (c[h[u]] == 1)
				{
					for (int i = 0; i < n; ++i)
						if (h[i] >= h[u])
						{
							--c[h[i]];
							h[i] = max(h[i], n + 1);
							++c[h[i]];
							enqueue(i);
						}
				}
				else
					relabel(u);
			}
		}

		T flow = 0;
		for (int i = p[s]; i != -1; i = G[i].next)
			flow += G[i].f;
		return flow;
	}
};