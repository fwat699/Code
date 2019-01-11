#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define go(u) for(int i = head[u], v = e[i].to; i; i=e[i].lst, v=e[i].to)
#define rep(i, a, b) for(int i = a; i <= b; ++i)
#define pb push_back
#define re(x) memset(x, 0, sizeof x)
inline int gi() {
    int x = 0,f = 1;
    char ch = getchar();
    while(!isdigit(ch)) { if(ch == '-') f = -1; ch = getchar();}
    while(isdigit(ch)) { x = (x << 3) + (x << 1) + ch - 48; ch = getchar();}
    return x * f;
}
template <typename T> inline void Max(T &a, T b){if(a < b) a = b;}
template <typename T> inline void Min(T &a, T b){if(a > b) a = b;}
typedef unsigned long long ull;
const int N = 2e5 + 7, m1 = 1e9 + 7, m2 = 1e9 + 9;
int n, vc, ans;
LL w[N], h[N], c[N], V[N], d[N];
struct ht {
	ull v1, v2;
	ht(){}ht(LL v1, LL v2):v1(v1), v2(v2){}
	ht operator +(LL x) { return ht((v1 + x) % m1, (v2 + x) % m2);}
	ht operator *(LL x) { return ht((LL)v1 * x % m1, (LL) v2 * x % m2);}
	ht operator +(ht b) {  return ht((v1 + b.v1) % m1, (v2 + b.v2) % m2);}
	ht operator -(ht b) {  return ht((v1 - b.v1 + m1) % m1, (v2 - b.v2 + m2) % m2);}
	ht operator *(ht b) {  return ht((LL) v1 * b.v1 % m1, (LL) v2 * b.v2 % m2);}
	ull get() { return (LL) v1 * m1 + v2;}
}t, lst;
struct data {
	LL h, c;
	bool operator <(const data &rhs) const {
		return h < rhs.h;
	}
};
LL gcd(LL a, LL b) {
	return !b ? a : gcd(b, a % b);
}
vector<data> G[N];
int main() {
#ifndef ONLINE_JUDGE
#endif
	n = gi();
	rep(i, 1, n) {
		scanf("%lld%lld%lld", &w[i], &h[i], &c[i]);
		V[i] = w[i];
	}
	sort(V + 1, V + 1 + n);
	vc = unique(V + 1, V + 1 + n) - V - 1;
	rep(i, 1, n) {
		w[i] = lower_bound(V + 1, V + 1 + vc, w[i]) - V;
		G[w[i]].pb((data){ h[i], c[i]});
	}
	rep(i, 1, vc) {
		sort(G[i].begin(), G[i].end());
		LL &g = d[i];
		g = G[i][0].c;
		for(int j = 1; j < G[i].size(); ++j) g = gcd(G[i][j].c, g);
		t = ht(0, 0);
		for(auto v:G[i]) t = t * 233 + (ull) (v.c / g) * v.h;
		if(i ^ 1 && t.get() != lst.get()) return puts("0"), 0;
		lst = t;
	}
	LL g = d[1];
	rep(i, 2, vc) g = gcd(d[i], g);
	for(int i = 1, l = (int)sqrt(g); i <= l; ++i) if(g % i == 0){
		++ans;
		if(1ll * i * i != g) ++ans;
	}
	printf("%d\n", ans);
	return 0;
}
