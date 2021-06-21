typedef complex<double> point;

void fft(point a[], size_t n, int sign)
{
    for (size_t i = 1, j = 0; i + 1 < n; ++i)
    {
        for (size_t k = n >> 1; (j ^= k) < k; k >>= 1);
        if (i < j) swap(a[i], a[j]);
    }
    const double theta = 2 * acos(-1) * sign;
    for (size_t m, mh = 1; (m = mh << 1) <= n; mh = m)
    {
        point wm = polar(1.0, theta / m);
        for (size_t i = 0; i < n; i += m)
        {
            point w(1.0);
            for (size_t j = i; j < i + mh; ++j)
            {
                point u = a[j], v = a[j + mh] * w;
                a[j] = u + v;
                a[j + mh] = u - v;
                w *= wm;
            }
        }
    }
    if (sign == -1)
        for (size_t i = 0; i < n; ++i) a[i] /= n;
}

vector<ll> convolve(const vector<ll> &a, const vector<ll> &b)
{
	int n = a.size() + b.size() - 1, size = 1;
	while (size < n) size *= 2;
	vector<point> pa(size), pb(size);
	for (int i = 0; i < a.size(); ++i) pa[i] = a[i];
	for (int i = 0; i < b.size(); ++i) pb[i] = b[i];
	fft(pa.data(), pa.size(), +1);
	fft(pb.data(), pb.size(), +1);
	for (int i = 0; i < size; ++i) pa[i] *= pb[i];
		fft(pa.data(), pa.size(), -1);
	vector<ll> ans(n);
	for (int i = 0; i < n; ++i) ans[i] = round(real(pa[i]));
	return ans;
}
