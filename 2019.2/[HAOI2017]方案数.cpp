#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define go(u) for(int i = head[u], v = e[i].to; i; i=e[i].lst, v=e[i].to)
#define rep(i, a, b) for(int i = a; i <= b; ++i)
#define pb push_back
#define re(x) memset(x, 0, sizeof x)
template <typename T> inline bool Max(T &a, T b){return a < b ? a = b, 1 : 0;}
template <typename T> inline bool Min(T &a, T b){return a > b ? a = b, 1 : 0;}
const int mod = 998244353;
const int N = 1e5 + 7, Num = 1e5;
int o;
LL n, m, r;
LL fac[N], invfac[N], inv[N], f[66][66][66], g[N];
int ctb(LL x) {
	int ans = 0;
	for(; x; x -= x & -x) ++ans;
	return ans;
}
struct data {
	LL x, y, z;
	int a, b, c;
	data(){}data(LL x, LL y, LL z):x(x), y(y), z(z){
		a = ctb(x);
		b = ctb(y);
		c = ctb(z);
	}
	bool operator <(const data &rhs) const {
		if(x ^ rhs.x) return x < rhs.x;
		if(y ^ rhs.y) return y < rhs.y;
		return z < rhs.z;
	}
	bool inc(data rhs) {
		return (x & rhs.x) == x && (y & rhs.y) == y && (z & rhs.z) == z;
	}
}p[N], st[20];
LL C(int n, int m) {
	return fac[n] * invfac[m] % mod * invfac[n - m] % mod;
}
void add(LL &a, LL b) {
	a += b;if(a >= mod) a -= mod;
}
int main() {
	scanf("%lld%lld%lld", &n, &m, &r);
	scanf("%d", &o);
	rep(i, 1, o) {
		LL x, y, z;
		scanf("%lld%lld%lld", &x, &y, &z);
		if((x & n) != x || (y & m) != y || (z & r) != z) {--i, --o; continue;}
		p[i] = data(x, y, z);
	}
	p[0] = data(0, 0, 0);
	p[++o] = data(n, m, r);
	sort(p, p + o + 1);
	
	inv[1] = fac[0] = invfac[0] = 1;
	rep(i, 1, Num) {
		if(i ^ 1) inv[i] = (mod - mod / i) * inv[mod % i] % mod;
		fac[i] = fac[i - 1] * i % mod;
		invfac[i] = invfac[i - 1] * inv[i] % mod;
	}
	f[0][0][0] = 1;
	for(int i = 0, l1 = ctb(n); i <= l1; ++i)
	for(int j = 0, l2 = ctb(m); j <= l2; ++j)
	for(int k = 0, l3 = ctb(r); k <= l3; ++k) {
		rep(a, 1, i) add(f[i][j][k], f[i - a][j][k] * C(i, a) % mod);
		rep(a, 1, j) add(f[i][j][k], f[i][j - a][k] * C(j, a) % mod);
		rep(a, 1, k) add(f[i][j][k], f[i][j][k - a] * C(k, a) % mod);
	}
	g[0] = 1;
	for(int i = 0; i <= o; ++i) {
		for(int j = i + 1; j <= o; ++j) if(p[i].inc(p[j])) {
			add(g[j], mod - g[i] * f[p[j].a - p[i].a][p[j].b - p[i].b][p[j].c - p[i].c] % mod);
		}
	}
	printf("%lld\n", mod - g[o]);
	return 0;
}
