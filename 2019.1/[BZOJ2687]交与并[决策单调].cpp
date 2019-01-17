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
typedef pair<int, int> pii;
#define mp make_pair
#define fi first
#define se second
const int N = 1e6 + 7;
int n, ndc, cnt;
int sum[N];
LL ans;
pii q[N];
struct data {
	int l, r;
	data(){}data(int l, int r):l(l), r(r){}
	bool operator <(const data &rhs) const {
		if(l != rhs.l) return l < rhs.l;
		return r > rhs.r;
	}
}t[N], d[N];
LL calc(int p, int a) {
	if(d[p].l > d[a].r) return 0;
	return (LL)(d[p].r - d[a].l) * (d[a].r - d[p].l);
}
bool better(int p, int a, int b) {
	return calc(p, a) <= calc(p, b);
}
int find(int l, int r, int a, int b) {
	while(l < r) {
		int mid = l + r >> 1;
		if(better(mid, a, b)) r = mid;
		else l = mid + 1;
	}
	return l;
}
int main() {
	n = gi();
	rep(i, 1, n) t[i].l = gi(), t[i].r = gi();
	sort(t + 1, t + 1 + n);
	for(int i = 1, maxn = 0, cho; i <= n; ++i) {
		if(t[i].r > maxn) d[++ndc] = t[i], maxn = t[i].r, cho = i;
		else Max(ans, (LL)(t[cho].r - t[cho].l) * (t[i].r - t[i].l));
	}
	int hd = 1, tl = 0;
	for(int i = 1; i <= ndc; ++i) {
		for(; hd < tl && q[hd + 1].fi <= i; ++hd);
		if(i ^ 1) Max(ans, calc(i, q[hd].se));
		for(; hd <= tl && better(max(i + 1, q[tl].fi), q[tl].se, i); --tl);
		if(hd > tl) q[++tl] = mp(i + 1, i);
		else if(i < ndc && better(ndc, q[tl].se, i)) q[tl + 1] = mp(find(max(i + 1, q[tl].fi), ndc, q[tl].se, i), i), ++tl;
	}
	printf("%lld\n", ans);
	return 0;
}
