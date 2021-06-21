struct bellman_ford
{
	int V, E;
	vector<ll> d;
	vector<int> parent, cycle;
	struct edge { int u, v; ll w; };
	vector<edge> G;

	bellman_ford(int n) :
			V(n), E(0), d(n, oo), parent(n, -1), cycle(0), G(0) {}

	void add_edge(int u, int v, ll w)
	{
		G.push_back({ u, v, w });
	}

	void negative_cycle(int u)
	{
		for (int i = 0; i < V; ++i)
			u = parent[u];

		cycle.push_back(u);
		for (int v = parent[u]; v != u; v = parent[v])
			cycle.push_back(v);
	}

	bool solve(int source = 0)
	{
		d[source] = 0;
		E = G.size();
		bool r = true;

		for (int i = 1; i <= V && r; ++i)
		{
			r = false;
			for (auto e : G)
				if (d[e.u] != oo && d[e.u] + e.w < d[e.v])
				{
					r = true;
					parent[e.v] = e.u;
					d[e.v] = d[e.u] + e.w;

					if (i == V)
					{
						negative_cycle(e.v);
						return true;
					}
				}
		}

		return false;
	}
};
