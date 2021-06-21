#include <bits/stdc++.h>
using namespace std;
//#define endl '\n'
typedef long long ll;
typedef pair<ll, ll> pii;
struct segment_tree
{
    vector<int> mn, mx;
    segment_tree(int n) : mn(4 * n), mx(4 * n)
    {
        build(1, 0, n);
    }
    void build(int p, int b, int e)
    {
        mn[p] = b;
        mx[p] = e - 1;
        if(b + 1 < e)
        {
            int m = (b + e) >> 1, l = p << 1, r = l | 1;
            build(l, b, m);
            build(r, m, e);
        }
    }
    void update(int p, int b, int e, int x, int v)
    {
        if(b + 1 == e) mn[p] = mx[p] = v;
        else
        {
            int m = (b + e) >> 1, l = p << 1, r = l | 1;
            if(x < m) update(l, b, m, x, v);
            else update(r, m, e, x, v);
            mn[p] = min(mn[l], mn[r]);
            mx[p] = max(mx[l], mx[r]);
        }
    }
    int query(int p, int b, int e, int x, int y, int v)
    {
        if(x <= b && e <= y)
        {
            if(mn[p] == mx[p])return mn[p] == v ? -1 : b;
            int m = (b + e) >> 1, l = p << 1, r = l | 1, ans = -1;
            ans = query(l, b, m, x, y, v);
            if(ans == -1)ans = query(r, m, e, x, y, v);
            return ans;
        }
        else
        {
            int m = (b + e) >> 1, l = p << 1, r = l | 1, ans = -1;
            if(x < m)     ans = query(l, b, m, x, y, v);
            if(ans == -1 && m < y)     ans = query(r, m, e, x, y, v);
            return ans;
        }
    }
};
struct disjoint_set
{
    int n, comp;
    vector<int> p;
    vector<vector<int>> S;
    disjoint_set(int _n) : n(_n), comp(n), p(n, -1), S(n)
    {
        for(int i = 0; i < n; ++i) S[i].emplace_back(i);
    }
    int root(int x)
    {
        return p[x] < 0 ? x : p[x] = root(p[x]);
    }
    bool merge(int x, int y, segment_tree &st)
    {
        if((x = root(x)) == (y = root(y))) return false;
        if(S[x].size() < S[y].size()) swap(x, y);
        for(auto &e : S[y])    st.update(1, 0, n, e, x), S[x].emplace_back(e);
        p[x] += p[y];
        p[y] = x;
        --comp;
        return true;
    }
};
int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    vector<ll> V(n);
    for(int i = 0, x; i < n; ++i)   scanf("%d", &x), V[i] = x;
    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int x, int y)
    {
        return V[x] < V[y];
    } );
    vector<int> id(n);
    for(int i = 0; i < n; ++i)   id[ord[i]] = i;
    vector<set<int>> g(n);
    for(int i = 0, a, b; i < m; ++i)
    {
        scanf("%d %d", &a, &b), --a, --b;
        a = id[a];
        b = id[b];
        if(a < b) swap(a, b);
        g[a].insert(b);
    }
    sort(V.begin(), V.end());
    disjoint_set ds(n);
    segment_tree st(n);
    id = vector<int>(n, -1);
    auto get_nxt = [&](int x)
    {
        if(id[x] >= x) return -1;
        int nxt = st.query(1, 0, n, id[x] + 1, x + 1, ds.root(x));
        return nxt;
    };
    set<pii> S;
    for(int i = 0; i < n; ++i)
    {
        id[i] = get_nxt(i);
        while(id[i] != -1 && g[i].find(id[i]) != g[i].end())    id[i] = get_nxt(i);
        if(id[i] != -1)    S.emplace(V[i] + V[id[i]] + V[i], i);
    }
    ll ans = 0;
    for(auto &el : V)   ans -= el;
    while(!S.empty())
    {
        pii u = *S.begin();
        S.erase(S.begin());
        if(ds.merge(u.second, id[u.second], st))    ans += u.first;
        int i = u.second;
        id[i] = get_nxt(i);
        while(id[i] != -1 && g[i].find(id[i]) != g[i].end())    id[i] = get_nxt(i);
        if(id[i] != -1)    S.emplace(V[i] + V[id[i]] + V[i], i);
    }
    if(ds.comp > 1)   printf("NIE\n");
    else   printf("%lld\n", ans);
    return 0;
}
