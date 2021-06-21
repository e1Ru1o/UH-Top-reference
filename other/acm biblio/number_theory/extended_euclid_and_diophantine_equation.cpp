// returns (d, x, y) such that d = gcd(a, b) = ax + by
int extended_euclid(int a, int b, int &x, int &y)
{
	if (b == 0) { x = 1, y = 0; return a; }
	int r = extended_euclid(b, a % b, y, x);
	y -= a / b * x;
	return r;
}

// returns (x, y) such that c = ax + by
pair<int, int> diophantine_equation(int a, int b, int c)
{
	int g, x, y;
	g = extended_euclid(a, b, x, y);
	int k = 0; // k e Z
	return { x * c / g + (k * b / g), y * c / g - (k * a / g) };
}