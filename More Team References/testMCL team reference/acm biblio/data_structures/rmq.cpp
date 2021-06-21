template<typename T>min
struct RMQ
{
	int n, lg;
	vector<vector<T>> dp;

	RMQ(vector<T> &a) : n(a.size()), lg(log2(n)), dp(n + 1, vector<T>(lg + 1, 1<<30))
	{
		for (int j = 1; j <= n; j++)
			dp[j][0] = a[j - 1];

		for (int i = 1; i <= lg; i++)
			for (int j = 1; j <= n - (1 << i) + 1; j++)
				dp[j][i] = min(dp[j][i - 1], dp[j + (1 << (i - 1))][i - 1]);
	}

	T query(int a, int b)
	{
		int l = log2(b - a + 1);
		return min(dp[a][l], dp[b - (1 << l) + 1][l]);
	}
};