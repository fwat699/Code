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
template <typename T> inline bool Max(T &a, T b){return a < b ? a = b, 1 : 0;}
template <typename T> inline bool Min(T &a, T b){return a > b ? a = b, 1 : 0;}
const int N = 1e6 + 7, mod = 1e9 + 7;
int n, ans = 1, tp;
int par[N], col[N], nxt[N], st[N];
vector<int>G[N], H[N];
typedef pair<int, int>pii;
#define mp make_pair
#define fi first
#define se second
pii p[N];
set<pii>Q;
void Add(int a, int b) {
	G[a].pb(b), G[b].pb(a);
}
void dfs(int u, int c) {
	if(col[u] != -1) {
		if(col[u] != c) puts("0"), exit(0);
		return;
	}
	col[u] = c;
	for(auto v:G[u]) dfs(v, col[u] ^ 1);
	for(auto v:H[u]) dfs(v, col[u]);
}
int main() {
	n = gi();
	memset(col, -1, sizeof col);
	rep(i, 1, n) p[i].fi = gi(), p[i].se = gi();
	sort(p + 1, p + 1 + n);
	rep(i, 1, n) {
		tp = 0;
		while(!Q.empty() && (*Q.begin()).fi < p[i].fi) {//Ê÷ÐÎ½á¹¹£»
			int t = (*Q.begin()).se;
			Q.erase(Q.begin());
			if(nxt[t]) Q.insert(mp(p[nxt[t]].se, nxt[t]));
		}
		while(!Q.empty() && (*Q.begin()).fi < p[i].se) {
			st[++tp] = (*Q.begin()).se;
			Q.erase(Q.begin());
		}
		if(tp) {
			rep(j, 1, tp - 1) nxt[st[j]] = st[j + 1], H[st[j]].pb(st[j + 1]), H[st[j + 1]].pb(st[j]);
			rep(j, 1, tp) Add(i, st[j]);
			Q.insert(mp(p[st[1]].se, st[1]));
		}
		Q.insert(mp(p[i].se, i));
	}
	rep(i, 1, n) if(col[i] == -1) ans = ans * 2 % mod, dfs(i, 0);
	printf("%d\n", ans);
	return 0;
}
