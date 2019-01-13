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
const int N = 2e5 + 7, m1 = 1e9 + 7, m2 = 1e9 + 9;
int n, tim, tp;
int in[N], out[N], st[N], Len[N];
vector<int>G[N];
typedef pair<int, int> pii;
#define mp make_pair
#define fi first
#define se second
vector<pii> f[N];
struct ht {
	int v1, v2;
	ht(){v1 = v2 = 0;}ht(int v1, int v2):v1(v1), v2(v2){}
	ht operator +(int x) { return ht((v1 + x) % m1, (v2 + x) % m2);}
	ht operator -(int x) { return ht((v1 - x + m1) % m1, (v2 - x + m2) % m2);}
	ht operator *(int x) { return ht((LL)v1 * x % m1, (LL)v2 * x % m2);}
	ht operator +(ht x) {  return ht((v1 + x.v1) % m1, (v2 + x.v2) % m2);}
	ht operator -(ht x) {  return ht((v1 - x.v1 + m1) % m1, (v2 - x.v2 + m2) % m2);}
	ht operator *(ht x) {  return ht((LL)v1 * x.v1 % m1, (LL)v2 * x.v2 % m2);}
	LL get() { return (LL)v1 * m1 + v2;}
}bin[N], pre[N];
void dfs1(int u) {
	in[u] = ++tim;
	pre[tim] = pre[tim - 1] * 233 + 1;
	for(auto v:G[u]){
		dfs1(v);
		Max(Len[u], Len[v] + 1);
	}
	out[u] = ++tim;
	pre[tim] = pre[tim - 1] * 233 + 0;
}
void dfs2(int u, int mid) {
	st[++tp] = u;
	if(tp > mid + 1) f[st[tp - mid - 1]].pb(mp(in[u], out[u]));
	for(auto v:G[u]) {
		dfs2(v, mid);
	}
	--tp;
}
LL gg[N];
ht get(int l, int r) {
	return pre[r] - pre[l - 1] * bin[r - l + 1];
}
void add(ht &t, int l, int r) {
	if(l > r) return;
	t = t * bin[r - l + 1] + get(l, r);
}
bool check(int mid) {
	rep(i, 1, n) f[i].clear();
	dfs2(1, mid);
	rep(i, 1, n) sort(f[i].begin(), f[i].end());
	int len = 0;
	rep(u, 1, n) if(Len[u] >= mid){
		ht tmp;
		if(!f[u].size()) add(tmp, in[u], out[u]);
		else {
			if(in[u] < f[u][0].fi) add(tmp, in[u], f[u][0].fi - 1);
			for(int j = 0; j + 1 < f[u].size(); ++j) add(tmp, f[u][j].se + 1, f[u][j + 1].fi - 1);
			if(out[u] > f[u][f[u].size() - 1].se) add(tmp, f[u][f[u].size() - 1].se + 1, out[u]);
		}
		gg[++len] = tmp.get();
	}
	sort(gg + 1, gg + 1 + len);
	rep(i, 2, len) if(gg[i] == gg[i - 1]) return 1;
	return 0;
}
int main() {
	n = gi();
	bin[0] = ht(1, 1); rep(i, 1, 2 * n) bin[i] = bin[i - 1] * 233;
	rep(i, 1, n) {
		int x = gi();
		rep(j, 1, x) G[i].pb(gi());
	}
	dfs1(1);
	int l = 0, r = n - 1;
	while(l < r) {
		int mid = l + r + 1>> 1;
		if(check(mid)) l = mid;
		else r = mid - 1;
	}
	printf("%d\n", l);
	return 0;
}
