
typedef complex<double> point;
typedef vector<point> polygon;

#define NEXT(i) (((i) + 1) % n)

struct circle { point p; double r; };
struct line { point p, q; };
using segment = line;

const double eps = 1e-9;

// fix comparations on doubles with this two functions
int sign(double x) { return x < -eps ? -1 : x > eps; }

int dblcmp(double x, double y) { return sign(x - y); }

double dot(point a, point b) { return real(conj(a) * b); }

double cross(point a, point b) { return imag(conj(a) * b); }

double area2(point a, point b, point c) { return cross(b - a, c - a); } // cross

int ccw(point a, point b, point c)
{
	b -= a; c -= a;
	if (cross(b, c) > 0) return +1; // counter clockwise
	if (cross(b, c) < 0) return -1; // clockwise
	if (dot(b, c) < 0) return +2; // c--a--b on line
	if (dot(b, b) < dot(c, c)) return -2; // a--b--c on line
	return 0;
}

namespace std
{
	bool operator<(point a, point b)
	{
		if (a.real() != b.real())
			return a.real() < b.real();
		return a.imag() < b.imag();
	}
}

double angle(point a, point b, point c) // returns the angle abc (cos(x) = Va * Vb / |Va| * |Vb|)
{
    a -= b, c -= b;
    return acos((a.X * c.X + a.Y * c.Y) / (sqrt((double) sqr(a.X) + sqr(a.Y)) * sqrt((double) sqr(c.X) + sqr(c.Y))));
}

// contrary clock side direction
pair<double, double> rotacion(double x, double y, double ang)
{
	ang = (acos(-1.0) * ang) / 180.0;
	return { x * cos(ang) - y * sin(ang), x * sin(ang) + y * cos(ang) };
}

// contrary clock side direction
point rotacion(point x, ld ang)
{
	ang = (acos(-1.0) * ang) / 180.0;
	return x * polar(1.0, ang);//ang en radianes...
}