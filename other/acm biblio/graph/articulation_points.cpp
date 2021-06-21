struct articulation_points
{
    int V, dt;
    vector<bool> ap;
    vector<int> dfsnum, low;
    vector<vector<int>> G;
 
    articulation_points(int n) :
            V(n), dt(0), ap(n, 0), dfsnum(n, 0), low(n, 0), G(n, vector<int>(0)) {}
 
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
                dfs(v), low[u] = min(low[u], low[v]);
                if ((dfsnum[u] == 1 && dfsnum[v] > 2) || (dfsnum[u] != 1 && low[v] >= dfsnum[u])) ap[u] = true;
            }
            else low[u] = min(low[u], dfsnum[v]);
    }
 
    vector<bool> solve()
    {
        for (int i = 0; i < V; ++i)
            if (!dfsnum[i]) dt = 0, dfs(i);
        return ap;
    }
};