template<typename T>
struct ABI
{
    int n;
    vector<T> f;
    ABI(int n) : n(n), f(n + 1) {}

    T query(int b)
    {
        T ret = 0;
        for (; b; b -= b & -b)
            ret += f[b];
        return ret;
    }

    void update(int b, T c)
    {
        for (; b <= n; b += b & -b)
            f[b] += c;
    }
};