struct two_satisfability // 0-based
{
	int V, dt, k;
	vector<bool> del, usd;
	vector<int> dfsnum, low, scc, ord, S;
	vector<vector<int>> G, iG;

	two_satisfability(int n) :
		V(2 * n), dt(0), k(0), del(V, 0), usd(V, 0), dfsnum(V, 0), low(V, 0), scc(V), ord(0), S(0), G(V, vector<int>(0)), iG(V, vector<int>(0)) {}

	void add_or(int u, int v)
	{
		G[u ^ 1].push_back(v), G[v ^ 1].push_back(u);
		iG[u].push_back(v ^ 1), iG[v].push_back(u ^ 1);
	}

	void top_sort(int u)
	{
		usd[u] = true;
		for (int i = 0, sz = G[u].size(); i < sz; i++)
			if (!usd[G[u][i]]) top_sort(G[u][i]);
		ord.push_back(u);
	}

	void dfs(int u)
	{
		S.push_back(u), dfsnum[u] = low[u] = ++dt;

		for (int v : iG[u])
			low[u] = min(low[u], !dfsnum[v] ? dfs(v), low[v] : !del[v] ? dfsnum[v] : low[u]);

		if (low[u] == dfsnum[u] && ++k)
			while (!del[u]) scc[S.back()] = k, del[S.back()] = true, S.pop_back();
	}

	bool solve(vector<bool> &out)
	{
		for (int i = 0; i < V; ++i)
			if (!usd[i]) top_sort(i);

		for (int i = V - 1; i >= 0; --i)
			if (!dfsnum[ord[i]]) dfs(ord[i]);

		for (int i = 0; i < V; i += 2)
		{
			if (scc[i] == scc[i ^ 1]) return false;
			out.push_back(scc[i] > scc[i ^ 1]);
		}

		return true;
	}
};