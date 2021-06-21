struct bridge
{
    int V, dt;
    vector<int> low, dfsnum, parent;
    vector<pair<int, int>> bridges;
    vector<vector<int>> G;
 
    bridge(int n) :
            V(n), dt(0), low(n, 0), dfsnum(n, 0), parent(n), bridges(0), G(n, vector<int>(0)) {}
 
    void add_edge(int u, int v)
    {
        G[u].push_back(v), G[v].push_back(u);
    }
 
    void dfs(int u)
    {
        dfsnum[u] = low[u] = ++dt;
        for (int v : G[u])
            if (!dfsnum[v])
            {
                parent[v] = u, dfs(v), low[u] = min(low[u], low[v]);
                if (dfsnum[u] < low[v]) bridges.push_back(make_pair(u, v));
            }
            else if (v != parent[u])
                low[u] = min(low[u], dfsnum[v]);
    }
 
    vector<pair<int, int>> solve()
    {
        for (int i = 0; i < V; ++i)
            if (!dfsnum[i]) dfs(i);
        return bridges;
    }
};