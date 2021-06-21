typedef pair<int, int> ii;

struct biconnected_component
{
	int V, E, dt;
	vector<ii> S;
	vector<bool> usd;
	vector<int> dfsnum, low;
	vector<vector<ii>> G, BCC;

	biconnected_component(int n) :
			V(n), E(0), dt(0), S(0), usd(0), dfsnum(n, 0), low(n, 0), G(n, vector<ii>(0)), BCC(0) {}

	void add_edge(int u, int v)
	{
		G[u].push_back(ii(v, E)), G[v].push_back(ii(u, E++));
	}

	void dfs(int u)
	{
		dfsnum[u] = low[u] = ++dt;

		for (auto i : G[u])
		{
			int v = i.first, e = i.second;

			if (!usd[e])
				S.push_back(ii(u, v)), usd[e] = true;

			if (!dfsnum[v])
			{
				dfs(v);
				if (low[v] >= dfsnum[u])
				{
					BCC.push_back(vector<ii>(0));
					do
					{
						BCC.back().push_back(S.back()), S.pop_back();
					} while (BCC.back().back() != ii(u, v));
				}
				else low[u] = min(low[u], low[v]);
			}
			else low[u] = min(low[u], dfsnum[v]);
		}
	}

	vector<vector<ii>> solve()
	{
		usd.resize(E, false);
		for (int i = 0; i < V; ++i)
			if (!dfsnum[i]) dfs(i);
		return BCC;
	}
};