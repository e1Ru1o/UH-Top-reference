// My Contest Data

// Input - Output  ############################################
ios_base::sync_with_stdio(0);
cin.tie(0);

freopen("file.in", "r", stdin);
freopen("file.out", "w", stdout);
//##############################################################

// Output size #################################################
//C++ style
cout << setw(10) << setfill(’0’) << n << endl;
//C style
printf("%010lld\n", n);
//##############################################################

// numerical limits ############################################
numeric_limits<ll>::max();
numeric_limits<ll>::min();
//##############################################################

// Criva - Sieve ###############################################
vector<int> primes;
vector<bool> mark(n + 1);
for(ll i = 2; i <= n; ++i){
    if(!mark[i]){
        primes.push_back(i);                
        for(ll j = i * i; j <= n; j += i)
            mark[j] = true;
    }
}
//##############################################################

// LIS #########################################################
int lis(vector<int> &v) {
    set<int> p;
    for(int i = 0; i < v.size(); ++i) {
        auto it = lower_bound(p.begin(), p.end(), v[i]);
        if(it != p.end()) p.erase(it);
        p.insert(v[i]);
    }
    return p.size();
}
//###############################################################

// Combinations DP ##############################################
vector<vector<int>> cb(n + 1, vector<int>(n + 1));
for(int i = 0; i <= n; ++i){
    for(int j = 0; j <= i; ++j){
        if(j == 0 || i == j)
            cb[i][j]    = 1;
        else
            cb[i][j] = (cb[i - 1][j - 1] + cb[i - 1][j]) % MOD;
    }
}
//###############################################################

// Bin Exp ######################################################
typedef long long ll;
ll BinExp(ll num, ll pot){
    ll x = 1;
    for(; pot > 0; pot /= 2){
        if(pot & 1)
            x = (x * num) % MOD;
        num = (num * num) % MOD;
    }
    return x;
}
//If MOD is a prime number is possible to find
//the modular inverse of ‘num‘ with ‘pot = MOD - 2‘
//###############################################################

// AVL ##########################################################
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp>     // Including tree_order_statistics_node_update

#define select find_by_order
#define rank order_of_key

using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
//###############################################################

// Random ##########################################################
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
 
template<typename T>
static T randint(T lo, T hi){
    return uniform_int_distribution<T>(lo, hi)(rng);
}   
//###############################################################

// Trie #########################################################
struct Trie{
    string s;
    int node = 0;
    int trie[MAX][30];
    long long counter[MAX];
    long long fin[MAX];
    int PrefixQuery(int &k, int v){
        int pos = 0;
        while(k < s.size() && trie[pos][s[k] - ’a’] != 0){
            pos = trie[pos][s[k++] - ’a’];
            counter[pos] += v;
        }
        return pos;
    }
    void Add(int k, int v){
        ++counter[0];
        int pos = PrefixQuery(k, v);
        while(k < s.size()){
            trie[pos][s[k++] - ’a’] = ++node;
            pos = node;
            counter[pos] += v;
        }
        fin[pos] += v;
    }
    void Remove(int k, int v){
        int safe = k;
        int pos = PrefixQuery(k, 0);
        if(k == s.size()){
            fin[pos] -= v;
            fin[pos] = max(0, fin[pos]);
            k = safe;
            PrefixQuery(k, -1 * v);
        }
    }
};
//###############################################################

// Fenwick - ABI - BIT ##########################################
typedef long long ll;
struct Fenwick{
    vector<ll> tree;
    int n;
    Fenwick(int n): n(n), tree(n + 1, 0){}
    //Point Update
    void update(int i, ll val){
        if(i > 0)
            while (i <= n) {
                tree[i] += val;
                i += i & -i;
            }
    }
    //Point query
    ll query(int i){
        ll sum = 0;
        while(i > 0){
            sum += tree[i];
            i -= i & -i;
        }
        return sum;
    }
    //Range update
    void rangeUpdate(int l, int r, ll val){
        update(l, val);
        update(r + 1, -val);
    }
    ll count(){ return query(n); }
    ll from(int i){ return count() - query(i - 1); }
    ll query(int l, int r) {return query(r) - query(l - 1); }
};
//Range update when Range Query
void rangeUpdate(Fenwick &f1, Fenwick &f2, int l, int r, ll val){
    f1.update(l, val);
    f1.update(r + 1, -val);
    f2.update(l, val * (l - 1));
    f2.update(r + 1, -val * r);
}
ll mergeQuery(Fenwick &f1, Fenwick &f2, int i){
    return (f1.query(i) * i) - f2.query(i);
}
//Range Query
ll rangeQuery(Fenwick &f1, Fenwick &f2, int l, int r){
    return mergeQuery(f1, f2, r) - mergeQuery(f1, f2, l - 1);
}
//###############################################################

// Segment Tree Lazy ############################################
struct segment_tree{
    int n;
    vector<ll> data;
    vector<ll> st;
    vector<ll> lazy;
    segment_tree(int n) : n(n), data(n), st(4 * n), lazy(4 * n) {}
    void push_lazy(int node){
        int l = node * 2, r = l + 1;
        //Set son’s lazy and new answer
        lazy[l] += lazy[node];
        st[l] += lazy[node];
        lazy[r] += lazy[node];
        st[r] += lazy[node];
        //clean node lazy
        lazy[node] = 0;
    }
    void build() { build(1, 1, n + 1); }
    void build(int node, int a, int b){
        if( a == b - 1){
            // set initial value
            st[node] = data[a - 1];
            return;
        }
        int mid = (a + b) / 2, l = node * 2, r = l + 1;
        build(l, a, mid);
        build(r, mid, b);
        //set node’s answer
        st[node] = min(st[l], st[r]);
    }
    void update(int x, int y, ll v) { update(1, 1, n + 1, x, y + 1, v); }
    ll update(int node, int a, int b, int x, int y, ll v){
        if(x <= a && b <= y){
            //Add Lazy
            lazy[node] += v;
            st[node] += v;
        }
        else{
            push_lazy(node);
            int mid = (a + b) / 2, l = node * 2, r = l + 1;
            if(y <= mid)
                st[node] = min(st[r], update(l, a, mid, x, y, v));
            else if(x >= mid)
                st[node] = min(st[l], update(r, mid, b, x, y, v));
            else {
                st[node] = update(l, a, mid, x, y, v);
                st[node] = min(st[node], update(r, mid, b, x, y, v));
            }
        }
        return st[node];
    }
    ll query(int x, int y) { return query(1, 1, n + 1, x, y + 1); }
    ll query(int node, int a, int b, int x, int y){
        if(x <= a && b <= y){
            return st[node];
        }
        push_lazy(node);
        int mid = (a + b) / 2, l = node * 2, r = l + 1;
        ll val;
        if(y <= mid)
            val = query(l, a, mid, x, y);
        else if(x >= mid)
            val = query(r, mid, b, x, y);
        else {
            val = query(l, a, mid, x, y);
            val = min(val, query(r, mid, b, x, y));
        }
        return val;
    }
};
//###############################################################

// Persistent Segment Tree ######################################
struct segment_tree{
    struct st_node{
        int val;
        int r, l;
    };
    int n;
    int identifier = 0;
    vector<st_node> container;
    vector<int> versions;
    segment_tree(ll n, int v):
            n(n), versions(v + 1), container(v * (ceil(log2(n + 1)) + 1)){}
    void CopieAndInsert(int original, int &copie, int l, int r, int element, int cant){
        copie = ++identifier;
        container[copie] = container[original];
        container[copie].val += cant;
        if(l + 1 == r)
            return;
        int middle = (l + r) / 2;
        if(element < middle){
            CopieAndInsert(container[original].l, container[copie].l,
                           l, middle, element, cant);
        }
        else{
            CopieAndInsert(container[original].r, container[copie].r,
                           middle, r, element, cant);
        }
    }
    void add(int old, int cur, int x, int cant) {
        CopieAndInsert(versions[old], versions[cur], 1, n + 1, x, cant);
    }
    int query(int v, int x) {return query(versions[v], 1, n + 1, x);}
    int query(int root, int l, int r, int element){
        if(l + 1 == r){
            return container[root].val;
        }
        int middle = (l + r) / 2;
        if(element < middle)
            return query(container[root].l, l, middle, element);
        else
            return query(container[root].r, middle, r, element);
    }
};
//###############################################################

// Aho-Corasick #################################################
typedef pair<int, int> pi;
struct AhoCorasick {
    int alpha;
    int node = -1;
    vector<vector<int>> trie;
    vector<bool> fin;
    AhoCorasick(int top, int alpha):
            alpha(alpha), trie(top, vector<int>(alpha)), fin(top) {}
    AhoCorasick(int alpha): alpha(alpha) { NewNode(); }
    int NewNode(){
        trie.emplace_back(vector<int>(alpha));
        fin.push_back(false);
        return ++node;
    }
    void Add(string& s, int v = 1) {
        int pos = 0;
        for(auto c:s) {
            if(trie[pos][c - ’a’] == 0)
            trie[pos][c - ’a’] = NewNode();
            pos = trie[pos][c - ’a’];
        }
        fin[pos] = true;
    }
    void Fails() {
        queue<pi> q;
        int a, b;
        for (int i = 0; i < alpha; ++i)
            if (trie[0][i] != 0)
                q.push({trie[0][i], 0});
        pi v;
        while (!q.empty()) {
            v = q.front();
            q.pop();
            for (int i = 0; i < alpha; ++i) {
                a = trie[v.first][i];
                b = trie[v.second][i];
                if (a != 0) {
                    fin[a] = fin[a] || fin[b];
                    q.push({a, b});
                }
                else
                    trie[v.first][i] = b;
            }
        }
    }
};
//###############################################################

// Disjoin Set ##################################################
struct DS{
    vector<int> p, sz;
    DS(int n): p(n, 0), sz(n, 1){
        iota(all(p), 0);
    }
    int SetOf(int x){
        return (p[x] == x)? x : p[x] = SetOf(p[x]);
    }
    bool Merge(int x, int y){
        x = SetOf(x);
        y = SetOf(y);
        if(x == y)
            return false;
        if(sz[x] < sz[y])
            swap(x, y);
        p[y] = x;
        sz[x] += sz[y];
        return true;
    }
};
//###############################################################

// Indexed Heap #################################################
struct Heap{
    int cant;
    vector<int> heap, pos, idx;
    Heap(): heap(1, 0), pos(1, 0), idx(1, 0), cant(0){}
    Heap(int n): heap(n + 1, 0), pos(n + 1, 0), idx(n + 1, 0), cant(0){}
    void Add(int x){
        if(++cant >= (int)heap.size()){
            heap.push_back(0);
            idx.push_back(0);
            pos.push_back(0);
        }
        heap[cant] = x;
        idx[cant] = pos[cant] = cant;
        HeapifyUp(cant);
    }
    void Insert(int x){
        heap[++cant] = x;
        HeapifyUp(cant);
    }
    int SuprimeAt(int x){
        return Suprime(pos[x]);
    }
    int Suprime(int x = 1){
        int result = heap[x];
        heap[x] = heap[cant--];
        HeapifyDown(x);
        HeapifyUp(x);
        return result;
    }
    int Peek(){ return heap[1]; }
    void Swap(int x, int y){
        pos[idx[x]] = y;
        pos[idx[y]] = x;
        swap(idx[x], idx[y]);
        swap(heap[x], heap[y]);
    }
    void HeapifyUp(int x){
        while(x > 1 && heap[x] < heap[x / 2]){
            Swap(x, x / 2);
            x = x / 2;
        }
    }
    void HeapifyDown(int x){
        while(2 * x <= cant){
            int i = 2 * x;
            i += (i < cant && heap[i + 1] < heap[i]);
            if(heap[x] <= heap[i])
                break;
            Swap(x, i);
            x = i;
        }
    }
    bool empty() {return cant == 0;}
};
//###############################################################

// Articulation-points Bridge-edges #############################
struct articulation_points{
    int V, dt;
    vector<bool> ap;
    vector<int> d, low;
    vector<vector<int>> G;
    articulation_points(int n): V(n), dt(0), d(n, 0), low(n, 0), G(n), ap(n) {}
    void add_edge(int u, int v){
        G[u].push_back(v);
    }
    void dfs(int u){
        d[u] = low[u] = ++dt;
        for (int v : G[u])
            if (!d[v]){
                dfs(v);
                low[u] = min(low[u], low[v]);
                if((d[u] == 1 && d[v] > 2) || (d[u] != 1 && low[v] >= d[u]))
                    ap[u] = true;
            }
            else low[u] = min(low[u], d[v]);
    }
    void solve(){
        for (int i = 0; i < V; ++i)
            if (!d[i]) dt = 0, dfs(i);
    }
};
struct bridge{
    int V, dt;
    vector<pair<int, int>> bridges;
    vector<int> low, d, parent;
    vector<vector<int>> G;
    bridge(int n) :
            V(n), dt(0), low(n, 0), d(n, 0), parent(n), bridges(0), G(n, vector<int>(0)) {}
    void add_edge(int u, int v){
        G[u].push_back(v);
    }
    void dfs(int u){
        d[u] = low[u] = ++dt;
        for (int v : G[u])
            if (!d[v]){
                parent[v] = u;
                dfs(v);
                low[u] = min(low[u], low[v]);
                if(d[u] < low[v])
                    bridges.emplace_back(min(u, v), max(u, v));
            }
            else if (v != parent[u])
                low[u] = min(low[u], d[v]);
    }
    void solve(){
        for (int i = 0; i < V; ++i)
            if (!d[i]) dfs(i);
    }
};
//###############################################################

// Z-function ###################################################
vector<int> z_function(string &s) {
    int n = (int) s.length();
    vector<int> z(n, 0);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = min (r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}
//###############################################################

// Edmonds-Karp #################################################
struct EdmondsKarp {
    struct edge {
        int from, to, f, cap;
    };
    matrix G;
    vector<edge> E;
    int source, sink;
    const int inf = 1e9;

    EdmondsKarp(int s, int t): source(s), sink(t), G(t + 1){};

    void add_edge(int from, int to, int cap){
        G[from].push_back(E.size());
        E.push_back({from, to, cap, cap});
        G[to].push_back(E.size());
        E.push_back({to, from, 0, cap});
    }

    int solve(){
        auto bfs = [&](){
            vector<int> dad(sink + 1, -1), e(sink + 1);
            dad[source] = -2;

            queue<int> q;
            q.push(source);
            while(!q.empty()){
                int v = q.front();
                q.pop();

                if(v == sink) break;

                for(int i = 0; i < G[v].size(); ++i){
                    int idx = G[v][i];
                    int next = E[idx].to;

                    if(dad[next] == -1 && E[idx].f){
                        dad[next] = v;
                        e[next] = idx;
                        q.push(next);
                    }
                }
            }
            if(dad[sink] == -1)
                return 0;
            
            int cur = sink, flow = inf;
            while(cur != source){
                int idx = e[cur];
                flow = min(flow, E[idx].f);
                cur = dad[cur];
            }
            cur = sink;
            while(cur != source){
                int idx = e[cur];
                E[idx].f -= flow;
                E[idx ^ 1].f += flow;
                cur = dad[cur];
            }

            return flow;
        };

        int flow = 0, f;
        while(f = bfs()) flow += f;
        return flow;
    }
};
// ##############################################################

// Dinic ########################################################
struct Dinic {
    struct FlowEdge {
        int v, u;
        long long cap, flow = 0;
        FlowEdge(int v, int u, long long cap) : v(v), u(u), cap(cap) {}
    };
    const long long flow_inf = 1e18;
    vector<FlowEdge> edges;
    vector<vector<int>> adj;
    int n, m = 0;
    int s, t;
    vector<int> level, ptr;
    queue<int> q;

    Dinic(int n, int s, int t) : n(n), s(s), t(t) {
        adj.resize(n);
        level.resize(n);
        ptr.resize(n);
    }

    void add_edge(int v, int u, long long cap) {
        edges.emplace_back(v, u, cap);
        edges.emplace_back(u, v, 0);
        adj[v].push_back(m);
        adj[u].push_back(m + 1);
        m += 2;
    }

    bool bfs() {
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int id : adj[v]) {
                if (edges[id].cap - edges[id].flow < 1)
                    continue;
                if (level[edges[id].u] != -1)
                    continue;
                level[edges[id].u] = level[v] + 1;
                q.push(edges[id].u);
            }
        }
        return level[t] != -1;
    }

    long long dfs(int v, long long pushed) {
        if (pushed == 0)
            return 0;
        if (v == t)
            return pushed;
        for (int& cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
            int id = adj[v][cid];
            int u = edges[id].u;
            if (level[v] + 1 != level[u] || edges[id].cap - edges[id].flow < 1)
                continue;
            long long tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
            if (tr == 0)
                continue;
            edges[id].flow += tr;
            edges[id ^ 1].flow -= tr;
            return tr;
        }
        return 0;
    }

    long long flow() {
        long long f = 0;
        while (true) {
            fill(level.begin(), level.end(), -1);
            level[s] = 0;
            q.push(s);
            if (!bfs())
                break;
            fill(ptr.begin(), ptr.end(), 0);
            while (long long pushed = dfs(s, flow_inf)) {
                f += pushed;
            }
        }
        return f;
    }
};
//###############################################################

//Dijkstra ######################################################
struct Dijkstra{
    int n, oo;
    vector<int> d, p;
    vector<bool> flag;
    vector<vector<pair<int, int>>> G;
    queue<pair<int, int>> cola;

    Dijkstra(int n, int inf):
        n(n + 1), oo(inf), d(n + 1, inf), p(n + 1, 0), flag(n + 1), G(n + 1){}
    
    void add_edge(int a, int b, int cost){
        G[a].push_back({b, cost});
    }

    void solve(int start){
        int u, v, c;
        d[start] = 0;
        cola.push({0, start});
        fill(all(flag), true);

        while(!cola.empty()){
            u = cola.front().second;
            cola.pop();
            if(flag[u] && value[u] < k){
                for(auto &edge:G[u]){
                    v = edge.first;
                    c = edge.second;
                    if(flag[v] && c + d[u] < d[v]){
                        d[v] = c + d[u];
                        p[v] = u;
                        cola.push({-(c + d[u]), v});
                    }
                }
                flag[u] = false;
            }
        }
    }
};

//###############################################################

//Range-Minimum-Query ###########################################
struct RMQ{
    int n, lg;
    vector<vector<ll>> dp;
    RMQ(vector<ll> &data, ll top):
        n(data.size()), lg((int)log2(n)), dp(n + 1, vector<ll>(lg + 1, top))
    {
        for (int i = 1; i <= n; ++i)
            dp[i][0] = data[i - 1];
        for (int p = 1; p <= lg; ++p)
            for (int i = 1; i <= n - (1 << p) + 1; ++i)
                dp[i][p] = min(dp[i][p - 1], dp[i + (1 << (p - 1))][p - 1]);
    }
    ll query(int a, int b){
        //in arguments for refer x is necessary to pass x + 1
        int p = log2(b - a + 1);
        return min(dp[a][p], dp[b - (1 << p) + 1][p]);
    }
};
//###############################################################

//Link-Cut-Tree #################################################
template<class node>
struct link_cut_tree
{
    bool connected(node* u, node* v) { return lca(u, v) != NULL; }
 
    int depth(node* u) { access(u); return get_sz(u->ch[0]); }
 
    node* get_root(node* u) // get root of LCT component
    {
        access(u);
        while (u->ch[0]) u = u->ch[0], u->push();
        return access(u), u;
    }
 
    node* ancestor(node* u, int k) // get k-th parent on path to root
    {
        k = depth(u) - k;
        assert(k >= 0);
        for (; ; u->push())
        {
            int sz = get_sz(u->ch[0]);
            if (sz == k) return access(u), u;
            if (sz < k) k -= sz+1, u = u->ch[1];
            else u = u->ch[0];
        }
        assert(0);
    }
 
    node* lca(node* u, node* v)
    {
        if (u == v) return u;
        access(u); access(v);
        if (!u->p) return NULL;
        u->splay(); return u->p ?: u;
    }
 
    void link(node* u, node* v) // make u parent of v
    {
        assert(!connected(u, v));
        make_root(v);
        access(u); set_link(v, u, 0); v->update();
    }
 
    void cut(node* u) // cut u from its parent
    {
        access(u);
        u->ch[0]->p = NULL;
        u->ch[0] = NULL;
        u->update();
    }
 
    void cut(node* u, node* v) // if u, v adj in tree
    {
        //make_root(u); access(v); cut(v);
        cut(depth(u) > depth(v) ? u : v);
    }
 
    void make_root(node* u) // make u root of LCT component
    {
        access(u);
        u->rev ^= 1;
        access(u);
        assert(!u->ch[0] && !u->ch[1]);
    }
 
    void access(node *u) // puts u on the preferred path, splay (right subtree is empty)
    {
        for (node* v = u, *pre = NULL; v; v = v->p)
        {
            v->splay(); // now update virtual children
            if (pre) v->update_vsub(pre, false);
            if (v->ch[1]) v->update_vsub(v->ch[1], true);
            v->ch[1] = pre; v->update(); pre = v;
        }
        u->splay(); assert(!u->ch[1]);
    }
 
    node* operator[](int i) { return &data[i]; }
    int operator[](node* i) { return i - &data[0]; }
 
    vector<node> data;
    link_cut_tree(int n) : data(n) {}
};
 
template<typename pnode>
struct splay_tree
{
    pnode ch[2], p;
    bool rev;
    int sz;
 
    splay_tree() { ch[0] = ch[1] = p = NULL; rev = 0; sz = 1; }
 
    friend int get_sz(pnode u) { return u ? u->sz : 0; }
 
    virtual void update()
    {
        if (ch[0]) ch[0]->push();
        if (ch[1]) ch[1]->push();
        sz = 1 + get_sz(ch[0]) + get_sz(ch[1]);
    }
 
    virtual void push()
    {
        if (rev)
        {
            if (ch[0]) ch[0]->rev ^= 1;
            if (ch[1]) ch[1]->rev ^= 1;
            swap(ch[0], ch[1]); rev = 0;
        }
    }
 
    int dir()
    {
        if (!p) return -2; // root of LCT component
        if (p->ch[0] == this) return 0; // left child
        if (p->ch[1] == this) return 1; // right child
        return -1; // root of current splay tree
    }
 
    bool is_root() { return dir() < 0; }
 
    friend void set_link(pnode u, pnode v, int d)
    {
        if (v) v->p = u;
        if (d >= 0) u->ch[d] = v;
    }
 
    void rotate() // assume p and p->p propagated
    {
        assert(!is_root());
        int x = dir(); pnode g = p;
        set_link(g->p, static_cast<pnode>(this), g->dir());
        set_link(g, ch[x^1], x);
        set_link(static_cast<pnode>(this), g, x^1);
        g->update(); update();
    }
 
    void splay() // bring this to top of splay tree
    {
        while (!is_root() && !p->is_root())
        {
            p->p->push(), p->push(), push();
            dir() == p->dir() ? p->rotate() : rotate();
            rotate();
        }
        if (!is_root()) p->push(), push(), rotate();
        push();
    }
};
 
struct node : splay_tree<node*>
{
    node() : splay_tree() {}
    void update_vsub(node* v, bool add) {}
};
//###############################################################

//monotonic queue ###############################################
struct monotonic_queue{
    deque<pair<ll, ll>> deq;

    void add(ll k, ll v, comparer foo){
        while (!deq.empty() && foo(deq.back(), k, v))
            deq.pop_back();
        deq.push_back({k, v});
    }

    void remove(ll k){
        while (!deq.empty() && deq.front().first <= k)
            deq.pop_front();
    }

    ll top(){
        return deq.front().second;
    }

    ll pos(){
        return deq.front().first;
    }
};
//###############################################################

// KMP ##########################################################
vector<int> prefixFunction(string &p){
    int k = 0, m = (int)p.size();
    vector<int> prefix(m, 0);
    for(int i = 1; i < m; ++i){
        while(k > 0 && p[i] != p[k])
           k = prefix[k - 1];
        k += (p[i] == p[k]);
        prefix[i] = k;
    }
    return prefix;
}

int kmp(string &t, string &p){
    int k = 0;
    auto prefix = prefixFunction(p);
    int cont = 0, n = (int)t.size(), m = (int)p.size();
    for(int i = 0; i < n; ++i){
        while(k > 0 && t[i] != p[k])
            k = prefix[k - 1];
        k += (t[i] == p[k]);
        if(k == m){
            ++cont;
            k = prefix[k - 1];
        }
    }
    return cont;
}
//###############################################################