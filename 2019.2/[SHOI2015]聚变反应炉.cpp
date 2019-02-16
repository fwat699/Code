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
const int N = 1e5 + 7, inf = 0x3f3f3f3f;
int n, edc, mx;
int d[N], c[N], head[N];
struct edge {
	int lst, to;
	edge(){}edge(int lst, int to):lst(lst), to(to){}
}e[N << 1];
void Add(int a, int b) {
	e[++edc] = edge(head[a], b), head[a] = edc;
	e[++edc] = edge(head[b], a), head[b] = edc;
}
namespace task1 {
    const int N = 1e5 + 7;
    int f[N], g[N];//f:ÏÈ¼¤»î¸¸Ç×£» 
    void dfs(int u, int fa) {
    	int cnt = 0;
    	g[u] = d[u];
    	go(u)if(v ^ fa) {
    		dfs(v, u);
    		if(f[v] < g[v]) g[u] += f[v];
    		else {
				g[u] += g[v];
				if(cnt < d[u] && c[v]) {
					++cnt;
					g[u]--;
				}
			}
    	}
    	f[u] = g[u] - (c[fa] && cnt < d[u]);
    }
    void solve() {
    	dfs(1, 0);
    	printf("%d\n", g[1]);
    }
}
namespace task2 {
	const int N = 2007;
	int g[N], f[N], h[N][10004], t[10004];
	void dfs(int u, int fa) {
		memset(h[u], 0x3f, sizeof h[u]);
		h[u][0] = 0;
		go(u)if(v ^ fa) {
			dfs(v, u);
			memset(t, 0x3f, sizeof t);
			for(int tv = min(10000, d[u]); ~tv; --tv) if(h[u][tv] != inf) {
				Min(t[min(d[u], tv + c[v])], h[u][tv] + g[v]);
				Min(t[tv], h[u][tv] + f[v]);
			}
			memcpy(h[u], t, sizeof t);
		}
		g[u] = f[u] = inf;
		for(int i = 0; i <= min(10000, d[u]); ++i) {
			Min(g[u], h[u][i] + d[u] - i);
			Min(f[u], h[u][i] + max(0, d[u] - i - c[fa]));
		}
	}
	void solve() {
		dfs(1, 0);
		printf("%d\n", g[1]);
	}
}
int main() {
    n = gi();
    rep(i, 1, n) d[i] = gi();
    rep(i, 1, n) c[i] = gi(), Max(mx, c[i]);
    rep(i, 1, n - 1) Add(gi(), gi());
    mx <= 1 ? task1::solve() : task2::solve();
	return 0;
}
