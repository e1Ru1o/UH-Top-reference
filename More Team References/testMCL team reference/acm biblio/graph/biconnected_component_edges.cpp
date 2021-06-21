vector<int> num(n), low(n), stk;
vector<vector<int>> comps;
int timer = 0;

function<void(int, int)> dfs = [&](int u, int p)
{
	num[u] = low[u] = ++timer;
	stk.push_back(u);

	for (int v : adj[u])
		if (v != p)
		{
			if (!num[v])
			{
				dfs(v, u);
				low[u] = min(low[u], low[v]);
			}
			else low[u] = min(low[u], num[v]);
		}

	if (num[u] == low[u])
	{
		comps.push_back({});

		do
		{
			comps.back().push_back(stk.back());
			stk.pop_back();
		}
		while (comps.back().back() != u);
	}
};