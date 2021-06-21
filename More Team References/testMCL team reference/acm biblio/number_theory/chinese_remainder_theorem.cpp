// return min x such that x % m[i] == a[i]
int chinese_remainder_theorem(vector<int> a, vector<int> m)
{
	int n = a.size(), s = 1, t, ans = 0, p, q;
	for (auto i : m) s *= i;
	for (int i = 0; i < n; i++)
	{
		t = s / m[i];
		extended_euclid(t, m[i], p, q);
		ans = (ans + t * p * a[i]) % s;
	}
	if (ans < 0) ans += s;
	return ans;
}

/*
	Solve x=ai(mod mi), for any i and j, (mi,mj)|ai-aj
	Return (x0,M) M=[m1..mn]. All solutions are x=x0+t*M

	Note: be carful with the overflow in the multiplication
	Tested: LIGHTOJ 1319
*/

pair<ll, ll> linear_congruences(const vector<ll> &a, const vector<ll> &m)
{
	int n = a.size();
	ll u = a[0], v = m[0], p, q;
	for (int i = 1; i < n; ++i)
	{
		ll r = gcd(v, m[i], p, q);
		ll t = v;
		if ((a[i] - u) % r)
			return {-1, 0}; // no solution
		v = v / r * m[i];
		u = ((a[i] - u) / r * p * t + u) % v;
	}
	if (u < 0)
		u += v;
	return {u, v};
}
