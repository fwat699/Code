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
const int mod = 1e9 + 9, N = 1e5 + 7;
LL n, a, b, k, ans;
char S[N];
LL Pow(LL a, LL b) {
	a %= mod;
	LL res = 1ll;
	for(; b; b >>= 1, a = a * a % mod) if(b & 1) res = res * a % mod;
	return res;
}
LL Inv(LL a) {
	return Pow(a, mod - 2);
}
int main() {
	scanf("%lld%lld%lld%lld", &n, &a, &b, &k);
	scanf("%s", S);
	for(int i = 0; i < k; ++i) {
		LL s = S[i] == '+' ? 1: mod - 1;
		LL x = (n - i) / k;
		LL sum;
		if(Inv(Pow(a, k)) * Pow(b, k) % mod != 1) {
			sum = (1 - Inv(Pow(a, (x + 1) * k)) * Pow(b, (x + 1) * k) % mod + mod) % mod;
			sum = sum * Inv((1 + mod - Inv(Pow(a, k)) * Pow(b, k) % mod)) % mod;
		}else sum = (x + 1);
		ans = (ans + s * Pow(a, n) % mod * sum % mod * Inv(Pow(a, i)) % mod * Pow(b, i) % mod) % mod;
	}
	printf("%lld\n", ans);
	return 0;
}
