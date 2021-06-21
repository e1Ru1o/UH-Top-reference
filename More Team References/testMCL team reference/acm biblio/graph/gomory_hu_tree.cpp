/*
	Gomory-Hu tree

	Tested: SPOj MCQUERY
	Complexity: O(n-1) max-flow call
*/

template<typename T>
struct graph
{
	struct edge
	{
		int src, dst;
		T cap, flow;
		int rev;
	};

	int n;
	vector<vector<edge>> adj;

	graph(int n) : n(n), adj(n) {}

	void add_edge(int src, int dst, T cap)
	{
		adj[src].push_back({ src, dst, cap, 0, (int) adj[dst].size() });
		if (src == dst)
			adj[src].back().rev++;
		adj[dst].push_back({ dst, src, cap, 0, (int) adj[src].size() - 1 });
	}

	vector<int> level, iter;
	T augment(int u, int t, T cur)
	{
		if (u == t)
			return cur;
		for (int &i = iter[u]; i < (int) adj[u].size(); ++i)
		{
			edge &e = adj[u][i];
			if (e.cap - e.flow > 0 && level[u] < level[e.dst])
			{
				T f = augment(e.dst, t, min(cur, e.cap - e.flow));
				if (f > 0)
				{
					e.flow += f;
					adj[e.dst][e.rev].flow -= f;
					return f;
				}
			}
		}
		return 0;
	}

	int bfs(int s, int t)
	{
		level.assign(n, -1);
		level[s] = 0;
		queue<int> Q;
		for (Q.push(s); !Q.empty(); Q.pop())
		{
			int u = Q.front();
			if (u == t)
				break;
			for (auto &e : adj[u])
			{
				if (e.cap - e.flow > 0 && level[e.dst] < 0)
				{
					Q.push(e.dst);
					level[e.dst] = level[u] + 1;
				}
			}
		}
		return level[t];
	}

	const T oo = numeric_limits<T>::max();

	T max_flow(int s, int t)
	{
		for (int u = 0; u < n; ++u) // initialize
			for (auto &e : adj[u])
				e.flow = 0;
		T flow = 0;
		while (bfs(s, t) >= 0)
		{
			iter.assign(n, 0);
			for (T f; (f = augment(s, t, oo)) > 0;)
				flow += f;
		} // level[u] == -1 ==> t-side
		return flow;
	}

	vector<edge> tree;

	void gomory_hu()
	{
		tree.clear();
		vector<int> parent(n);
		for (int u = 1; u < n; ++u)
		{
			tree.push_back({ u, parent[u], max_flow(u, parent[u]) });
			for (int v = u + 1; v < n; ++v)
				if (level[v] >= 0 && parent[v] == parent[u])
					parent[v] = u;
		}
	}
};
