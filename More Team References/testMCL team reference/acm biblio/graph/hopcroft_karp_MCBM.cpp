struct hopcroft_karp
{
	int N, M;
	vector<vector<int> > G;
	vector<int> match, d, q;

	hopcroft_karp(int n, int m) :
			N(n), M(m), G(n, vector<int>(0)), match(n + m, -1) {}

	void add_edge(int u, int v)
	{
		G[u].push_back(v);
	}

	bool bfs()
	{
		d.assign(N + M, 0), q.clear(), q.reserve(N);
		for (int i = 0; i < N; ++i)
			if (match[i] == -1) q.push_back(i);

		bool f = false;
		for (size_t i = 0; i < q.size(); ++i)
			for (auto v : G[q[i]])
				if (!d[N + v])
				{
					d[N + v] = d[q[i]] + 1;
					if (match[N + v] != -1)
						d[match[N + v]] = d[N + v] + 1, q.push_back(match[N + v]);
					else
						f = true;
				}

		return f;
	}

	bool dfs(int u)
	{
		for (auto v : G[u])
			if (d[N + v] == d[u] + 1)
			{
				d[N + v] = 0;
				if (match[N + v] == -1 || dfs(match[N + v]))
				{
					match[u] = v, match[N + v] = u;
					return true;
				}
			}

		return false;
	}

	int solve()
	{
		int flow = 0;
		while (bfs())
			for (int i = 0; i < N; ++i)
				flow += (match[i] == -1 && dfs(i));
		return flow;
	}
};