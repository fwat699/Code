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
const int N = 5e5 + 7;
int T, tot, n;
int d[N], f[N], cnt;
vector<int>G[N];
char s[N];
int main() {
	for(int T = gi(), tt = 1; tt <= T; ++tt) {
		n = gi();
		cnt = 0, tot = n;
		rep(i, 1, n) d[i] = f[i] = 0, G[i].clear();
		rep(i, 1, n - 1) {
			int u = gi(), v = gi();
			d[u] ++, d[v] ++;
			G[u].pb(v), G[v].pb(u);
		}
		scanf("%s", s + 1);
		rep(i, 1, n) if(s[i] == 'W') d[i] ++, f[i]++, tot += 3, ++cnt;
		rep(u, 1, n) for(auto v:G[u]) if(d[v] > 1) f[u]++;
		rep(i, 1, n) {
			if(d[i] >= 4 || (f[i] >= 2 && d[i] >= 3)) { puts("White"); goto A;}
			if(d[i] == 3) ++cnt;
		}
		if(cnt == 2) {
			if((tot - 4) % 2 == 1) puts("White");
			else puts("Draw");
		}
		else puts("Draw");
		A:;
	}
	return 0;
}
