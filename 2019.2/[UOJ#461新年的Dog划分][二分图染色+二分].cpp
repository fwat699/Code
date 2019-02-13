#include<bits/stdc++.h>
#include "graph.h"
using namespace std;
typedef long long LL;
#define go(u) for(int i = head[u], v = e[i].to; i; i = e[i].lst, v = e[i].to)
#define pb push_back
#define re(x) memset(x, 0, sizeof x)
typedef pair<int, int> pii;
#define mp make_pair
#define fi first
#define se second
inline int gi() {
	int x = 0, f = 1; char ch = getchar();
	while(!isdigit(ch)) { if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) { x = (x << 3) + (x << 1) + ch - 48; ch = getchar();}
	return x * f;
}
template<typename T>inline bool Max(T &a, T b) { return a < b ? a = b, 1 : 0;}
template<typename T>inline bool Min(T &a, T b) { return a > b ? a = b, 1 : 0;}
const int N = 204;
int n;
int vis[N], mark[N], inq[N], bel[N], gg[N][N], ont[N][N];
vector<pii>tq, del, t;
vector<int>q, G[N], A, C;
queue<int>Q;
void Add(int a, int b) { G[a].pb(b); G[b].pb(a);}
bool check(int u, int r) {
	tq = del;
	for(int i = 0; i <= r; ++i) tq.pb(mp(u, q[i]));
	return query(tq);
}
int find(int u) {
	if(q.size() == 0) return -1;
	int l = 0, r = q.size() - 1;
	if(check(u, r)) {for(int i = 0; i <= r; ++i) gg[u][q[i]] = 1, del.pb(mp(u, q[i])); vis[u] = -1; return -1;}
	while(l < r) {
		int mid = l + r >> 1;
		if(check(u, mid)) l = mid + 1;
		else r = mid;
	}
	for(int i = 0; i < l; ++i) gg[u][q[i]] = 1, del.pb(mp(u, q[i]));
	return q[l];
}
void dfs(int u, int fa) {
	for(auto v:G[u]) if(v ^ fa) {
		bel[v] = bel[u] ^ 1;
		dfs(v, u);
	}
}
bool fuck(int x) {
	tq.clear();
	for(int i = 0; i < n; ++i) if(!bel[i])
	for(int j = 0; j < n; ++j) if(bel[j] && !ont[i][j]) tq.pb(mp(i, j));
	tq.pb(t[x]);
	return query(tq);
}
vector<int> check_bipartite(int vsize)
{
	n = vsize;
	inq[0] = 1;Q.push(0);
	while(!Q.empty()) {
		int u = Q.front();
		q.clear();	for(int i = 0; i < n; ++i) if(!inq[i] && !gg[u][i]) q.pb(i);
		int v = find(u);
		if(v == -1) { Q.pop(); continue;}
		Q.push(v), inq[v] = 1;
		Add(u, v), ont[u][v] = ont[v][u] = 1, t.pb(mp(u, v));
	}
	dfs(0, -1);
	for(int i = 0; i < n; ++i) if(!bel[i]) A.pb(i);
	for(int i = 0; i < n - 1; ++i) if(fuck(i)) return C;
	return A;
}
