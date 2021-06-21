int num[N], low[N], timer;
bool artP[N];
vector<int> G[N],Stack;


void dfs(int u, vector<vector<int> > &cmps)
{
    Stack.push_back(u);
    num[u]=low[u]=timer++;

    for(int i=0;i<G[u].size();++i)
    {
        int v=G[u][i];
        if(!num[v])
        {
            dfs(v, cmps);
            low[u]=min(low[v], low[u]);
            if(low[v]>=num[u])
            {
                if(u!=0||num[v]>2)
                    artP[u]=1;

                cmps.push_back(vector<int>(1,u));
                do
                {
                    cmps.back().push_back(Stack.back());
                    Stack.pop_back();
                } while (cmps.back().back()!=v);

            }
        }
        else
            low[u]=min(low[u], num[v]);
    }
}