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
const int N = 2e5 + 7;
int n, tim;
int t[N][2], fa[N], zson[N], son[N], top[N], dep[N], invt[N], out[N], in[N], tr[N];
LL sum;
int lowbit(int x) { return x & -x;}
void modify(int x, int y) {
	for(int i = x; i <= n; i += lowbit(i)) tr[i] += y;
}
int query(int x) {
	int res = 0;
	for(int i = x; i; i -= lowbit(i)) res += tr[i];
	return res;
}
int query(int l, int r) {
	if(r == 0) return 0;
	return query(r) - query(l - 1);
}
void dfs1(int u) {
	son[u] = 1;
	for(int i = 1; ~i; --i) {
		int v = t[u][i];
		if(!v) continue;
		dep[v] = dep[u] + 1; fa[v] = u;
		dfs1(v); son[u] += son[v];
		if(son[v] >= son[zson[u]]) zson[u] = v;
	}
	sum += zson[u];
}
void dfs2(int u, int from) {
	top[u] = from;
	invt[in[u] = ++tim] = u;
	if(zson[u]) dfs2(zson[u], from);
	for(int i = 1; ~i; --i) {
		int v = t[u][i];
		if(!v || v == zson[u]) continue;
		dfs2(v, v);
	}
	modify(in[u], 1);
	out[u] = tim;
}
int jump(int x, int d) {
	for(; dep[top[x]] > d; x = fa[top[x]]);
	return invt[in[x] - (dep[x] - d)];
}
int side(int x) { return t[fa[x]][1] == x; }
int gts(int x) {
	return query(in[x], out[x]);
}
int main() {
	n = gi();
	rep(o, 1, n) {
		t[o][0] = gi(), t[o][1] = gi();
	}
	dep[1] = 1, dfs1(1), dfs2(1, 1);
	int Q = gi();
	printf("%lld\n", sum);
	while(Q--) {
		int x = gi(), rt = 1;
		modify(in[x], -1);
		while(1) {
			int l = dep[rt] + 1, r = dep[x], ret = r + 1;
			while(l <= r) {
				int mid = l + r >> 1;
				if(gts(jump(x, mid)) <= gts(rt) / 2) ret = mid, r = mid - 1;
				else l = mid + 1;
			}
			if(ret != dep[x] + 1) {
				int a = jump(x, ret), b = t[fa[a]][side(a) ^ 1];
				if(zson[fa[a]] == a) {
					if(gts(a) + 1 == gts(b)) sum += b - a, zson[fa[a]] = b;
					else if(!gts(a) && !gts(b)) sum -= a, zson[fa[a]] = 0;
				}
				rt = a;
			}else break;
		}
		printf("%lld\n", sum);
	}
	return 0;
}
