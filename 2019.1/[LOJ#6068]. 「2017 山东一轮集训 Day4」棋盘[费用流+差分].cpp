#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define go(u) for(int i = head[u], v = e[i].to; i; i=e[i].lst, v=e[i].to)
#define rep(i, a, b) for(int i = a; i <= b; ++i)
#define pb push_back
#define re(x) memset(x, 0, sizeof x)
typedef pair<int, int> pii;
#define mp make_pair
#define fi first
#define se second
inline int gi() {
    int x = 0,f = 1;
    char ch = getchar();
    while(!isdigit(ch)) { if(ch == '-') f = -1; ch = getchar();}
    while(isdigit(ch)) { x = (x << 3) + (x << 1) + ch - 48; ch = getchar();}
    return x * f;
}
template <typename T> inline void Max(T &a, T b){if(a < b) a = b;}
template <typename T> inline void Min(T &a, T b){if(a > b) a = b;}
const int N = 54, Nd = N * N * 3, inf = 0x3f3f3f3f;
int n, ndc;
int ans[N * N];
char s[N][N];
namespace MCMF {
	int edc = 1, st, ed;
	int head[Nd], vis[Nd], dis[Nd], cur[Nd];
	struct edge {
		int lst, to, cap, flow, c;
	}e[Nd * 10];
	void Add(int a, int b, int c, int d) {
		e[++edc] = (edge){ head[a], b, c, 0, d}, head[a] = edc;
		e[++edc] = (edge){ head[b], a, 0, 0, -d}, head[b] = edc;
	}
	bool spfa() {
		queue<int>Q;
		memset(dis, 0x3f, sizeof dis); dis[st] = 0;
		rep(i, 1, ndc) cur[i] = head[i];
		Q.push(st);
		while(!Q.empty()) {
			int u = Q.front();Q.pop();
			vis[u] = 0;
			go(u)if(e[i].cap - e[i].flow > 0 && dis[u] + e[i].c < dis[v]) {
				dis[v] = dis[u] + e[i].c;
				if(!vis[v]) vis[v] = 1, Q.push(v);
			}
		}
		return dis[ed] != inf;
	}
	pii dfs(int u, int b ){
		if(u == ed || !b) return mp(b, 0);
		pii res(0, 0), f;
		vis[u] = 1;
		for(int &i = cur[u], v = e[i].to; i; i = e[i].lst, v = e[i].to) 
		if(e[i].cap - e[i].flow > 0 && dis[u] + e[i].c == dis[v] && !vis[v]) {
			f = dfs(v, min(b, e[i].cap - e[i].flow));
			res.fi += f.fi;
			res.se += f.se + f.fi * e[i].c;
			e[i].flow += f.fi, e[i ^ 1].flow -= f.fi, b -= f.fi;
		}
		vis[u] = 0;
		return res;
	}
	pii mcmf() {
		pii res(0, 0);
		while(spfa()) {
			pii f = dfs(st, inf);
			rep(i, 1, f.fi)
				ans[res.fi + i] = ans[res.fi] + i * dis[ed];
			res.fi += f.fi;
			res.se += f.se;
		}
		return res;
	}
}
int idx(int x, int y) {
	return (x - 1) * n + y;
}
int main() {
	using namespace MCMF;
	n = gi();ndc = n * n;st = ++ndc, ed = ++ndc;
	rep(i, 1, n) scanf("%s", s[i] + 1);
	rep(r, 1, n) {
		for(int i = 1, j = 1; i <= n; i = j + 1, j = i) {
			while(j + 1 <= n && s[r][j + 1] == s[r][j]) ++j;
			if(s[r][i] == '.') {
				++ndc;
				rep(k, i, j) Add(ndc, idx(r, k), 1, 0);
				rep(k, 1, j - i + 1) Add(st, ndc, 1, k * (k - 1) / 2 - (k - 1) * (k - 2) / 2);
			}
		}
	}
	rep(c, 1, n) { 	
		for(int i = 1, j = 1; i <= n; i = j + 1, j = i) {
			while(j + 1 <= n && s[j + 1][c] == s[j][c]) ++j;
			if(s[i][c] == '.') {
				++ndc;
				rep(k, i, j) Add(idx(k, c), ndc, 1, 0);
				rep(k, 1, j - i + 1) Add(ndc, ed, 1, k * (k - 1) / 2 - (k - 1) * (k - 2) / 2);
			}
		}
	}
	mcmf();
	int Q = gi();
	while(Q--) printf("%d\n", ans[gi()]);
	return 0;
}
