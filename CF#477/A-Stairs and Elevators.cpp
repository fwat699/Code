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
const int N = 1e5 + 7, inf = 0x3f3f3f3f;
int s1[N], s2[N];
int n, m, cl, ce, v, x1, y1, x2, y2;
int solve(int *s, int n, int v) {
	if(!n) return inf;
	if(x1 == x2) return abs(y1 - y2);
	int res = inf;
	int p = lower_bound(s + 1, s + 1 + n, y1) - s;
	if(p != n + 1) {
		Min(res, abs(s[p] - y1) + abs(s[p] - y2) + abs(x1 - x2) / v + (bool)(abs(x1 - x2) % v));
	}
	if(p != 1) {
		--p;
		Min(res, abs(s[p] - y1) + abs(s[p] - y2) + abs(x1 - x2) / v + (bool)(abs(x1 - x2) % v));
	}
	return res;
}
int main() {
#ifndef ONLINE_JUDGE
//	freopen("data.in", "r", stdin);
#endif
	n = gi(), m = gi(), cl = gi(), ce = gi(), v = gi();
	rep(i, 1, cl) s1[i] = gi();
	rep(i, 1, ce) s2[i] = gi();
	int q = gi();
	while(q--) {
		x1 = gi(), y1 = gi(), x2 = gi(), y2 = gi();
		printf("%d\n", min(solve(s1, cl, 1), solve(s2, ce, v)));
	}
	return 0;
}
