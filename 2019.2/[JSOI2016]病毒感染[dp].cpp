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
const int N = 3007;
const LL inf = 1e16;
int n;
LL g[N][N], f[N], s[N], a[N];
int main() {
	n = gi();
	rep(i, 1, n) a[i] = gi(), s[i] = s[i - 1] + a[i];
	fill(f, f + n + 1, inf);
	for(int j = 1; j <= n; ++j) {
		g[j][j] = s[n] - s[j];
		for(int i = j - 1; i; --i) {
			g[i][j] = g[i + 1][j] + min(3 * (j - i) * a[i] + (s[n] - s[i]) + (s[n] - s[j]) * 2, (s[n] - s[i]) * 2 + (s[n] - s[j]));
		}
	}
	f[0] = 0;
	for(int j = 1; j <= n; ++j) {
		for(int i = 0; i < j; ++i)
			Min(f[j], f[i] + (s[n] - s[i]) * (i != 0) + g[i + 1][j] + (j != n) * (j - i - 1) * (s[n] - s[j]));
	}
	printf("%lld\n", f[n]);
	return 0;
}
