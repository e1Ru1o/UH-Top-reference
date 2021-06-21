#include <bits/stdc++.h>

#define db(x) cout << #x ": " << (x) << '\n';

using namespace std;

typedef pair<int,int> pii;

typedef long long ll;

const ll oo = 1e18;

const int MAXN = 1e5 + 100;

int N, M;

pii vect[MAXN];

int A[MAXN];

bool mark[MAXN];

vector<int> L[MAXN];

set<pii> st;

struct edge
{
    int u, v, w;
    friend bool operator<(const edge &a, const edge &b)
    {
        return a.w > b.w;
    }
};

bool find(int a, int b)
{
    return binary_search(L[a].begin(),L[a].end(),b);
}

int contg;
void add()
{
    contg++;
    if(contg == 2.5e6)printf("%d",6/0);
}

ll prim()
{
    ll mst = 0;
    int cont = 0;
    mark[1] = true;
    st.erase(st.find({A[1],1}));
    if(st.size())
    {
        vect[1] = *st.begin();
        priority_queue<edge> Q;
        Q.push({1,vect[1].second,A[1]+vect[1].first+max(A[1],vect[1].first)});
        while(!Q.empty())
        {
            add();
            edge root = Q.top();
            Q.pop();
            if(!find(root.u,root.v) && !mark[root.v])
            {
                mst += root.w;
                cont++;
                mark[root.v] = true;
                st.erase(st.find({A[root.v],root.v}));
                if(st.size())
                {
                    vect[root.v] = *st.begin();
                    Q.push({root.v,vect[root.v].second,A[root.v]+vect[root.v].first+max(A[root.v],vect[root.v].first)});
                }
            }
            auto pt = st.upper_bound(vect[root.u]);
            if(pt != st.end())
            {
                vect[root.u] = *pt;
                Q.push({root.u,vect[root.u].second,A[root.u]+vect[root.u].first+max(A[root.u],vect[root.u].first)});
            }
        }
    }
    if(cont != N-1)return oo;
    return mst;
}

int main()
{
    scanf("%d%d",&N,&M);

    ll sum = 0;

    for(int i = 1 ; i <= N ; i++)
    {
        int n;
        scanf("%d",&n);
        A[i] = n;
        st.insert({A[i],i});
        sum += A[i];
    }

    for(int i = 1 ; i <= M ; i++)
    {
        int u, v;
        scanf("%d%d",&u,&v);
        L[u].push_back(v);
        L[v].push_back(u);
    }

    for(int i = 1 ; i <= N ; i++)
    {
        sort(L[i].begin(),L[i].end());
    }

    ll res = prim();

    if(res == oo)printf("NIE");
    else printf("%ld",res-sum);

    return 0;
}