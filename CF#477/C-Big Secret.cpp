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
const int N = 1e5 + 7;
int n;
LL b, ans[N], sum;
multiset<LL>f[66];
int main() {
#ifndef ONLINE_JUDGE
#endif
	n = gi();
	rep(i, 1, n) {
		scanf("%lld", &b);
		for(int j = 59; ~j; --j) if(b >> j & 1) { f[j].insert(b); break;}
	}
	rep(i, 1, n) {
		bool fg = 0;
		for(int j = 0; j < 60; ++j) if(!(sum >> j & 1) && f[j].size()) {
			fg = 1;
			LL t = *f[j].begin();
			f[j].erase(f[j].lower_bound(t));
			ans[i] = t, sum ^= t;
			break;
		}
		if(!fg) return puts("No"), 0;
	}
	puts("Yes");
	for(int i = 1; i <= n; ++i) printf("%lld%c", ans[i], i == n?'\n':' ');
	return 0;
}
