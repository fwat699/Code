#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long LL;
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
const int N = 65;
int T, n;
int fail[N], s[N];
LL K, bin[N], f[N];
LL solve(int len) {
	re(f);
	rep(i, 1, n) {
		if(i <= len) { f[i] = !fail[i]; continue; }
		f[i] = bin[i - len];
		for(int j = 1; j <= i / 2; ++j) {
			if(j >= len) f[i] -= f[j] * bin[i - 2 * j];
			else if(len <= i - j) f[i] -= f[j] * bin[i - len - j];
			else if(f[j]){
				for(int a = 1, b = i - j + 1; b <= len; ++a, ++b) if(s[a] != s[b]) goto gg;
				--f[i];
			}
			gg:;
		}
	}
	return f[n];
}
void getfail(int len) {
	for(int i = 2, j = 0; i <= len; ++i) {
		while(j && s[j + 1] != s[i]) j = fail[j];
		fail[i] = s[j + 1] == s[i] ? ++j : 0;
	}
}
int main() {
	T = gi();
	bin[0] = 1; rep(i, 1, 63) bin[i] = bin[i - 1] * 2;
	while(T--) {
		scanf("%d%llu", &n, &K);
		printf("%llu\n", solve(0));
		rep(i, 1, n) {
			s[i] = 0;
			getfail(i);
			LL res = solve(i);
			if(K > res) K -= res, s[i] = 1;
		}
		rep(i, 1, n) {
			printf("%c", 'a' + s[i]);
		}
		puts("");
	}
	return 0;
}
