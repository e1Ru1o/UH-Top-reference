#include <bits/stdc++.h>

using namespace std;

struct SegmentTree {
    vector<int> st, lazy, A;
    int n;
    int leftc(int p) { return (p << 1) + 1; }
    int rightc(int p) { return (p << 1) + 2; }
    int join(int a, int b) { return a + b; }

    void build(int p, int L, int R) {
        if (L == R) { st[p] = A[L]; }
        else {
            int c = (L + R)/2, p1 = leftc(p), p2 = rightc(p);
            build(p1, L, c);
            build(p2, c + 1, R);
            st[p] = join(st[p1], st[p2]);
        }
    }

    int query(int p, int L, int R, int i, int j) {
        if (i == L && j == R) { return st[p]; }
        int c = (L + R)/2, p1 = leftc(p), p2 = rightc(p);
        push(p, L, R); //delete this for no using lazy part
        if ( j <= c ) { return query(p1, L, c, i, j); }
        if ( i > c ) { return query(p2, c + 1, R, i, j); }
        int q1 = query(p1, L, c, i, c), q2 = query(p2, c + 1, R, c + 1, j);
        return join(q1, q2);
    }

    //The Lazy part
    inline void push(int p, int L, int R) {
        if(lazy[p]) {
           int c = (L + R)/2, p1 = leftc(p), p2 = rightc(p);
           st[p1] += (c - L + 1)*lazy[p];
           st[p2] += (R - c)*lazy[p];
           lazy[p1] += lazy[p];
           lazy[p2] += lazy[p];
           lazy[p] = 0;
        }
    }

    void update(int p, int L, int R, int i, int j, int v) {
        if (i == L && j == R) { st[p] += (R - L + 1)*v; lazy[p] += v; return; }
        int c = (L + R)/2, p1 = leftc(p), p2 = rightc(p);
        push(p, L, R);
        if ( j <= c ) { update(p1, L, c, i, j, v); }
        else if ( i > c ) { update(p2, c + 1, R, i, j, v); }
        else { update(p1, L, c, i, c, v); update(p2, c + 1, R, c + 1, j, v); }
        st[p] = join(st[p1], st[p2]);
    }

    SegmentTree(const vector<int> v; &_A) {
        A = _A; n = (int)A.size();
        st.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
        build(0, 0, n - 1);
    }

    int query(int i, int j) { return query(0, 0, n - 1, i, j); }

    void update(int i, int j, int v) { update(0, 0, n - 1, i, j, v); }
};

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    vector<int> a{1, 2, 3 , 4 , 5, 6, 7};
    SegmentTree st(a);

    cout<<st.query(3, 4)<<"\n";

    st.update(2, 5, 1);
    
    cout<<st.query(3, 4)<<"\n";

    return 0;
}
