struct strongly_connected_component
{
	int V, dt;
	vector<bool> del;
	vector<int> dfsnum, low, S;
	vector<vector<int> > G, SCC;

	strongly_connected_component(int n) :
			V(n), dt(0), del(n, 0), dfsnum(n, 0), low(n, 0), S(0), G(n, vector<int>(0)), SCC(0) {}

	void add_edge(int u, int v)
	{
		G[u].push_back(v);
	}

	void dfs(int u)
	{
		S.push_back(u);
		dfsnum[u] = low[u] = ++dt;

		for (auto v : G[u])
			low[u] = min(low[u], !dfsnum[v] ? dfs(v), low[v] : !del[v] ? dfsnum[v] : low[u]);

		if (low[u] == dfsnum[u])
		{
			SCC.push_back(vector<int>(0));
			while (!del[u])
			{
				SCC.back().push_back(S.back());
				del[S.back()] = true;
				S.pop_back();
			}
		}
	}

	vector<vector<int> > solve()
	{
		for (int i = 0; i < V; ++i)
			if (!dfsnum[i]) dfs(i);
		return SCC;
	}
};
