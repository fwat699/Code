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
const int N = 5e4 + 7;
int n, T;
int a[N];
int main() {
#ifndef ONLINE_JUDGE
#endif
	T = gi();
	while(T--) {
		n = gi();bool fg = 1;LL tot = 0;
		rep(i, 1, n) a[i] = gi(), tot += a[i];
		if(tot != 1ll * n * (n - 1) / 2) { 
			puts("The data have been tampered with!");
			continue;
		}
		sort(a + 1, a + 1 + n);
		LL sum = 0;
		rep(i, 1, n) {
			sum += a[i];
			if(1ll * i * (i - 1) / 2 > sum) { fg = 0; break;}
		}
		if(!fg) puts("The data have been tampered with!");
		else puts("It seems to have no problem.");
	}
	return 0;
}
