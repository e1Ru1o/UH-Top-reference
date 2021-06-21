template<typename T>
struct dinic
{
    struct edge
    {
        int src, dst;
        T flow, cap;
        int rev;
    };

    int n;
    vector<vector<edge>> adj;
    vector<int> level, que, iter;

    dinic(int n) : n(n), adj(n), level(n), que(n), iter(n) {}

    void add_edge(int u, int v, T cuv, T cvu = 0)
    {
        adj[u].push_back({u, v, 0, cuv, (int) adj[v].size()});
        if (u == v) ++adj[u].back().rev;
        adj[v].push_back({v, u, 0, cvu, (int) adj[u].size() - 1});
    }

    bool bfs(int source, int sink)
    {
        level.assign(n, -1);
        que[0] = sink;
        level[sink] = 0;

        for (int qf = 0, qb = 1; qf < qb; ++qf)
        {
            sink = que[qf];
            for (edge &e : adj[sink])
            {
                edge &erev = adj[e.dst][e.rev];
                if (level[erev.src] == -1 && erev.flow < erev.cap)
                    level[que[qb++] = erev.src] = 1 + level[sink];
            }
        }

        return level[source] >= 0;
    }

    T dfs(int source, int sink, T flow)
    {
        if (source == sink) return flow;

        for (; iter[source] < (int) adj[source].size(); ++iter[source])
        {
            edge &e = adj[source][iter[source]];

            if (e.flow < e.cap && level[e.dst] + 1 == level[source])
            {
                T delta = dfs(e.dst, sink, min(flow, e.cap - e.flow));
                if (delta > 0)
                {
                    e.flow += delta;
                    adj[e.dst][e.rev].flow -= delta;
                    return delta;
                }
            }
        }

        return 0;
    }

    static const T oo = numeric_limits<T>::max();

    T max_flow(int source, int sink)
    {
        T flow = 0;

        for (int u = 0; u < n; ++u)
            for (edge &e : adj[u]) e.flow = 0;

        while (bfs(source, sink))
        {
            iter.assign(n, 0);

            for (T cur; (cur = dfs(source, sink, oo)) > 0;)
                flow += cur;
        }

        return flow;
    }
};