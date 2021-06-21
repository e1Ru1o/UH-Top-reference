struct Hash
{
	typedef unsigned long long ull;

	int n;
	vector<ull> h, p;

	Hash(const string &s, ull base = 31) : n(s.length()), h(n + 1), p(n + 1, 1)
	{
		for (int i = 1; i <= n; ++i)
			h[i] = h[i - 1] + (s[i - 1] - 'a' + 1) * (p[i] = p[i - 1] * base);
	}

	bool equal(int a, int b, int k)
	{
		return (h[a + k] - h[a]) * p[b - a] == h[b + k] - h[b];
	}
};