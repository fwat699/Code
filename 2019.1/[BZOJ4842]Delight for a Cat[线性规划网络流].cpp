#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define go(u) for(int i = head[u], v = e[i].to; i; i=e[i].lst, v=e[i].to)
#define rep(i, a, b) for(int i = a; i <= b; ++i)
#define pb push_back
#define re(x) memset(x, 0, sizeof x)
#define fi first
#define se second
#define mp make_pair
typedef pair<LL, LL> pii;
inline int gi() {
    int x = 0,f = 1;
    char ch = getchar();
    while(!isdigit(ch)) { if(ch == '-') f = -1; ch = getchar();}
    while(isdigit(ch)) { x = (x << 3) + (x << 1) + ch - 48; ch = getchar();}
    return x * f;
}
template <typename T> inline void Max(T &a, T b){if(a < b) a = b;}
template <typename T> inline void Min(T &a, T b){if(a > b) a = b;}
const int N = 1007, inf = 0x3f3f3f3f;
int n, k, ms, me;
int S[N], E[N], id[N];
namespace MCMF {
	int edc = 1, st, ed;
	int head[N], cur[N], vis[N];
	LL dis[N];
	struct edge {
		int lst, to, cap, flow, c;
		edge(){}edge(int lst, int to, int cap, int flow, int c) : lst(lst), to(to), cap(cap), flow(flow), c(c){}
	}e[N * 10];
	void Add(int a, int b, int c, int d) {
		e[++edc] = edge(head[a], b, c, 0, -d), head[a] = edc;
		e[++edc] = edge(head[b], a, 0, 0, d), head[b] = edc;
	}
	bool spfa() {
		queue<int>Q;
		Q.push(st);
		fill(dis + 1, dis + 3 + n, 1e18);dis[st] = 0;
		rep(i, 1, n + 2) cur[i] = head[i];
		while(!Q.empty()) {
			int u = Q.front();Q.pop();
			vis[u] = 0;
			go(u)if(e[i].cap - e[i].flow > 0 && dis[u] + e[i].c < dis[v]) {
				dis[v] = dis[u] + e[i].c;
				if(!vis[v]) vis[v] = 1, Q.push(v);
			}
		}
		return dis[ed] != 1e18;
	}
	pii dfs(int u, int b) {
		if(u == ed || !b) return mp(b, 0);
		pii res(0, 0), f;
		vis[u] = 1;
		for(int &i = cur[u]; i; i = e[i].lst) 
		if(e[i].cap - e[i].flow > 0 && dis[u] + e[i].c == dis[e[i].to] && !vis[e[i].to]){
			f = dfs(e[i].to, min(b, e[i].cap - e[i].flow));
			res.fi += f.fi;
			res.se += f.se + f.fi * e[i].c;
			e[i].flow += f.fi, e[i ^ 1].flow -= f.fi, b -= f.fi;
			if(!b) break;
		}
		vis[u] = 0;
		return res;
	}
	LL mcmf() {
		pii res(0, 0);
		while(spfa()) {
			pii f = dfs(st, inf);
			res.fi += f.fi;
			res.se += f.se;
		}
		return res.se;
	}
}
int main() {
	using namespace MCMF;
	n = gi(), k = gi(), ms = gi(), me = gi();
	LL sum = 0;
	rep(i, 1, n) S[i] = gi();
	rep(i, 1, n) E[i] = gi(), sum += E[i];
	ed = n + 1, st = n + 2;
	rep(i, 1, n) id[i] = edc + 1, Add(max(1, i - k + 1), i + 1, 1, S[i] - E[i]);
	rep(i, 1, n) Add(i, i + 1, i <= n - k + 1 ? k - ms - me: inf, 0);
	Add(st, 1, k - me, 0);
	printf("%lld\n", sum - mcmf());
	rep(i, 1, n) printf("%c", e[id[i]].flow == 1 ? 'S': 'E');
	return 0;
}
