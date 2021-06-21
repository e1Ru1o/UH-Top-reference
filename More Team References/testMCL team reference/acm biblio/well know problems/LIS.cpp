#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;
typedef vector<vi> vvi;

int lis(vi &v) {
    set<int> p;
    for(int i = 0; i < v.size(); ++i) {
        set<int>::iterator it = lower_bound(p.begin(), p.end(), v[i]);
        if(it != p.end()) { p.erase(it); }
        p.insert(v[i]);
    }
    return p.size();
}


int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    vi a{-7, 10, 9, 2, 3, 8, 8, 1};
    cout<<lis(a);

    return 0;
}
