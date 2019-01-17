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
const int N = 5e5 + 7;
int n, k, mod;
int inv[N], fac[N], invfac[N];
int C(int n, int m) {
	return (LL)fac[n] * invfac[m] % mod * invfac[n - m] % mod;
}
int Pow(int a, int b) {
	int res = 1;
	for(; b; b >>= 1, a = (LL) a * a % mod) if(b & 1) res = (LL)res * a % mod;
	return res;
}
int main() {
	n = gi(), k = gi(), mod = gi();
	inv[1] = fac[0] = invfac[0] = 1;
	rep(i, 1, n) {
		if(i ^ 1) inv[i] = (LL)(mod - mod / i) * inv[mod % i] % mod;
		fac[i] = (LL)fac[i - 1] * i % mod;
		invfac[i] = (LL)invfac[i - 1] * inv[i] % mod;
	}
	printf("%d\n", (LL)Pow(k, n - k - 1) * Pow(n - k, k - 1) % mod * C(n - 1, k - 1) % mod);
	return 0;
}
