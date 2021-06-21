template<typename T>
struct LCA
{
	int n;
	vector<vector<pair<int, T>>> adj;
	vector<vector<int>> lca;
	vector<vector<T>> dist;
	vector<int> p, lvl;

	LCA(int n) : n(n), adj(n + 1), lca(__lg(n) + 1, vector<int>(n + 1))
					, dist(__lg(n) + 1, vector<T>(n + 1)), p(n + 1), lvl(n + 1) {}

	void add_edge(int u, int v, T w)
	{
		adj[u].push_back({v, w});
		adj[v].push_back({u, w});
	}

	void buildlca(int r = 1)
	{
		queue<int> q;
		q.push(r);
		p[r] = -1;
		lvl[r] = 0;

		while (!q.empty())
		{
			int u = q.front();
			q.pop();
			for (auto i : adj[u])
			{
				int v = i.first, w = i.second;
				if (v == p[u]) continue;

				q.push(v);
				p[v] = u;
				lca[0][v] = u;
				dist[0][v] = w;
				lvl[v] = lvl[u] + 1;

				for (int i = 1, lg = __lg(lvl[v]); i <= lg; i++)
				{
					lca[i][v] = lca[i - 1][lca[i - 1][v]];
					dist[i][v] = dist[i - 1][lca[i - 1][v]] + dist[i - 1][v];
				}
			}
		}
	}

	T query(int u, int v)
	{
		if (lvl[v] > lvl[u])
			swap(u, v);

		T D = 0;
		for (int i = __lg(lvl[u]); i >= 0; i--)
			if (lvl[u] - (1 << i) >= lvl[v])
			{
				D += dist[i][u];
				u = lca[i][u];
			}

		if (u == v)
			return D; //u;

		for (int i = __lg(lvl[u]); i >= 0; i--)
			if ((1 << i) <= lvl[u] && lca[i][u] != lca[i][v])
			{
				D += dist[i][v] + dist[i][u];
				u = lca[i][u];
				v = lca[i][v];
			}

		D += dist[0][u] + dist[0][v];
		return D; //p[u];
	}
};