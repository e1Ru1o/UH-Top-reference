struct convex_hull_trick // upper_hull
{
	typedef long long ll;
	struct point { ll x, y; };
	vector<point> hull;
	int last;

	convex_hull_trick()
	{
		last = 0;
		hull.clear();
		hull.push_back({ 0, 0 });
	}

	void add(ll x, ll y)
	{
		int p = hull.size();
		while (--p && (y - hull[p - 1].y) * (hull[p].x - x) + y * (x - hull[p - 1].x)
						>= hull[p].y * (x - hull[p - 1].x)) hull.pop_back();
		last = min(last, (int) hull.size());
		hull.push_back({ x, y });
	}

	inline ll f(int i, ll x)
	{
		return hull[i].x * x + hull[i].y;
	}

	ll query(ll x)
	{
		while (last + 1 < (int) hull.size() && f(last + 1, x) >= f(last, x)) ++last;
		return f(last, x);
	}
};
