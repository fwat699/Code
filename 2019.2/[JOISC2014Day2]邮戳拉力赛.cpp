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
const int N = 3007, inf = 0x3f3f3f3f;
int n, T;
int a[N], b[N], c[N], d[N];
int f[N][N];
int main() {
#ifndef ONLINE_JUDGE
#endif
	n = gi(), T = gi();
	rep(i, 1, n) a[i] = gi(), b[i] = gi(), c[i] = gi(), d[i] = gi();
	memset(f, 0x3f, sizeof f);
	f[0][0] = 0;
	for(int i = 1; i <= n; ++i) {
		for(int j = 0; j <= n; ++j) {
			if(j) {
				Min(f[i][j], f[i - 1][j] + T * 2 * j + c[i] + d[i]);
				Min(f[i][j], f[i - 1][j - 1] + T * 2 * (j - 1) + b[i] + c[i]);
			}
			Min(f[i][j], f[i - 1][j] + T * 2 * j + a[i] + b[i]);
			Min(f[i][j], f[i - 1][j + 1] + T * 2 * (j + 1) + a[i] + d[i]);
		}
		for(int j = 1; j <= n; ++j) Min(f[i][j], f[i][j - 1] + b[i] + c[i]);
		for(int j = n - 1; ~j; --j) Min(f[i][j], f[i][j + 1] + a[i] + d[i]);
	}
	printf("%d\n", f[n][0] + (n + 1) * T);
	return 0;
}
