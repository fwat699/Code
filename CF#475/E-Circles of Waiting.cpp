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
const int N = 110, mod = 1e9 + 7;
int ndc, n = 102;
int id[N][N], G[8000][8000], dx[] = {-1, 0, 1, 0}, dy[] = {0, -1, 0, 1};
LL p[4], R;
LL Pow(LL a, LL b) {
	a %= mod;
	LL res = 1ll;
	for(; b; b >>= 1, a = a * a % mod) if(b & 1) res = res * a % mod;
	return res;
}
LL Inv(LL a) { return Pow(a, mod - 2);}
LL sqr(int x) { return 1ll * x * x;}
void Gauss(int n, int m) {
	for(int u = 1, col = 1; col <= m; ++u ,++col) {
		int sel = u;
		for(; sel <= n && !G[sel][col]; ++sel);
		if(sel > n) { --u; continue; }
		if(sel ^ u) { for(int i = col; i <= m + 1; ++i) swap(G[u][i], G[sel][i]); }
		LL inv = Inv(G[u][col]);
		for(int i = col; i <= min(m, col + 104); ++i) G[u][i] = (LL)G[u][i] * inv % mod;
		G[u][m + 1] = (LL)G[u][m + 1] * inv % mod;
		
		for(int v = u + 1; v <= min(n, u + 104); ++v) if(u ^ v){
			int val = G[v][col];
			for(int i = col; i <= min(m, col + 104); ++i) G[v][i] = (G[v][i] - (LL)G[u][i] * val % mod + mod) % mod;
			G[v][m + 1] = (G[v][m + 1] - (LL)G[u][m + 1] * val % mod + mod) % mod;
		}
	}
	for(int i = n; i; --i) {
		for(int j = i + 1; j <= n; ++j)
		G[i][m + 1] = (G[i][m + 1] - (LL) G[i][j] * G[j][m + 1] % mod + mod) % mod;
	}
}
int main() {
#ifndef ONLINE_JUDGE
#endif
	R = gi(), p[0] = gi(), p[1] = gi(), p[2] = gi(), p[3] = gi();
	LL inv = Inv(p[0] + p[1] + p[2] + p[3]);
	rep(i, 0, 3) p[i] = p[i] * inv % mod;
	
	rep(i, 1, n) rep(j, 1, n) if(sqr(51 - i) + sqr(51 - j) <= R * R) id[i][j] = ++ndc;
	rep(i, 1, n) rep(j, 1, n) if(sqr(51 - i) + sqr(51 - j) <= R * R) {
		int t = id[i][j];
		for(int d = 0; d < 4; ++d) {
			int tx = i + dx[d], ty = j + dy[d];
			if(sqr(51 - tx) + sqr(51 - ty) <= R * R) G[t][id[tx][ty]] = mod - p[d];
		}
		G[t][ndc + 1] = 1;
		G[t][t] = 1;
	}
	Gauss(ndc, ndc);
	printf("%d\n", G[id[51][51]][ndc + 1]);
	return 0;
}
